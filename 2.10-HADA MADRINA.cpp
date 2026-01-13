#include <iostream>
#include <vector>
using namespace std;

bool casoDePrueba() {
	int personas;
	cin >> personas;

	if (personas == 0)
		return false;

	int puestos, hada;
	cin >> puestos >> hada;

	vector<vector<int>> satisfacciones;
	for (int i = 0; i < puestos; i++) {
		for (int j = 0; j < personas; j++)
			cin >> satisfacciones[i][j];
	}



	return true;
}

int main() {
	while (casoDePrueba());
	return 0;
}