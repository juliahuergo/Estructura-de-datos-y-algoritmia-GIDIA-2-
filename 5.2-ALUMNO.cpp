#include <deque>
#include <iostream>
using namespace std;

bool casoDePrueba() {
	int N, M;
	cin >> N >> M;

	if (N == 0 && M == 0)
		return false;

	deque<int> corro;

	int cont = 0;

	for (int i = 1; i < N + 1; i++) {
		corro.push_back(i); //numerados en orden del 1 al N
	}

	while (corro.size() > 1) {
		if (cont < M) { //muevo el elemento hacia atrás
			int elem = corro.front();
			corro.pop_front();
			corro.push_back(elem);
			cont++;
		}
		else { //quito el elemento
			corro.pop_front();
			cont = 0;
		}
	}

	cout << corro.front() << "\n";

	return true;
}

int main() {
	while (casoDePrueba());
	return 0;
}