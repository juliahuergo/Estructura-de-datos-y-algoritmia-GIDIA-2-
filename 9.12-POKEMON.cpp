#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <list>

using namespace std;

using Entrenador = string;
using Pokemon = string;
using Nivel = int;

struct EntrenadorInfo {
	map<Nivel, Pokemon> niveles;
	unordered_map<Pokemon, pair<Nivel, list<Pokemon>::iterator>> pokemons; 
	list<Pokemon> antiguedad;
};

class MundoPokemon {
public:
	void capturar_pokemon(Entrenador e, Pokemon p, Nivel n) { //O(log(P))
		if (entrenadores[e].pokemons.contains(p))
			throw invalid_argument("Pokemon repetido");
		
		else if(entrenadores[e].niveles.contains(n))
			throw invalid_argument("Nivel repetido");

		entrenadores[e].antiguedad.push_back(p); //O(1)
		entrenadores[e].pokemons[p] = { n , --entrenadores[e].antiguedad.end()}; //O(1)
		entrenadores[e].niveles[n] = p; //O(log(P))
	}

	pair<Pokemon, Nivel> vencer_pokemon(Entrenador e, Nivel n) const { //O(1)
		if (!entrenadores.contains(e)) //O(1)
			throw invalid_argument("Entrenador no existente");
		
		if (entrenadores.at(e).pokemons.empty()) //O(1)
			throw invalid_argument("No tiene pokemons");
		
		auto it_nivel = --entrenadores.at(e).niveles.end(); //O(1)
		if (it_nivel->first < n)  //O(1)
			throw invalid_argument("El pokemon no puede ser vencido");


		return { it_nivel->second , it_nivel->first}; //O(1)
	}

	int dia_de_liberacion(Pokemon p) { //E vueltas * O(1) --> O(E)
		int liberados = 0;
		for (auto it = entrenadores.begin(); it != entrenadores.end(); it++) {
			if (it->second.pokemons.contains(p)) { //O(1)
				it->second.niveles.erase(it->second.pokemons[p].first); //O(1)
				it->second.antiguedad.erase(it->second.pokemons[p].second); //O(n)
				it->second.pokemons.erase(p); //O(1)

				liberados++;
			}
		}

		return liberados;
	}


	Pokemon gimnasio(Entrenador e) { //O(logP)

		if (!entrenadores.contains(e)) //O(1)
			throw invalid_argument("Entrenador no existente");
		
		if (entrenadores[e].pokemons.empty()) //O(1)
			throw invalid_argument("No tiene pokemons");

		Pokemon liberado = entrenadores[e].antiguedad.front(); //O(1)
		entrenadores[e].antiguedad.pop_front(); //O(1)
		entrenadores[e].niveles.erase(entrenadores[e].pokemons[liberado].first);  //O(logP) por eliminar en un map (ordenado)
		entrenadores[e].pokemons.erase(liberado); //O(1)

		return liberado;
	}


private:
	unordered_map<Entrenador, EntrenadorInfo> entrenadores;
	//unordered_map<Pokemon, unordered_set<Entrenador>> pokemons; PARA ITERAR SOBRE LOS POKEMONS EN VEZ DE LOS ENTRENADORES EN DIA DE LIBERACION
};


bool casoDePrueba() {
	MundoPokemon mundoPokemon;
	string operacion;

	// Leemos la primera operación del caso
	if (!(cin >> operacion)) return false; // fin de la entrada total

	while (operacion != "FIN") {
		try {
			if (operacion == "capturar_pokemon") {
				Entrenador E;
				Pokemon P;
				Nivel N;
				cin >> E >> P >> N;
				mundoPokemon.capturar_pokemon(E, P, N);
			}
			else if (operacion == "dia_de_liberacion") {
				Pokemon P;
				cin >> P;
				int resul = mundoPokemon.dia_de_liberacion(P);
				cout << "Liberados " << resul << " pokemon " << P << "\n";
			}
			else if (operacion == "vencer_pokemon") {
				Entrenador E;
				Nivel N;
				cin >> E >> N;
				pair<Pokemon, Nivel> resul = mundoPokemon.vencer_pokemon(E, N);
				cout << E << " utiliza el pokemon " << resul.first
					<< " con nivel " << resul.second
					<< " para vencer a un nivel " << N << "\n";
			}
			else if (operacion == "gimnasio") {
				Entrenador E;
				cin >> E;
				Pokemon P = mundoPokemon.gimnasio(E);
				cout << E << " deja el pokemon " << P << " en un gimnasio\n";
			}
		}
		catch (invalid_argument& e) {
			// Cualquier operación que lance error imprime ERROR: <mensaje>
			cout << "ERROR: " << e.what() << "\n";
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