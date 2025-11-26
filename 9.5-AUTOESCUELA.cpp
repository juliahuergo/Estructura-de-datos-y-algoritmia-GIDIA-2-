//HECHO POR EL PROFESOR
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <set>
#include <list>
using namespace std;

using Alumno = string;
using Profesor = string;

struct AlumnoInfo {
	Profesor profesor;
	int puntuacion;
};

class Autoescuela {
public:
	Autoescuela() {}

	void alta(Alumno A, Profesor P) { // O(log(a))
		if (!alumnos.contains(A)) {
			alumnos[A] = { P,0 };
			profesores[P].insert(A); //coste log(a)
			/*o hacer: alumnos[A].profesor = P;
			alumnos[A].puntuacion = 0;*/
		}
		else if(alumnos[A].profesor != P){
			profesores[alumnos[A].profesor].erase(A);
			alumnos[A].profesor = P;
			profesores[P].insert(A);
		}
	}

	bool es_alumno(Alumno A, Profesor P) { // O(1)
		return alumnos[A].profesor == P;
	}

	int puntuacion(Alumno A) const { // O(1)
		if (!alumnos.contains(A))
			throw domain_error("El alumno A no esta matriculado");

		return alumnos.at(A).puntuacion; //con los corchetes la función no puede ser const
	}


	void actualizar(Alumno A, int N) {// O(1)
		if (!alumnos.contains(A))
			throw domain_error("El alumno A no esta matriculado");

		alumnos[A].puntuacion += N;
		
	}

	list<Alumno> examen(Profesor P, int N) { // O(a)
		list<Alumno> resul; 
		for (Alumno A : profesores[P]) { // a vueltas
			if (alumnos[A].puntuacion >= N) //coste constante
				resul.push_back(A);
		}
		return resul;
		
		/*LENTA CON VECTOR: alog(a) por el sort (si no se pone tamaño suficentemente grande puede llamar a redimensionar --> coste cuadrático
		vector<Alumno> resul(alumnos.size());
		for (auto[a, info] : alumnos) { //a vueltas
			if (es_alumno(a, P) && puntuacion(a) >= N)
				resul.insert(a);
		}

		sort(resul.begin(), resul.end()) antes del return
		return resul;*/
	}

	void aprobar(Alumno A) { // O(logA)
		if (!alumnos.contains(A)) 
			throw domain_error("El alumno A no esta matriculado");

		profesores[alumnos[A].profesor].erase(A); //coste logarítmico
		alumnos.erase(A); //coste constante
	}


private:
	unordered_map<Alumno, AlumnoInfo> alumnos;  
	unordered_map<Profesor, set<Alumno>> profesores;
};

bool casoDePrueba() {
	Autoescuela escuela;
	string operacion;

	// Leemos la primera operación del caso
	if (!(cin >> operacion)) return false; // fin de la entrada total

	while (operacion != "FIN") {
		try {
			if (operacion == "alta") {
				Alumno A;
				Profesor P;
				cin >> A >> P;
				escuela.alta(A, P);
			}
			else if (operacion == "es_alumno") {
				Alumno A;
				Profesor P;
				cin >> A >> P;
				if (escuela.es_alumno(A, P))
					cout << A << " es alumno de " << P << '\n';
				else
					cout << A << " no es alumno de " << P << '\n';
			}
			else if (operacion == "puntuacion") {
				Alumno A;
				cin >> A;
				int puntos = escuela.puntuacion(A);
				cout << "Puntuacion de " << A << ": " << puntos << '\n';
			}
			else if (operacion == "actualizar") {
				Alumno A;
				int N;
				cin >> A >> N;
				escuela.actualizar(A, N);
			}
			else if (operacion == "examen") {
				Profesor P;
				int N;
				cin >> P >> N;
				list<Alumno> lista = escuela.examen(P, N);
				cout << "Alumnos de " << P << " a examen:\n";
				for (const Alumno& a : lista) {
					cout << a << '\n';
				}
			}
			else if (operacion == "aprobar") {
				Alumno A;
				cin >> A;
				escuela.aprobar(A);
			}
		}
		catch (domain_error&) {
			// Cualquier operación que lance error imprime solo ERROR
			cout << "ERROR\n";
		}

		// Leemos la siguiente operación del caso
		if (!(cin >> operacion)) return false;
	}

	// Al encontrar FIN, cerramos el caso
	cout << "---\n";
	return true;
}

int main() {
	while (casoDePrueba());
	return 0;
}