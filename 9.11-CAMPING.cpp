#include <iostream>
#include <stdexcept>
#include <queue>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

using Persona = string;
using Parcela = int;
using Dia = int;

struct PersonaInfo {
	Dia dia;
	Parcela parcela;
	bool es_titular;
	bool en_espera;
};


class Camping {
public:
	void nueva_reserva(const Persona& persona, Parcela parcela, Dia dia) { // CAMBIAR CUANDO LA PARCELA NO ESTA RESERVADA METER EL ULTIMO MAP
		//persona ya en otra reserva (como titular o a la cola)
		if (personas.contains(persona))
			throw domain_error("Persona ya ha reservado");

		//parcela ya reservada para ese día 
		if (dias_reservado_por_parcela[parcela].contains(dia)) {
			personas[persona] = { dia, parcela, false, true };
			reservas[dia][parcela].push(persona);
		}
		//se reserva la parcela
		else {
			personas[persona] = { dia, parcela, true, false };
			reservas[dia][parcela].push(persona); //
			dias_reservado_por_parcela[parcela].insert(dia);
			parcelas_reservadas_por_dia[dia].insert(parcela);
			titular_por_dia_y_parcela[dia][parcela] = persona;
		}
	}

	void cancelar_reserva(const Persona& persona) { //O(logN + logM)
		auto itPersona = personas.find(persona); //O(1)

		if (itPersona == personas.end() || !itPersona->second.es_titular)
			throw domain_error("No es titular de ninguna reserva");

		auto [dia, parcela, _, __] = itPersona->second;
		personas.erase(persona); //sin reserva esa persona ya no sirve de nada

		reservas[dia][parcela].pop(); //el titular es el primero en la cola

		//si no hay más gente en la cola
		if (reservas[dia][parcela].empty()) {

			reservas[dia].erase(parcela); //O(1)

			parcelas_reservadas_por_dia[dia].erase(parcela); //O(logN)
			if (parcelas_reservadas_por_dia[dia].empty()) //O(1)
				parcelas_reservadas_por_dia.erase(dia); //O(1)

			dias_reservado_por_parcela[parcela].erase(dia); //O(logM)
			if (dias_reservado_por_parcela[parcela].empty()) //O(1)
				dias_reservado_por_parcela.erase(parcela); //O(1)

			titular_por_dia_y_parcela[dia].erase(parcela); //O(1)
			if (titular_por_dia_y_parcela[dia].empty())  //O(1)
				titular_por_dia_y_parcela.erase(dia);    //O(1)
		}
		//se cambia de titular
		else {
			Persona nuevoTitular = reservas[dia][parcela].front();  //O(1)
			personas[nuevoTitular] = { dia, parcela, true, false };  //O(1)
			titular_por_dia_y_parcela[dia][parcela] = nuevoTitular;  //O(1)
		}
	}

	Persona quien_reserva(Parcela parcela, Dia dia) const {
		auto itDia = titular_por_dia_y_parcela.find(dia);
		if (itDia == titular_por_dia_y_parcela.end() || !itDia->second.contains(parcela)) //O(1)
			throw domain_error("Parcela no reservada");

		return itDia->second.at(parcela); //O(1)
	}

	bool puede_extender_reserva(const Persona& persona, int n) const {
		auto itPersona = personas.find(persona);   //O(1)

		if (itPersona == personas.end() || !itPersona->second.es_titular)   //O(1)
			throw domain_error("No es titular de ninguna reserva");

		auto [dia, parcela, _, __] = itPersona->second;

		const auto& setDias = dias_reservado_por_parcela.at(parcela);   //O(1)

		auto itDia = setDias.find(dia); //O(logN)

		if (itDia != --setDias.end()) {
			int diferencia = *(++itDia) - dia - 1; //O(1)
			return n <= diferencia;
		}

		//entonces es el último día reservado, se puede extender lo que se quiera
		return true;
	}

	int menor_distancia(const Persona& persona) const {
		auto itPersona = personas.find(persona);   //O(1)

		if (itPersona == personas.end() || !itPersona->second.es_titular)   //O(1)
			throw domain_error("No es titular de ninguna reserva");

		auto [dia, parcela, _, __] = itPersona->second;
		const auto& setParcelas = parcelas_reservadas_por_dia.at(dia); //O(1)
		auto it = setParcelas.find(parcela);  //O(logN)

		if (setParcelas.size() <= 1) { // O(1)
			return -1;
		}

		//tiene parcelas a ambos lados
		if (it == setParcelas.begin()) {
			auto posterior = next(it);
			int dist1 = abs(*next(it) - *it) - 1;
			return dist1;
		}
		else if (it == --setParcelas.end()) {
			auto anterior = prev(it);
			int dist2 = abs(*prev(it) - *it) - 1;
			return dist2;
		}
		else {
			auto anterior = prev(it);
			auto posterior = next(it);
			int dist1 = abs(*next(it) - *it) - 1; //-1 pq si son contiguas es un 0
			int dist2 = abs(*prev(it) - *it) - 1;
			return min(dist1, dist2);
		}
		//no tiene a ningún lado
		return -1;
	}



private:
	unordered_map<Persona, PersonaInfo> personas;
	unordered_map<Dia, unordered_map<Parcela, queue<Persona>>> reservas; //el primero de la cola es el titular 
	unordered_map<Parcela, set<Dia>> dias_reservado_por_parcela;
	unordered_map<Dia, set<Parcela>> parcelas_reservadas_por_dia; //comparamos con la parcela a la izda y dcha y cogemos el minimo
	unordered_map<Dia, unordered_map<Parcela, Persona>> titular_por_dia_y_parcela;
};

bool casoDePrueba() {
	Camping camping;
	string op;

	if (!(cin >> op)) return false; // EOF

	while (op != "FIN") {
		try {
			if (op == "nueva_reserva") {
				string persona; int parcela, dia;
				cin >> persona >> parcela >> dia;
				camping.nueva_reserva(persona, parcela, dia);
				cout << "OK\n";
			}
			else if (op == "cancelar_reserva") {
				string persona;
				cin >> persona;
				camping.cancelar_reserva(persona);
				cout << "OK\n";
			}
			else if (op == "quien_reserva") {
				int parcela, dia;
				cin >> parcela >> dia;
				string p = camping.quien_reserva(parcela, dia);
				cout << "(" << parcela << ", " << dia << ") reservada por " << p << "\n";
			}
			else if (op == "puede_extender_reserva") {
				string persona; int n;
				cin >> persona >> n;
				bool ok = camping.puede_extender_reserva(persona, n);
				if (ok) cout << persona << " puede extender la reserva " << n << " dias\n";
				else    cout << persona << " no puede extender la reserva " << n << " dias\n";
			}
			else if (op == "menor_distancia_vecinos") {
				string persona;
				cin >> persona;
				int d = camping.menor_distancia(persona);
				if (d == -1) cout << "INFINITO\n";
				else cout << d << "\n";
			}
		}
		catch (domain_error const& e) {
			cout << "ERROR: " << e.what() << "\n";
		}
		cin >> op;
	}

	cout << "---\n";
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	while (casoDePrueba()) {}
	return 0;
}