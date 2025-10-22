#include <iostream>
#include <stack>
#include <utility>
#include <string>

using namespace std;

bool casoDePrueba() {
	int N;
	cin >> N;
	if (!cin)
		return false;

	stack<pair<string, int>> pila;
	
	string param1, param2; //fecha, muertos

	for (int i = 0; i < N; i++) {
		string fecha;
		int muertos;
		cin >> fecha >> muertos;

		while (!pila.empty() && pila.top().second <= muertos) {
			pila.pop();
		}

		if (pila.empty())
			cout << "NO HAY\n";
		else
			cout << pila.top().first << "\n";

		pila.push(make_pair(fecha, muertos));
	}

	cout << "---\n";
	return true;
}

int main() {
	while (casoDePrueba());
	return 0; 
}