#include <iostream>
#include <vector>
using namespace std;

int contar(const vector<int>& nums, int ini, int fin) { //devuelve cantidad de números pares en una secuencia
	int cont = 0;
	for (int i = ini; i < fin+1; i++) {
		if (nums[i] % 2 == 0) cont++;
	}
	return cont;
}

bool caucasico(const vector<int>& nums, int ini, int fin) {
	if (fin - ini <= 3)
		return true;

	int mid = ini + (fin - ini) / 2;
	if (abs(contar(nums, ini, mid) - contar(nums, mid + 1, fin)) <= 2)
		return caucasico(nums, ini, mid) && caucasico(nums, mid + 1, fin);
	else
		return false;
}

bool resuelveCaso() {
	int n;
	cin >> n;

	if (n == 0)
		return false;	

	vector<int> nums(n);
	for (int i = 0; i < n; i++) cin >> nums[i];

	if (caucasico(nums, 0, n-1)) cout << "SI\n";
	else cout << "NO\n";

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}