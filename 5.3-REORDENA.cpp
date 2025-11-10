#include <deque>
#include <iostream>

using namespace std;

bool casoDePrueba() {
	int N;
	cin >> N;

	if (N == 0)
		return false;

	deque<int> negativos;
	deque<int> global;

	int entrada;
	for (int i = 0; i < N; i++) {
		cin >> entrada;
		if (entrada < 0)
			negativos.push_back(entrada);
		else
			global.push_back(entrada);
	}

	while (!negativos.empty()) {
		cout << negativos.back() << " ";
		negativos.pop_back(); 
	} 

	while (!global.empty()) {
		if (size(global) != 1)
			cout << global.front() << " ";
		else
			cout << global.front();
		global.pop_front();
	}

	cout << "\n";

	return true;
}

int main() {
	while (casoDePrueba());
	return 0;
}