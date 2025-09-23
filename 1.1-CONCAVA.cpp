#include <iostream>
#include <vector>
using namespace std;

int encuentraMin(const vector<int>& nums, int ini, int fin) {
	if (ini == fin)
		return nums[ini];

	else if (fin - ini == 1)
		return min(nums[fin], nums[ini]);

	int mid = ini+(fin-ini) / 2;
	if (nums[mid] < nums[mid - 1])
		return encuentraMin(nums, mid, fin);
	else
		return encuentraMin(nums, ini, mid - 1);	
}


bool resuelveCaso() {
	int n;
	if (!(cin >> n)) return false;

	vector<int> nums(n);
	for (int i = 0; i < n; i++)
		cin >> nums[i];

	cout << encuentraMin(nums, 0, n-1) << "\n";

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}