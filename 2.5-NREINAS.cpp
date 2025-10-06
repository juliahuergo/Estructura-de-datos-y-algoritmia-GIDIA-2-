#include <iostream>
#include <vector>
using namespace std;

//Algoritmo: bucle sobre las filas (reina por fila), luego por las columnas comprobando que no haya en las diagonales ni en vertical

void backtrack(vector<bool>& columnas, vector<bool>& diag, vector<bool>& antidiag, int k, int N, int& ans) { //k == fila
	if (k == N) //N reinas colocadas - k hace de fila del tablero (iterar sobre las filas)
		ans++;
	
	else { //faltan reinas por colocar
		for (int i = 0; i < N; i++) { //iteramos sobre las columnas
			int di = k + i;
			int ai = k - i + (N - 1);
			if (!columnas[i] && !diag[di] && !antidiag[ai]) { //no hay reina en la columna i
				columnas[i] = diag[di] = antidiag[ai] =  true; //MARCAR
				backtrack(columnas, diag, antidiag, k + 1, N, ans);
				columnas[i] = diag[di] = antidiag[ai] = false; //DESMARCAR
			}
		}
	}
}

void resuelveCaso() {
	int N;
	cin >> N;
	
	vector<bool> columnas(N, false); //false = en esa columnas no hay reinas
	vector<bool> diag(2 * N - 1, false);
	vector<bool> antidiag(2 * N - 1, false);

	int ans = 0;
	backtrack(columnas, diag, antidiag, 0, N, ans);

	cout << ans << "\n";
}

int main() {
	int casos;
	cin >> casos;
	for (int i = 0; i < casos; i++)
		resuelveCaso();
	return 0;
}