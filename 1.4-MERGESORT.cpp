#include <iostream>
#include <vector>
using namespace std;

void combina(vector<int>& nums, int ini, int mid, int fin) {
	int nl = mid - ini;
	int nr = fin - mid;

	vector<int> vl;
	vector<int> vr;

	for (int i = 0; i < nl; i++) //mete en vl todos los nº de la primera mitad
		vl.push_back(nums[ini + i]);

	for (int j = 0; j < nr; j++) //mete en vr los nº de la segunda mitad
		vr.push_back(nums[mid + j]); 

	int i = 0, j = 0;
	for (int k = ini; k < fin; k++) {
		if (j >= nr || (i < nl && vl[i] <= vr[j])) {
			nums[k] = vl[i];
			i = i + 1;
		}
		else {
			nums[k] = vr[j];
			j = j + 1;
		}
	}
}

void ordena(vector<int>& nums, int ini, int fin) {	
	if (ini < fin - 1) {
		int mid = ini + (fin - ini) / 2;
		ordena(nums, ini, mid);
		ordena(nums, mid, fin);
		combina(nums, ini, mid, fin);
	}
}

void resuelveCaso() {
	int N;
	cin >> N;

	vector<int> nums(N);
	for (int i = 0; i < N; i++)
		cin >> nums[i];

	ordena(nums, 0, N);

	for (int i = 0; i < N; i++) {
		if (i) cout << " ";
		cout << nums[i];
	}
		
	
	
	cout << "\n";
}

int main() {
	int casos;
	cin >> casos;
	for (int i = 0; i < casos; i++)
		resuelveCaso();
	return 0;
}