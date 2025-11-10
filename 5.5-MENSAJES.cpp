#include <iostream>
#include <deque>
#include <stack>
#include <string>
using namespace std;

bool casoDePrueba() {
	string cifrado;
	getline(cin, cifrado);

	if (!cin)
		return false;

	deque<char> pila1, pila2;

	for (int i = 0; i < cifrado.size(); i++) {
		if (i % 2 == 0)
			pila1.push_back(cifrado[i]);
		else
			pila2.push_back(cifrado[i]);
	}

	while (!pila2.empty()) {
		pila1.push_back(pila2.back());
		pila2.pop_back();
	}

	//Ahora está X' en pila1
	stack<char> aux;
	while (!pila1.empty()) {
		//SI VOCAL, AÑADIMOS DIRECTAMENTE
		if (tolower(pila1.front()) == 'a' || tolower(pila1.front()) == 'e' || tolower(pila1.front()) == 'o' || tolower(pila1.front()) == 'i' || tolower(pila1.front()) == 'u') {
			cout << pila1.front();
			pila1.pop_front();
		}
		//SI NO, INVERTIMOS
		else {
			while (!pila1.empty() && !(tolower(pila1.front()) == 'a' || tolower(pila1.front()) == 'e' || tolower(pila1.front()) == 'o' || tolower(pila1.front()) == 'i' || tolower(pila1.front()) == 'u')) {
				aux.push(pila1.front());
				pila1.pop_front();
			}
			while (!aux.empty()) {
				cout << aux.top();
				aux.pop();
			}
		}
	}

	cout << "\n";

	return true;
}

int main() {
	while (casoDePrueba());
	return 0;
}