#include <iostream>
using namespace std;
#include <vector>

void backtrack(const vector<vector<int>>& canciones, int k, const int capacidad, int& ans, 
	int A, int B, int N, const vector<int>& maximo, int suma) {
	if (k == N) { // ya se han revisado las N canciones
		ans = max(ans, suma);
	}

	else {
		//PODA - OP.1
		if (suma + maximo[k] <= ans)
			return;

		if (canciones[k][0] + A <= capacidad) //meter en cara A
			backtrack(canciones, k+1, capacidad, ans, A + canciones[k][0], B, N, maximo, suma + canciones[k][1]);

		if (B != A && canciones[k][0] + B <= capacidad) //meter en cara B (solo si no entra en la A)
			backtrack(canciones, k+1, capacidad, ans, A, B + canciones[k][0], N, maximo, suma + canciones[k][1]);

		backtrack(canciones, k+1, capacidad, ans, A, B, N, maximo, suma);

	}
}

//CANCIONES NI SE REPITEN NI SE CORTAN AL FINAL D UNA CARA O CINTA COMPLETA
bool resuelveCaso() {
	int N; 
	cin >> N;

	if (N == 0)
		return false;

	int capacidad;
	cin >> capacidad;

	vector<vector<int>> canciones(N, vector<int>(2));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2; j++)
			cin >> canciones[i][j];
	}

	int ans = 0;
	int A = 0, B = 0;

	vector<int> maximo(N+1, 0);
	for (int i = N - 1; i >= 0; --i) {
		maximo[i] = maximo[i + 1] + canciones[i][1];
	}

	backtrack(canciones, 0, capacidad, ans, 0, 0, N, maximo, 0);

	cout << ans << "\n";


	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}


/*
* Nº canciones
* Capacidad de una cara (hay dos - no puede quedarse una canción
* a medias a final de una cara)
* 
* Duración _ Puntuación 
*/