#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
using namespace std;

void backtrack(const vector<vector<int>>& gustos, int n, int a, int t, int suma, int& ans, int k, vector<int>& contadores, const vector<int>& optima) {

	if (k == n) { //ya se han asignado todas las tareas
		ans = max(ans, suma);
		return; 
	}

	else {
		//Probamos todas las parejas posibles - si no sería enfoque greedy - a corto plazo
		for (int i = 0; i < a; i++) if (contadores[i] < t) {
			for (int j = i + 1; j < a; j++) if (contadores[j] < t) {
				contadores[i]++; // MARCAMOS AMBOS ALUMNOS
				contadores[j]++;
				if(suma + gustos[i][k] + gustos[j][k] + optima[k] > ans) 
					/*Comprobamos con estimación : si pudiésemos a partir de la suma actual sólo sumar el máximo de satisfacciones y aún así no superásemos el ans 
					actual, no exploramos esa rama*/
					backtrack(gustos, n, a, t, suma + gustos[i][k] + gustos[j][k], ans, k + 1, contadores, optima);
				contadores[i]--; // DESMARCAMOS AMBOS ALUMNOS
				contadores[j]--;
			}
		}
		
	}
}

bool casoDePrueba() {
	int n, a, t;
	cin >> n >> a >> t; //num tareas, num alumnos, max tareas / alumno
	//dos alumnos por tarea

	if (n == 0 && a == 0 && t == 0)
		return false;

	vector<vector<int>> gustos(a, vector<int>(n));
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < n; j++)
			cin >> gustos[i][j];
	}


	int ans = 0;
	vector<int> contadores(a, 0); // actualiza el número de tareas realizadas por alumno
	
	vector<int>maximos(n); //suma de las dos satisfacciones maximas para cada tarea para las tareas que quedan
	for (int i = 0; i < n; i++) { //cada tarea
		int max1 = 0, max2 = 0;
		for (int j = 0; j < a; j++) { //cada alumno
			if (gustos[j][i] > max1) {
				max2 = max1;
				max1 = gustos[j][i];
			}
			else if (gustos[j][i] > max2) {
				max2 = gustos[j][i];
			}
		}
		maximos[i] = max1 + max2;
	}

	vector<int> optima(n, 0);
	int pos = n - 2;
	while (pos >= 0) {
		optima[pos] = maximos[pos + 1] + optima[pos + 1];
		pos--;
	}

	backtrack(gustos, n, a, t, 0, ans, 0, contadores, optima); 

	cout << ans << "\n";

	return true;

}


int main() {
	while (casoDePrueba());
	return 0;
}