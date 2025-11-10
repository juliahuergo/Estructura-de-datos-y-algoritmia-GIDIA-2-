#include <iostream>
#include <deque>

using namespace std;

bool casoDePrueba() {
	int N, tam;
	cin >> N;

	if (!cin)
		return false;
	
	cin >> tam;

	deque<pair<int, int>> wo; // (indice, valor)

	int entrada;
	for (int i = 0; i < N; i++) { 
		cin >> entrada; 
		
		while (!wo.empty() && wo.front().first <= i - tam) {
			wo.pop_front();
		}
				

		while (!wo.empty() && wo.back().second <= entrada) {
			wo.pop_back();
		}

		wo.push_back({ i, entrada }); 

		if (i >= tam - 1) {
			cout << wo.front().second;
			if (i != N - 1)
				cout << " ";
		}
	}
	cout << "\n";
	return true;
}

int main() {
	while (casoDePrueba());
	return 0;
}