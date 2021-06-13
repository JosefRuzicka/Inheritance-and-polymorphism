#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

#include "Objeto.h"

class GrafoAbst
{
    /* Representa una red compleja polimórfica con vértices de tipo derivado de Objeto.
    *  Ver Objeto para los requerimientos sobre las clases derivadas.
    */

public:
    /* CONSTRUCTORES */

    // Dado N como la cantidad de vértices.

    // REQ: 0 < p < 1 && 0 < N.
    // Construye un GrafoAbst con N vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando p. Esto
    // implica que la probabilidad de que un arco exista entre 
    // cualesquiera dos vértices es igual a p.
    // NOTA: Inicializa los vértices con copias del objeto apuntado por "po".
    GrafoAbst(int N, double p, Objeto* po);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices se identifican con números de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1 (N > 0).
    // NOTA: Inicializa los vértices con copias del objeto apuntado por "po".
    GrafoAbst(ifstream& archivo, Objeto* po);

    // Construye una copia idéntica a orig.
    // NOTA: se clonan todos los objetos apuntados desde los vértices de orig.
    GrafoAbst(const GrafoAbst& orig);

    // Destructor
    ~GrafoAbst();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el GrafoAbst.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna la cantidad de vértices adyacentes a idVrt en el GrafoAbst.    
    int obtCntVrtAdys(int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna una copia del vértice con índice idVrt para que *this NO pueda ser modificado.
    // NOTA: la copia queda en el HEAP.
    Objeto& operator[](int idVrt) const;

    // EFE: retorna el total de arcos o adyacencias en el GrafoAbst.
    int obtTotArc() const;

    // EFE: retorna el total de vértices en el GrafoAbst.
    int obtTotVrt() const;

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    Objeto& operator[](int idVrt);

private:

    struct Vrt {
        Objeto* t;
        list< int > lstAdy;

        // constructor estándar de Vrt
        Vrt() : t(0), lstAdy() {};

        // constructor con dato de vértice, OJO: se clona el objeto!!
        Vrt(const Objeto* obj_p) : t(obj_p->clonar()), lstAdy() {};

        // constructor de copias de Vrt, OJO: se clona el objeto!!
        Vrt(const Vrt& vrt) : t(vrt.t->clonar()), lstAdy(vrt.lstAdy) {};

        ~Vrt() { delete t; } // debe liberarse la memoria asignada dinamicamente!!!
    };

    vector< Vrt > vectorVrts; // vector de vértices
};

GrafoAbst::GrafoAbst(int N, double p, Objeto* po) {
    // crear N nodos.
    vectorVrts.resize(N, Vrt(po));
    int randomNum;
    //crear adys de cada nodo.
    for (int i = 0; i < N; i++) {
        for (int n = i; n < N; n++) {
            //este if para que un nodo no sea ady con él mismo
            if (n != i) {
                randomNum = rand() % 10 + 1;
                if (randomNum * 0.10 <= p) {
                    vectorVrts.at(i).lstAdy.push_back(n);
                    vectorVrts.at(n).lstAdy.push_back(i);
                }
            }
        }
    }
}

GrafoAbst::GrafoAbst(ifstream& archivo, Objeto* po) {
    string delimiter = ", ";
    string cantidad;
    int numeroCantidad;
    string token[13];
    string linea;

    archivo.open("red_peq.txt", ios::in);// Abrimos el archivo para leer.
    //Comprobamos si se abre correctamente.
    if (archivo.fail()) {
        exit(1);
    }
    //Leemos la primera linea para ver de que tamaño va a ser el vector.
    getline(archivo, cantidad);
    //La guardamos en un entero.
    numeroCantidad = stoi(cantidad);
    //Hacemos el vector del tamaño de la primera linea de el archivo.
    vectorVrts.resize((numeroCantidad), Vrt(po));

    //Recorremos el Archivo para crear las adyacencias
    for (int j = 1; j <= numeroCantidad; j++) {
        getline(archivo, linea);// lee cada linea del archivo
        //Vaciamos el arreglo token para ingresar nuevos valores de adyacencias 
        if (j > 1) {
            for (int c = 0; c < 13; c++) {
                token[c].clear();
            }
        }
        //Recorremos cada linea para guardar las respectivas adyancencias a cada vertice.
        for (int i = 1; i <= linea.length() + 1; i++) {
            int count = 1;
            int cierto = 1;
            //Revisamos si el archivo esta separado por comas o espacios
            if (linea.find(delimiter) != 0) {
                //Guardamos en token[i] lo que hay en la primera posicion separada por una coma del string linea.
                token[i] = linea.substr(0, linea.find_first_of(","));
                //Borramos lo que acabamos de guardar en token[i] del string linea, para seguir haciendo esto con todos los datos separados por comas del string linea.
                linea = linea.substr(linea.find_first_of(",") + 1);
            }
            else {
                //Guardamos en token[i] lo que hay en la primera posicion separada por una coma del string linea.
                token[i] = linea.substr(0, linea.find_first_of(" "));
                //Borramos lo que acabamos de guardar en token[i] del string linea, para seguir haciendo esto con todos los datos separados por comas del string linea.
                linea = linea.substr(linea.find_first_of(" ") + 1);
            }
            //Se quiere comparar cada posicion del token para no ingresar numeros repetidos al vector. 
            while (count != i)//No es necesario comparar si estamos en la primera posicion.
            {
                char c;
                c = token[i].at(0);
                //comprobamos que token[i] no sea un numero repetido en el arreglo, que no sea un espacio en blanco o que este vacio
                if (token[i] == token[count] || c == ' ' || token[i].empty()) {
                    //De cumplirse una de estas condiciones entonces ponemos nuestra variable cierto en cero para que no se ingrese al vector.
                    cierto = 0;
                    //Tambien se pone count en i para que deje de revisar y no entre mas en el while
                    count = i;
                }
                //De no cumplirse lo anterior seguimos revisando con cada posicion del token para que no haya ningun numero repetido.
                if (count < i) {
                    count++;
                }
            }
            // En caso de que la primera posicion este vacia
            count = 1;
            if (token[i].length() == 0) {
                cierto = 0;
            }
            //cierto es cero si alguna de las condiciones anteriores se cumplio, por lo tanto solo agregamos el numero al vector si cierto no fue modificado osea que sea igual a uno.
            if (cierto == 1) {
                vectorVrts.at(j - 1).lstAdy.push_back(stoi(token[i]));
            }

        }
    }
    archivo.close();
}

GrafoAbst::GrafoAbst(const GrafoAbst& orig) {
    this->vectorVrts = orig.vectorVrts;
}

GrafoAbst::~GrafoAbst() {
    vectorVrts.clear();
    //for (vector< Vrt >::iterator it = vectorVrts.begin(); it != vectorVrts.end(); it++) {
    //    delete it->t;
    //}
    /*
    Objeto* sig;
    for (auto it = vectorVrts.begin(); it != vectorVrts.end(); it++) {
         sig = it->t;
         delete it->t;
     }
     */
    //for (auto p : vectorVrts)
      //    delete p.t;
}

bool GrafoAbst::xstVrt(int idVrt) const {
    bool respuesta = false;
    if (idVrt >= 0 && idVrt < obtTotVrt() - 1)
        respuesta = true;
    return respuesta;
}

bool GrafoAbst::xstAdy(int idVrtO, int idVrtD) const {
    bool resultado = false;
    list<int> lstAdyCopia = vectorVrts.at(idVrtO).lstAdy;
    while (!lstAdyCopia.empty() && resultado == false) {
        if (lstAdyCopia.front() == idVrtD)
            resultado = true;
        else
            lstAdyCopia.pop_front();
    }
    return resultado;
}

void GrafoAbst::obtIdVrtAdys(int idVrt, vector< int >& rsp) const {
    list<int> lstAdyCopia = vectorVrts.at(idVrt).lstAdy;
    int idVrtAdy;
    while (!lstAdyCopia.empty()) {
        idVrtAdy = lstAdyCopia.front();
        rsp.push_back(idVrtAdy);
        lstAdyCopia.pop_front();
    }
}

int GrafoAbst::obtCntVrtAdys(int idVrt) const {
    int contador = 0;
    for (auto it = vectorVrts.at(idVrt).lstAdy.begin(); it != vectorVrts.at(idVrt).lstAdy.end(); it++) {
        contador++;
    }
    return contador;
}

Objeto& GrafoAbst::operator[](int idVrt) const {
  
    return *(vectorVrts.at(idVrt).t);
}

int GrafoAbst::obtTotArc() const {
    int contador = 0;
    for (int i = 0; i < vectorVrts.size(); i++) {
        for (auto it = vectorVrts.at(i).lstAdy.begin(); it != vectorVrts.at(i).lstAdy.end(); it++) {
            if (*it >= i)
                contador++;
        }
    }
    return contador;
}

int GrafoAbst::obtTotVrt() const {
    int respuesta = vectorVrts.size();
    return respuesta;
}

Objeto& GrafoAbst::operator[](int idVrt) {

    return *(vectorVrts.at(idVrt).t);
}
