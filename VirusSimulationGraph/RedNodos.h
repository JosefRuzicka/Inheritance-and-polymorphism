#pragma once

#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <memory>
using namespace std;

#include "Nodo.h"
#include "GrafoAbst.h"

class RedNodos {
    // Representa una red de nodos.

public:
    /* CONSTRUCTORES */

    // DADOS:
    // N la cantidad de vértices o nodos.

    // REQ: 0 < p < 1.
    // Construye un RedNodos con N vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando p. Esto
    // implica que la probabilidad de que un arco exista entre 
    // cualesquiera dos vértices es igual a p.
    RedNodos(int N, double p);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices se identifican con números de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    // NOTA: todos los vértices son inicializados con Nodo().
    RedNodos(ifstream& archivo);

    // Construye una copia idéntica a orig.
    RedNodos(const RedNodos& orig);

    // Destructor
    ~RedNodos();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el RedNodos.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna la cantidad de vértices adyacentes a idVrt en el RedNodos.    
    int obtCntVrtAdys(int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna una copia del nodo con índice idVrt para que *this NO pueda ser modificado.
    // NOTA: la copia queda en el HEAP.
    Nodo operator[](int idVrt) const;

    // EFE: retorna el total de vértices en el RedNodos.
    int obtTotVrt() const;

    // EFE: retorna el total de nodos susceptibles en la red.
    int obtTotVrtSusceptibles() const;

    // EFE: retorna el total de nodos infectados en la red.
    int obtTotVrtInfectados() const;

    // EFE: retorna el total de nodos resistentes en la red.
    int obtTotVrtResistentes() const;

    // EFE: retorna el porcentaje de nodos susceptibles en la red.
    double obtPrcVrtSusceptibles() const;

    // EFE: retorna el porcentaje de nodos infectados en la red.
    double obtPrcVrtInfectados() const;

    // EFE: retorna el porcentaje de nodos resistentes en la red.
    double obtPrcVrtResistentes() const;

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    Nodo& operator[](int idVrt);

private:

    GrafoAbst red_nodos; // GrafoGnr especializado con Nodo
    static unique_ptr< Nodo > p_inicializador;
};

unique_ptr< Nodo > RedNodos::p_inicializador = unique_ptr< Nodo >(new Nodo());

RedNodos::RedNodos(int N, double p) : red_nodos(N, p, RedNodos::p_inicializador.get()) {

}

RedNodos::RedNodos(ifstream& archivo) : red_nodos(archivo, RedNodos::p_inicializador.get()) {

}

RedNodos::RedNodos(const RedNodos& orig) : red_nodos(orig.red_nodos) {

}

RedNodos::~RedNodos() {
    red_nodos.~GrafoAbst();
}

bool RedNodos::xstVrt(int idVrt) const {
    bool resultado = false;
    if (red_nodos.xstVrt(idVrt))
        resultado = true;
    return resultado;
}

bool RedNodos::xstAdy(int idVrtO, int idVrtD) const {
    bool resultado = false;
    if (red_nodos.xstAdy(idVrtO, idVrtD))
        resultado = true;
    return resultado;
}

void RedNodos::obtIdVrtAdys(int idVrt, vector< int >& rspRetornar) const {
    red_nodos.obtIdVrtAdys(idVrt, rspRetornar);
}

int RedNodos::obtCntVrtAdys(int idVrt) const {
    int resultado = red_nodos.obtCntVrtAdys(idVrt);
    return resultado;
}

Nodo RedNodos::operator[](int idVrt) const {
    return *((Nodo*)(&red_nodos[idVrt])->clonar());
}

int RedNodos::obtTotVrt() const {
    int resultado = red_nodos.obtTotVrt();
    return resultado;
}

int RedNodos::obtTotVrtSusceptibles() const {
    int contador = 0;
    for (int i = 0; i < red_nodos.obtTotVrt(); i++) {
        Nodo* nodo = ((Nodo*)(&red_nodos[i]));
        if (nodo->obtEstado() == Nodo::E::S)

            contador++;
    }
    return contador;
}

int RedNodos::obtTotVrtInfectados() const {
    int contador = 0;
    for (int i = 0; i < red_nodos.obtTotVrt(); i++) {
        Nodo* nodo = ((Nodo*)(&red_nodos[i]));
        if (nodo->obtEstado() == Nodo::E::I)

            contador++;
    }
    return contador;
}

int RedNodos::obtTotVrtResistentes() const {
    int contador = 0;
    for (int i = 0; i < red_nodos.obtTotVrt(); i++) {
        Nodo* nodo = ((Nodo*)(&red_nodos[i]));
        if (nodo->obtEstado() == Nodo::E::R)

            contador++;
    }
    return contador;
}

double RedNodos::obtPrcVrtSusceptibles() const {
    double resultado = double(obtTotVrtSusceptibles()) / double(obtTotVrt());
    return resultado;
}

double RedNodos::obtPrcVrtInfectados() const {
    double resultado = double(obtTotVrtInfectados()) / double(obtTotVrt());
    return resultado;
}

double RedNodos::obtPrcVrtResistentes() const {
    double resultado = double(obtTotVrtResistentes()) / double(obtTotVrt());
    return resultado;
}

Nodo& RedNodos::operator[](int idVrt){
    
    return *((Nodo*)(&red_nodos[idVrt]));
}


