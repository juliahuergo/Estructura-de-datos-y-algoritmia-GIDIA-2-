/*
meter en la pila si es (, { o [
si aparece uno cerrado, pop, si el anterior es su correspondiente pop

si al final la pila tiene elemento --> NO
si no --> SI
*/

#include <stack>
#include <iostream>
#include <string>

using namespace std;

bool casoDePrueba() {

	string entrada;
	getline(cin, entrada);

	if (!cin)
		return false;


	stack<int> pila;

	for (int i = 0; i < entrada.length(); i++) {
		if (entrada[i] == '(' || entrada[i] == '[' || entrada[i] == '{')
			pila.push(entrada[i]);
		else if (entrada[i] == ')' || entrada[i] == ']' || entrada[i] == '}') {
			if (!pila.empty()) {
				if (entrada[i] == ')' && pila.top() == '(')
					pila.pop();
				else if (entrada[i] == ']' && pila.top() == '[')
					pila.pop();
				else if (entrada[i] == '}' && pila.top() == '{')
					pila.pop();
				else
					pila.push(entrada[i]);
			}
			else
				pila.push(entrada[i]);
		}
		//es una letra --> se ignora
	}

	if (pila.empty())
		cout << "SI\n";
	else
		cout << "NO\n";
	return true;
}

int main() {
	while (casoDePrueba());
	return 0;
}
