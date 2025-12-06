#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <map>
#include <queue>
#include <list>

using namespace std;

using PuntosVida = int;

using Nombre = string;

struct VillanoInfo {
	int puntosVida;
	int valorAtaque;
	list<Nombre>::iterator it;
};

struct HeroeInfo {
	int puntosVida;
	map<string, int> ataques; //ataque mapeado a valor de daño
	list<Nombre>::iterator it;
};


class Fantasy {
public:
	void aparece_villano(Nombre v, int s, int a) { //O(1)
		if (villanos.contains(v) || heroes.contains(v))
			throw invalid_argument("Personaje ya existente");

		villanos[v].puntosVida = s;
		villanos[v].valorAtaque = a;

		turnos.push_back(v);
		villanos[v].it = --turnos.end();
	}

	void aparece_heroe(Nombre h, int s) { //O(1)
		if (heroes.contains(h) || villanos.contains(h))
			throw invalid_argument("Personaje ya existente");

		heroes[h].puntosVida = s;

		turnos.push_back(h);
		heroes[h].it = --turnos.end();
	}

	void aprende_ataque(Nombre h, string a, int v) { //O(logA) por la búsqueda en un mapa ordenado
		if (!heroes.contains(h))
			throw invalid_argument("Heroe inexistente");

		if (heroes[h].ataques.contains(a))
			throw invalid_argument("Ataque repetido");

		heroes[h].ataques[a] = v;
	}

	vector<pair<Nombre, int>> mostrar_ataques(Nombre h) { //O(A) por recorrer la lista de ataques (longitud A)
		if (!heroes.contains(h))
			throw invalid_argument("Heroe inexistente");

		vector<pair<Nombre, int>> resul;
		for (auto [nombre, valor] : heroes[h].ataques) //A vueltas (cada una con trabajo constante)
			resul.push_back({ nombre, valor });

		return resul;
	}

	vector<pair<Nombre, int>> mostrar_turnos() { //O(T) por recorrer turnos (longitud T)
		vector<pair<Nombre, int>> resul;
		for (Nombre personaje : turnos) { //T vueltas (cada una con trabajo cte.)
			if (heroes.contains(personaje))
				resul.push_back({ personaje, heroes[personaje].puntosVida });
			else
				resul.push_back({ personaje, villanos[personaje].puntosVida });
		}

		return resul;
	}

	bool villano_ataca(Nombre v, Nombre h) { //O(1)
		if (!villanos.contains(v))
			throw invalid_argument("Villano inexistente");
		if (!heroes.contains(h))
			throw invalid_argument("Heroe inexistente");
		
		if (turnos.front() != v) 
			throw invalid_argument("No es su turno");

		heroes[h].puntosVida -= villanos[v].valorAtaque;

		bool derrotado = false;
		if (heroes[h].puntosVida <= 0) {
			turnos.erase(heroes[h].it);
			heroes.erase(h);
			derrotado = true;
		}

		turnos.pop_front();
		turnos.push_back(v);
		villanos[v].it = --turnos.end();

		return derrotado;
	}

	bool heroe_ataca(Nombre h, string a, Nombre v) { //O(logA) por las operaciones sobre el map de ataques
		
		if (!villanos.contains(v))
			throw invalid_argument("Villano inexistente");

		if (!heroes.contains(h))
			throw invalid_argument("Heroe inexistente");

		if (turnos.front() != h)
			throw invalid_argument("No es su turno");

		if (!heroes[h].ataques.contains(a))
			throw invalid_argument("Ataque no aprendido");

		villanos[v].puntosVida -= heroes[h].ataques[a];

		bool derrotado = false;

		if (villanos[v].puntosVida <= 0) {
			turnos.erase(villanos[v].it); 
			villanos.erase(v);
			derrotado = true;
		}

		turnos.pop_front();
		turnos.push_back(h);
		heroes[h].it = --turnos.end();
		return derrotado;
	}


private:
	unordered_map<Nombre, VillanoInfo> villanos;
	unordered_map<Nombre, HeroeInfo> heroes;
	list<Nombre> turnos;
};



bool casoDePrueba() {

	Fantasy sistema;   // sistema nuevo para este caso
	string op;

	// Intentamos leer la primera operación
	if (!(cin >> op)) return false; // no hay más casos (EOF)

	// Procesamos hasta encontrar FIN
	while (op != "FIN") {
		try {
			if (op == "aparece_villano") {
				string v;
				long long s, a;
				cin >> v >> s >> a;
				sistema.aparece_villano(v, s, a);
			}
			else if (op == "aparece_heroe") {
				string h;
				long long s;
				cin >> h >> s;
				sistema.aparece_heroe(h, s);
			}
			else if (op == "aprende_ataque") {
				string h, a_nombre;
				long long d;
				cin >> h >> a_nombre >> d;
				sistema.aprende_ataque(h, a_nombre, d);
			}
			else if (op == "mostrar_ataques") {
				string h;
				cin >> h;
				auto ataques = sistema.mostrar_ataques(h);
				cout << "Ataques de " << h << "\n";
				for (auto const& par : ataques) {
					cout << par.first << " " << par.second << "\n";
				}
			}
			else if (op == "mostrar_turnos") {
				auto turnos = sistema.mostrar_turnos();
				cout << "Turno:\n";
				for (auto const& par : turnos) {
					cout << par.first << " " << par.second << "\n";
				}
			}
			else if (op == "villano_ataca") {
				string v, h;
				cin >> v >> h;
				bool derrotado = sistema.villano_ataca(v, h);
				cout << v << " ataca a " << h << "\n";
				if (derrotado) {
					cout << h << " derrotado\n";
				}
			}
			else if (op == "heroe_ataca") {
				string h, a_nombre, v;
				cin >> h >> a_nombre >> v;
				bool derrotado = sistema.heroe_ataca(h, a_nombre, v);
				cout << h << " ataca a " << v << "\n";
				if (derrotado) {
					cout << v << " derrotado\n";
				}
			}

		}
		catch (const invalid_argument& e) {
			cout << "ERROR: " << e.what() << "\n";
		}
		// Leemos la siguiente operación; si hay EOF raro, salimos
		if (!(cin >> op)) return false;
	}

	// Hemos leído FIN para este caso
	cout << "---\n";
	return true;  // hay más casos (o no, pero el main lo volverá a preguntar)
}


int main() {
	while (casoDePrueba());
	return 0;
}