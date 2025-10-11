#include <iostream>
#include <vector>
using namespace std;

int suma(int ini, int fin, int fila, const vector<vector<int>>& nums) { //suma del intervalo cerrado [ini, fin]
	int cont = 0;
	for (int i = ini; i <= fin; i++) {
		cont += nums[fila][i];
	}
	return cont;
}

bool degradado(int ini, int fin, int fila, const vector<vector<int>>& nums) {
	if (ini >= fin)
		return true;
	
	if (fin - ini == 1) //sólo dos elementos
		return nums[fila][fin] > nums[fila][ini];
	else { //más de dos elementos
		int mid = ini + (fin - ini) / 2;

		if (suma(ini, mid, fila, nums) < suma(mid + 1, fin, fila, nums))
			return degradado(ini, mid, fila, nums) && degradado(mid + 1, fin, fila, nums);

		else
			return false;
	}
}


bool casoDePrueba() {
	int n;

	if (!(cin >> n))
		return false;
	
	int m;
	cin >> m;

	vector<vector<int>> nums(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> nums[i][j];
		}
	}

	int i = 0;
	while (i < n && degradado(0, m-1, i, nums))
		i++;

	if (i == n)
		cout << "SI\n";
	else
		cout << "NO\n";
	
	return true;

}

int main() {
	while (casoDePrueba());
	return 0;
}