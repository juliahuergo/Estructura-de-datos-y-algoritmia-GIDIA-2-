#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

using Participante = string;
using Objeto = string;
using Puja = int;

struct ParticipanteInfo {
	int saldo_inicial;
	set<Objeto> objGanados;
	unordered_map<Objeto, pair<Puja, list<Participante>::iterator>> pujados;
};

struct ObjetoInfo {
	int puja_min;
	map<Puja, list<Participante>> pujas; 
	bool vendido;
};

class CasaDeSubastas {
public:
	void nuevo_participante(Participante part, int saldo_inicial) { //O(1)
		if (participantes.contains(part)) //O(1)
			throw domain_error("Participante ya existente");

		if (saldo_inicial <= 0) //O(1)
			throw domain_error("Saldo inicial no valido");

		participantes[part].saldo_inicial = saldo_inicial;  //O(1)
	}

	void nueva_subasta(Objeto obj, Puja puja_min) { //O(1)
		if (objetos.contains(obj)) //O(1)
			throw domain_error("Objeto no valido");

		if (puja_min <= 0)  //O(1)
			throw domain_error("Puja inicial no valida");

		objetos[obj].puja_min = puja_min;
		objetos[obj].vendido = false; 
	}

	void nueva_puja(Participante part, Objeto obj, Puja cantidad) { //O(log(n))
		if (!participantes.contains(part)) //O(1)
			throw domain_error("Participante no existente");

		if (!objetos.contains(obj) || objetos[obj].vendido) //O(1)
			throw domain_error("Objeto no valido");

		if (participantes[part].pujados.contains(obj)) //O(1)
			throw domain_error("Participante repetido");

		//O(1)
		if (cantidad > participantes[part].saldo_inicial || cantidad < objetos[obj].puja_min)
			throw domain_error("Cantidad no valida");

		

		objetos[obj].pujas[cantidad].push_back(part); //O(log(n)) por ser una inserción en un map

		participantes[part].saldo_inicial -= cantidad; //O(1)

		//O(1)
		participantes[part].pujados[obj] = { cantidad, --objetos[obj].pujas[cantidad].end() };
	}

	list<Objeto> subastas_ganadas(Participante part) const { //O(n)
		if (!participantes.contains(part)) //O(1)
			throw domain_error("Participante no existente");

		list<Objeto> resul;
		for (Objeto obj : participantes.at(part).objGanados) //O(n)
			resul.push_back(obj); //O(1)

		return resul;
	}

	void abandonar_casa(Participante part) { //O(n*log(n))
		if (!participantes.contains(part)) //O(1)
			throw domain_error("Participante no existente");

		for (auto const& [obj, objInfo] : participantes[part].pujados) { //O(n)
			objetos[obj].pujas[objInfo.first].erase(objInfo.second);  //O(log(n))

			if (objetos[obj].pujas[objInfo.first].empty())  //O(log(n)) 
				objetos[obj].pujas.erase(objInfo.first); //O(log(n))
		}

		participantes.erase(part); //O(1)
	}

	Participante cerrar_subasta(Objeto obj) { //O(n)
		if (!objetos.contains(obj) || objetos[obj].vendido) //O(1)
			throw domain_error("Objeto no valido");

		if (objetos[obj].pujas.empty()) //O(1)
			throw domain_error("Objeto no vendido");
		
		auto it = --objetos[obj].pujas.end(); //O(1)
		Participante ganador = it->second.front(); //O(1)
		it->second.pop_front(); //O(1)
		participantes[ganador].pujados.erase(obj); //O(1)
		participantes[ganador].objGanados.insert(obj);  //O(log(n))

		objetos[obj].vendido = true;

		for (auto& [puja, lista] : objetos[obj].pujas) { //O(n)
			for (const auto& p : lista) {
				if (p != ganador) {
					if (participantes.contains(p) &&
						participantes[p].pujados.contains(obj)) { //O(1)

						participantes[p].saldo_inicial
							+= participantes[p].pujados[obj].first; //O(1)

						participantes[p].pujados.erase(obj); //O(1)
					}
				}
			}
		}

		return ganador;
	}


private:
	unordered_map<Participante, ParticipanteInfo> participantes;
	unordered_map<Objeto, ObjetoInfo> objetos;
};


bool casoDePrueba() {
	CasaDeSubastas casa;
	string op;

	if (!(cin >> op)) return false; // EOF

	while (op != "FIN") {
		try {
			if (op == "nuevo_participante") {
				Participante p; int saldo;
				cin >> p >> saldo;
				casa.nuevo_participante(p, saldo);
				cout << "OK\n";
			}
			else if (op == "nueva_subasta") {
				Objeto obj; Puja min;
				cin >> obj >> min;
				casa.nueva_subasta(obj, min);
				cout << "OK\n";
			}
			else if (op == "nueva_puja") {
				Participante p; Objeto obj; Puja cant;
				cin >> p >> obj >> cant;
				casa.nueva_puja(p, obj, cant);
				cout << "OK\n";
			}
			else if (op == "abandonar_casa") {
				Participante p;
				cin >> p;
				casa.abandonar_casa(p);
				cout << "OK\n";
			}
			else if (op == "cerrar_subasta") {
				Objeto obj;
				cin >> obj;
				Participante ganador = casa.cerrar_subasta(obj);
				cout << obj << " ha sido ganado por: " << ganador << "\n";
			}
			else if (op == "subastas_ganadas") {
				Participante p;
				cin >> p;
				list<Objeto> ganadas = casa.subastas_ganadas(p);
				cout << p << " ha ganado:";
				for (auto const& obj : ganadas) cout << " " << obj;
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
