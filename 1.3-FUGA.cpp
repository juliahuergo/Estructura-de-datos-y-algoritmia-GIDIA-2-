#include <iostream>
#include <vector>

using namespace std;

bool esta(const vector<int>& v, int ini, int fin, int x) {
	if (ini > fin) 
		return false;  

	int mid = ini + (fin - ini) / 2;
	if (v[mid] == x) 
		return true;

	if (v[mid] < x)  
		return esta(v, mid + 1, fin, x); 

	else             
		return esta(v, ini, mid - 1, x); 
}


void resuelveCaso() {
	char iniL, finL;
	cin >> iniL >> finL;

	int ini = iniL - 'a';  
	int fin = finL - 'a'; 

	int n = fin - ini;

	vector<int> nums(n);
	char aux;
	for (int i = 0; i < n; i++) {
		cin >> aux;
		nums[i] = aux - 'a'; // guardamos los NUMEROS que corresponden a las letras
	}

	for (int i = ini; i <= fin; i++) {
		if (!esta(nums, 0, n-1, i)) 
			cout << char(i + 'a') << "\n";
	}

}

int main() {
	int casos;
	cin >> casos;

	for (int i = 0; i < casos; i++)
		resuelveCaso();

	return 0;
}