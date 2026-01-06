#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>
using namespace std;

void casoDePrueba() {
	unordered_map<string, int> dicAntiguo;
	//vector<set<string>> datos(3); //0=añadidas, 1=eliminadas, 2=cambiadas
	set<string> nuevas;
	set<string> eliminadas;
	set<string> cambiadas;

	string linea;
	string entrada;
	getline(cin, linea);
	stringstream ss(linea); //convertimos linea a stringstream
	int cant;

	while (ss >> entrada >> cant)
		dicAntiguo[entrada] = cant;

	getline(cin, linea);
	stringstream s(linea);
	while (s >> entrada >> cant) {  //O(nlogn)
		auto itEntrada = dicAntiguo.find(entrada); //O(1)

		//la palabra no está en el diccionario antiguo
		if (itEntrada == dicAntiguo.end()) {
			nuevas.insert(entrada); //O(logN)
		}
		//cantidad cambiada
		else if (itEntrada->second != cant) {
			cambiadas.insert(entrada); //O(logC)
			dicAntiguo.erase(itEntrada); //O(1) borramos para luego meter las restantes en eliminadas
		}
		//ya estaba y con el mismo valor 
		else {
			dicAntiguo.erase(itEntrada);
		}
	}

	for (auto [entrada, _] : dicAntiguo) {  //O(nlogn)
		eliminadas.insert(entrada); //O(logn)
	}

	bool cambiada = false;
	if (!nuevas.empty()) {
		cambiada = true;
		cout << "+ ";
		auto it = nuevas.begin();

		while (it != nuevas.end()) {
			cout << *it;
			if (it != --nuevas.end())
				cout << " ";
			it++;
		}
		cout << "\n";
	}

	if (!eliminadas.empty()) {
		cambiada = true;
		cout << "- ";
		auto it = eliminadas.begin();

		while (it != eliminadas.end()) {
			cout << *it;
			if (it != --eliminadas.end())
				cout << " ";
			it++;
		}
		cout << "\n";
	}

	if (!cambiadas.empty()) {
		cambiada = true;
		cout << "* ";
		auto it = cambiadas.begin();

		while (it != cambiadas.end()) {
			cout << *it;
			if (it != --cambiadas.end())
				cout << " ";
			it++;
		}
		cout << "\n";
	}

	if (!cambiada)
		cout << "Sin cambios" << "\n";


	cout << "---\n";
}

int main() {
	int n;
	cin >> n;
	cin.ignore(); //porque lo siguiente es un getline()
	while (n--) casoDePrueba();
	return 0;
}

