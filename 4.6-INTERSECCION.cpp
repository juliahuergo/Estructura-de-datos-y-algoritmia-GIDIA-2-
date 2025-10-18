/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
    Introduce aquí los nombres de los componentes del grupo:

    Componente 1: Julia Huergo
    Componente 2:
  */
  //@ </answer>


#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const int& elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const int& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    int& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const int& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    int& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const int& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    int& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }


    // Nuevo método
    void add_to(int index, int val);
    void partition(int pivote);
    void my_display(std::ostream& out) const;
    void interseccion(ListLinkedDouble& other);

    void intersect(const ListLinkedDouble& other); //4.6


private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);

    // Nuevos métodos
    static void attach(Node* node, Node* before);
    static void detach(Node* node);
};

ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedDouble::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

void ListLinkedDouble::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

void ListLinkedDouble::my_display(std::ostream& out) const {
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << " " << current->value;
            current = current->next;
        }
    }
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
    l.display(out);
    return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

void ListLinkedDouble::attach(Node* node, Node* after) {
    node->next = after;
    node->prev = after->prev;
    after->prev = node;
    node->prev->next = node;
}

void ListLinkedDouble::detach(Node* node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = node->prev = nullptr;
    //si hace falta delete, hacerlo fuera de esta función
}

void ListLinkedDouble::intersect(const ListLinkedDouble& other) { //coste lineal: se recorre en un bucle los elementos de la lista y haciendo operaciones constantes por iteración
    Node* current = head->next;
    Node* curOther = other.head->next;

    while (current != head && curOther != other.head) {
        if (current->value < curOther->value) {
            //quitamos elemento de this
            //avanzamos puntero de this
            Node* sig = current->next;
            detach(current);
            current = sig; 
        }
        else if (current->value == curOther->value) {
            //dejamos elemento en current
            //avanzamos puntero de this
            //avanzamos puntero de curOther
            current = current->next;
            curOther = curOther->next;
        }
        else { //current->value > curOther->value
            //avanzamos puntero de curOther
            curOther = curOther->next;
        }
    }

    //Opción 1: this y other no tienen más elementos -> fin 
    //Opción 2: sólo quedan elementos en other -> no aparecen en this -> fin
    //Opción 3: sólo quedan elementos en this -> no aparecen en other -> hay que eliminarlos de this:

    while (current != head) {
        Node* sig = current->next;
        detach(current);
        current = sig;
    }
}

bool tratar_caso() {

    ListLinkedDouble lista, lista2;

    int N;
    cin >> N;
    int aux;
    for (int i = 0; i < N; i++) {
        cin >> aux;
        lista.push_back(aux);
    }

    int M;
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> aux;
        lista2.push_back(aux);
    }

    //Hacer operación
    lista.intersect(lista2);
    lista.display(std::cout);
    std::cout << endl;
    return true;
}

int main() {
    int casos;
    cin >> casos;

    for (int i = 0; i < casos; i++)
        tratar_caso();

    return 0;
}

//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>