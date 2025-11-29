#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <set>
#include <map>
#include <vector>

using namespace std;

using Nombre = string;
using Partido = string;
using Num_votos = int;
using Num_compromisarios = int;

struct EstadoInfo {
	Num_compromisarios num_compromisarios;
	Partido partidoGanador;
	unordered_map<Partido, Num_votos> votosporpartido;
};

//DONDE AÑADIR LOS Nº DE COMPROMISARIOS A UN PARTIDO EN PARTIDOSESTATAL

class ConteoVotos {
public:
	ConteoVotos() {}

	void nuevo_estado(const string& nombre, int num_compromisarios) { //O(logn)
		if (estados.contains(nombre))
			throw domain_error("Estado ya existente");
		estados[nombre].num_compromisarios = num_compromisarios;
	}

	void sumar_votos(const string& estado, const string& partido, int num_votos) { // O(log(n))
		if (!estados.contains(estado))
			throw domain_error("Estado no encontrado");

		estados[estado].votosporpartido[partido] += num_votos;

		/*if (estados[estado].partidoGanador.empty())
			estados[estado].partidoGanador = partido;*/

		if (estados[estado].votosporpartido[partido] > estados[estado].votosporpartido[estados[estado].partidoGanador]) {
			//restar compromisarios al antiguo ganador
			partidosEstatal[estados[estado].partidoGanador] -= estados[estado].num_compromisarios;

			estados[estado].partidoGanador = partido;

			//sumar compromisarios al nuevo ganador
			partidosEstatal[estados[estado].partidoGanador] += estados[estado].num_compromisarios;
		}
	}

	string ganador_en(const string& estado) const { // O(n)
		if (!estados.contains(estado))
			throw domain_error("Estado no encontrado");
		//devolver partido con mayor número de votos en "estado"
		return estados.at(estado).partidoGanador;
	}

	vector<pair<string, int>> resultados() const {
		vector<pair<string, int>> resul;
		for (auto [partido, votos] : partidosEstatal) { 
			if(votos > 0)
				resul.push_back({partido, votos});  
		}
		return resul;
	}

private:
	unordered_map<Nombre, EstadoInfo> estados;
	map<Partido, Num_compromisarios> partidosEstatal;
};


bool casoDePrueba() {
	ConteoVotos eleccion; 
	string operacion;

	// Leemos la primera operación del caso
	if (!(cin >> operacion)) return false; // fin de la entrada total

	while (operacion != "FIN") {
		try {
			if (operacion == "nuevo_estado") {
				Nombre N;
				Num_votos V; 
				cin >> N >> V;
				eleccion.nuevo_estado(N, V);
			}
			else if (operacion == "sumar_votos") {
				Nombre E;
				Nombre P;
				Num_votos V;
				cin >> E >> P >> V;
				eleccion.sumar_votos(E, P, V);
			}
			else if (operacion == "ganador_en") {
				Nombre E;
				cin >> E;
				Partido ganador = eleccion.ganador_en(E);
				cout << "Ganador en " << E << ": " << ganador << "\n";
			}
			else if (operacion == "resultados") {
				vector<pair<string, int>> imprimir = eleccion.resultados();
				for (auto [partido, votos] : imprimir) {
					cout << partido << " " << votos << "\n";
				}
			}
		}
		catch (const domain_error& e) {
			// Cualquier operación que lance error imprime solo ERROR
			cout << e.what() << "\n";
		}

		// Leemos la siguiente operación del caso
		if (!(cin >> operacion)) return false;
	}

	// Al encontrar FIN, cerramos el caso
	cout << "---\n";
	return true;
}

int main() {
	while (casoDePrueba());
	return 0;
}