#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool minMayor(const vector<int>& nums, int ini, int mid, int fin) {
	bool answer = true;

	auto start = nums.begin() + ini;
	auto med = nums.begin() + mid + 1;
	auto end = nums.begin() + fin + 1;

	int miniI = *min_element(start, med);
	int maxiI = *max_element(start, med);

	int maxiD = *max_element(med, end);
	int miniD = *min_element(med, end);

	return maxiD >= maxiI && miniI <= miniD;
}

bool ordenado(const vector<int>& nums, int ini, int fin) {
	if (fin - ini <= 0)
		return true;
	if (fin - ini == 1) // 2 elementos
		return nums[fin] >= nums[ini];

	// 4 o más elementos - comprobar que se cumpla para ese y llamar recursivamente
	int mid = ini + (fin - ini) / 2;
	return minMayor(nums, ini, mid, fin)
		&& ordenado(nums, ini, mid)
		&& ordenado(nums, mid + 1, fin);

}

bool resuelveCaso() {
	vector<int> nums;
	int aux;
	cin >> aux;
	if (aux == 0) return false;

	while (aux != 0) {
		nums.push_back(aux);
		cin >> aux;
	}

	if (ordenado(nums, 0, nums.size() - 1)) cout << "SI\n";
	else cout << "NO\n";
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}