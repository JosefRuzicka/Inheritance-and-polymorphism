#pragma once

#include <random>
#include <ostream>
#include "string"
using namespace std;

#include "Objeto.h"

class Nodo : public Objeto {
public:
    // Representa un nodo de la red de computadores sobre la cual se aplica la simulación
    // de dispersión de virus.

    /* TIPO PÚBLICO DE ESTADOS DE VÉRTICES */
    enum E { // representa el tipo de estados de la red de infección
        S, // representa un vértice susceptible de infección
        I, // representa un vértice infectado
        R, // representa un vértice resistente
    };

    Nodo();
    Nodo(const Nodo& orig);
    virtual ~Nodo();

    // EFE: retorna el valor del estado del nodo.
    E obtEstado() const;

    // MOD: *this.
    // EFE: cambia el estado del nodo a ne.
    void modEstado(E ne);

    // EFE: modifica *this con los valores de n.
    Nodo operator=(const Nodo& n);

    /* CLONADOR DEBE REDEFINIR AL VIRTUAL PURO */

    //EFE: realiza la misma función del constructor de copias, pero a diferencia del constructor
    //	   este método sí permite el enlace dinámico, el constructor sólo permite el enlace estático.
    // NOTA: la copia queda en el HEAP.
    virtual Objeto* clonar() const override;

    /* SERIALIZADOR DEBE REDEFINIR AL VIRTUAL PURO */

    // EFE: genera una hilera que representa el estado de *this.
    // RET: "Susceptible" si estado == S.
    // RET: "Infectado" si estado == I.
    // RET: "Resistente" si estado == R.
    virtual string toString() const override;

private:
    E estado; // representa el estado del nodo
};

Nodo::Nodo() : estado(S) {
}

Nodo::Nodo(const Nodo& orig) : estado(orig.estado) {
}

Nodo::~Nodo() {
}

Nodo::E Nodo::obtEstado() const {
    return estado;
}

void Nodo::modEstado(E ne) {
    estado = ne;
}

Nodo Nodo::operator=(const Nodo& n) {
    this->modEstado(n.estado);
    return *this;
}

Objeto* Nodo::clonar() const {
    Objeto* puntero = new Nodo();
    *puntero = *this;
    return puntero;
}

string Nodo::toString() const {
   
    string resultado;
    if (this->obtEstado() == Nodo::I) {
        resultado = "Infectado";
    }
    else if (this->obtEstado() == Nodo::S) {
        resultado = "Susceptible";
    }
    else if (this->obtEstado() == Nodo::R) {
        resultado = "Resistente";
    }
    return resultado;
}
