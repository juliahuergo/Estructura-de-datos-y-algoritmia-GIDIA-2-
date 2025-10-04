#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;

void backtrack(const vector<vector<int>>& precios, int m, int n, 
	int col, int suma, int& ans, vector<int>& contadores) {

	//CASO BASE:
	if (col == n) { //ya se ha escogido un precio por productos
		ans = min(ans, suma);
		return;
	}

	if (suma >= ans) //no seguir por esta rama si ya hay otra mejor 
		return;

	else { //no es necesario poner else - por claridad
		for (int j = 0; j < m; j++) {
			if (contadores[j] < 3) {
				contadores[j]++; //marcar
				backtrack(precios, m, n, col+1, suma+precios[j][col], ans, contadores);
				contadores[j]--; //desmarcar
			}
		}
	}
}

void resuelveCaso() {
	int m, n;
	cin >> m >> n;

	vector<vector<int>> precios(m, vector<int>(n));  // bc vector<type>(size, value)
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> precios[i][j];
		}
	}

	int ans = INF;

	vector <int> contadores(m, 0);
	backtrack(precios, m, n, 0, 0, ans, contadores);

	if (ans == INF)
		cout << "”Sin solucion factible\n";
	
	else
		cout << ans << "\n";
}


int main() {
	int casos;
	cin >> casos;
	for (int i = 0; i < casos; i++)
		resuelveCaso();
}
//vector de contadores: un contador por supermercado 
//TMB SE PUEDE USAR UN VECTOR CON LOS PRECIOS MÍNIMOS DE LOS PRODUCTOS PARA PARAR DE EXPLORAR UNA RAMA CUANDO SU SUMA MINIMA (AÑADIENDO EL COSTE ESTIMADO DE
// LOS PRODUCTOS QUE QUEDAN POR AÑADIR) YA SUPERA ANS.