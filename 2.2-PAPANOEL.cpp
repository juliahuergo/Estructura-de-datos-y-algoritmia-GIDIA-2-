#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void backtrack(const vector<vector<int>>& juguetes, int m, int n, int k, 
	int suma, int& ans, vector<bool>& contadores, const vector<int>& optima) {
	
	//CASO BASE
	if (k == n) { //ya se han seleccionado n juguetes
		ans = max(ans, suma);
		return;
	}

	
	else {
		for (int i = 0; i < m; i++) {
			if (!contadores[i]) { //el juguete todavía no ha sido escogido
				contadores[i] = true; //marcar
				if(suma + juguetes[k][i] + optima[k] > ans )
					backtrack(juguetes, m, n, k+1, suma+juguetes[k][i], ans, contadores, optima); 
				contadores[i] = false; //desmarcar
			}
		}
	}
}

//M = COLUMNAS
//N = FILAS

bool resuelveCaso() {
	int m; //número de juguetes = columnas
	if (!(cin >> m))
		return false;
	int n; //número de niños = filas
	cin >> n;

	vector<vector<int>> juguetes(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cin >> juguetes[i][j];
	}

	

	vector<bool> contadores(m, false);
	
	vector <int> maximos(m); // maxima satisfaccion de cada juguete
	for (int i = 0; i < n; i++) {
		int ans = INT_MIN;
		for (int j = 0; j < m; j++) {
			if (juguetes[i][j] > ans)
				ans = juguetes[i][j];
		}
		maximos[i] = ans;
	}

	
	vector<int> optima(m, 0); //satisfaccion del mejor juguete para cada niño 
	int i = m - 2;
	while (i >= 0) {
		optima[i] = maximos[i + 1] + optima[i + 1];
		--i;
	}
		
	int ans = 0;
	backtrack(juguetes, m, n, 0, 0, ans, contadores, optima);

	cout << ans << "\n";
	return true; 
}

int main() {
	while (resuelveCaso());
	return 0;
}
