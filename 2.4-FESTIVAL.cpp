#include <iostream>
#include <vector>
using namespace std;



void backtrack(const vector<vector<int>>& donaciones, const vector<vector<int>>& vetos, int n, vector<bool>& tocado, int k, int& ans, int suma, vector<int>& orden, const vector<int>& optima) {

	if (k == n) { // se han escogido ya todos los momentos 
		ans = max(suma, ans);
	}

	else {
		for (int i = 0; i < n; i++) if (((k == 0) || vetos[i][orden[k - 1]] == 1) && (!tocado[i])) { //iteramos sobre los artistas
			tocado[i] = true;
			orden.push_back(i);
			if (optima[k] + suma + donaciones[i][k] > ans) //puede tocar en ese momento 
				backtrack(donaciones, vetos, n, tocado, k + 1, ans, suma + donaciones[i][k], orden, optima);
			orden.pop_back();
			tocado[i] = false;
		}
	}
}

void resuelveCaso() {
	int n; //número de artistas
	cin >> n;

	vector<vector<int>> donaciones(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> donaciones[i][j];
	}

	vector<vector<int>> vetos(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> vetos[i][j];
	}

	vector<bool> tocado(n, false);
	vector<int> orden; 

	vector<int> maximos(n);
	for (int i = 0; i < n; i++) {
		int maximo = 0; 
		for (int j = 0; j < n; j++) {
			if (donaciones[j][i] > maximo)
				maximo = donaciones[j][i];
		}
		maximos[i] = maximo; 
	}

	vector<int> optima(n, 0);
	int i = n - 2;
	while (i >= 0) {
		optima[i] = optima[i + 1] + maximos[i + 1];
		i--;
	}

	int ans = -1;
	backtrack(donaciones, vetos, n, tocado, 0, ans, 0, orden, optima);

	
	if (ans < 0)
		cout << "NEGOCIA CON LOS ARTISTAS\n";
	
	else 
		cout << ans << "\n";
}

int main() {
	int casos;
	cin >> casos;
	for (int i = 0; i < casos; i++)
		resuelveCaso();
	return 0;
}