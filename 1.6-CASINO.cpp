#include <iostream>
#include <vector>
using namespace std;

bool disperso(const vector<int>& nums, int ini, int fin, int k) {
	if (ini == fin) 
		return true;
	else if (fin - ini == 1) 
		return abs(nums[fin] - nums[ini]) >= k;

	int mid = ini + (fin - ini) / 2;
	return disperso(nums, ini, mid, k) && disperso(nums, mid+1, fin, k) && abs(nums[fin]-nums[ini])>=k;
}

bool resuelveCaso() {
	int n;
	if (!(cin >> n)) return false;

	int k;
	cin >> k;

	vector<int> nums(n); 
	for (int i = 0; i < n; i++)
		cin >> nums[i];

	if (disperso(nums, 0, n - 1, k))
		cout << "SI\n";
	else
		cout << "NO\n";

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}
