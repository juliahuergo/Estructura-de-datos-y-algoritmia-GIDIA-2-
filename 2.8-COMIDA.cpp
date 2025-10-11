#include <iostream>
#include <vector>

using namespace std;

void backtrack(const vector<vector<float>>& distancias, int k, int n, 
	int m, int& ans, int suma, const vector <vector<int>>& allegados,
	vector<bool>& personasSentadas, vector<bool>& plazasCogidas, 
	vector<int>& plazaDe) {
	
	if (k == m) //sentados a todos los comensales
		ans = max(ans, suma);

	else {
		personasSentadas[k] = true;
		for (int i = 0; i < n; i++) if (!plazasCogidas[i]) {
			//MARCAR
			plazasCogidas[i] = true;
			plazaDe[k] = i;

			bool posibleSentarlos = true;
			int delta = 0;

			for (int j = 0; j < m; j++) if (personasSentadas[j] && j != k) {
				
				if (allegados[k][j] == 0) {
					if (distancias[plazaDe[k]][plazaDe[j]] < 2)
						posibleSentarlos = false;
				}
				else { //ni se suma ni se imposibilita el planteamiento
					if (distancias[plazaDe[k]][plazaDe[j]] < 2)
						delta++;
				}
			}

			//Se sabe que que es posible sentar a k en plaza i (no rompe ninguna regla de distancia con la gente ya sentada)
			if (posibleSentarlos)
				backtrack(distancias, k + 1, n, m, ans, suma + delta, allegados, personasSentadas, plazasCogidas, plazaDe);

			//DESMARCAR
			plazasCogidas[i] = false;
			plazaDe[k] = -1;
		}
		personasSentadas[k] = false;
	}
}

void casoDePrueba() {
	int n, m;
	cin >> n >> m;

	vector<vector<float>> distancias(n, vector<float>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> distancias[i][j];
	}

	vector <vector<int>> allegados(m, vector<int>(m));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++)
			cin >> allegados[i][j];
	}

	int ans = 0; //nº de parejas de allegados a menos de 2m

	vector<bool> personasSentadas(m, false); //para marcar a las personas a las que ya hemos sentado
	vector<bool> plazasCogidas(n, false); 
	vector<int> plazaDe(m, -1);

	backtrack(distancias, 0, n, m, ans, 0, allegados, personasSentadas, plazasCogidas, plazaDe);

	if (ans != 0)
		cout << "PAREJAS " << ans << "\n";
	else
		cout << "CANCELA\n";
}

int main() {
	int casos;
	cin >> casos;
	for (int i = 0; i < casos; i++) 
		casoDePrueba();
	return 0;
}