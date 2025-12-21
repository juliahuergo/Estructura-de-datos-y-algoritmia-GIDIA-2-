#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


using Paciente = string;
using Gravedad = int;


struct PacienteInfo {
	Gravedad gravedad;
	list<Paciente>::iterator it;
};

class Urgencias {
public:
	void nuevo_paciente(Paciente paciente, Gravedad gravedad) { //O(1)
		if (pacientes.contains(paciente)) //O(1)
			throw domain_error("Paciente repetido");
		if (gravedad < 1 || gravedad > 3) //O(1)
			throw domain_error("Gravedad incorrecta");

		int pos = abs(3 - gravedad);  //O(1)
		esperas[pos].push_back(paciente);   //O(1)
		pacientes[paciente] = { gravedad, --esperas[pos].end() }; //O(1)
	}

	int gravedad_actual(Paciente paciente) { //O(1)
		
		if(!pacientes.contains(paciente))
			throw domain_error("Paciente inexistente");

		return pacientes[paciente].gravedad; //O(1)
	}

	Paciente siguiente() { //O(1) pq el tamaño de esperas es fijo
		Paciente resul;
		for (int i = 0; i < esperas.size(); i++) { //3 vueltas como mucho
			if (!esperas[i].empty()) { //O(1)
				resul = esperas[i].front(); //O(1)
				esperas[i].pop_front(); //O(1)
				pacientes.erase(resul); //O(1)
				return resul;
			}
		}
		throw domain_error("No hay pacientes");
	}

	void mejora(Paciente paciente) { //O(log(n))
		if(!pacientes.contains(paciente)) //O(1)
			throw domain_error("Paciente inexistente");

		int i = 3 - pacientes[paciente].gravedad;   // lista donde está ahora: 0,1,2

		esperas[i].erase(pacientes[paciente].it); //O(1)

		if (i != 2) { // no era leve 
			esperas[i + 1].push_front(paciente); //O(1)
			pacientes[paciente].it = esperas[i + 1].begin(); //O(1)
			pacientes[paciente].gravedad--; //O(1)
		}
		else {
			recuperado.insert(paciente); //O(log(n))
			pacientes.erase(paciente); //O(1)
		}
	}

	set<Paciente> recuperados() { //O(1)
		return recuperado; 
	}

private:
	unordered_map<Paciente, PacienteInfo> pacientes;

	//Hacer vector que contenga estas tres listas: 
	vector<list<Paciente>> esperas{3}; //0=grave, 1=medio, 2=leve
	
	set<Paciente> recuperado;

};


bool casoDePrueba() {
	Urgencias urg;
	string op;

	if (!(cin >> op)) return false; // EOF

	while (op != "FIN") {
		try {
			if (op == "nuevo_paciente") {
				string p; int g;
				cin >> p >> g;
				urg.nuevo_paciente(p, g);
			}
			else if (op == "gravedad_actual") {
				string p; cin >> p;
				int g = urg.gravedad_actual(p);
				cout << "La gravedad de " << p << " es " << g << "\n";
			}
			else if (op == "siguiente") {
				string p = urg.siguiente();
				cout << "Siguiente paciente: " << p << "\n";
			}
			else if (op == "mejora") {
				string p; cin >> p;
				urg.mejora(p);
			}
			else if (op == "recuperados") {
				auto rec = urg.recuperados();
				cout << "Lista de recuperados:";
				for (auto const& p : rec) cout << " " << p;
				cout << "\n";
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
