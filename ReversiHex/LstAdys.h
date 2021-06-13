#pragma once

#include <sstream>  // permite usar ostringstream en "toString()".
#include <list>
#include <vector>
using namespace std;

/**
* Clase LstAdys, Al crearse un TableroReversiHex, cada casilla es asignada con una lista de adyacencias que es manejada en esta clase.
*
* Authors Josef Ruzicka y Samantha Romero, con código base del profesor Alan Calderón
* version 3.0
* since   2020-04-05
*/

class LstAdys
{
public:

	// se usa para pasar y recibir datos de adyacencias contenidas en la lista.
	struct DatosAdy {
		int dir;
		int c;
		int p;
		DatosAdy() : dir(0), c(0), p(0) {};
		DatosAdy(int d, int c, int p) : dir(d), c(c), p(p) {};
	};

	// EFE: construye una lista de adyacencias vacia. El destructor no es necesario porque se usan shared_ptr
	LstAdys();

	// REQ: dady.dir exista como dir en alguna de las adyacencias de la lista.
	// EFE: retorna por referencia los datos de una adyacencia cuya direccion es dir.
	//		retorna dady.dir == -1 si la direccion dady.dir no existe en la lista.
	void obtDatosAdy(DatosAdy& dady) const;

	// REQ: la longitud de la lista sea mayor que cero.
	// EFE: retorna por referencia un vector con los datos de todas las adyacencias.
	void obtAdys(vector< DatosAdy >& v_dadys) const;
	// EFE: retorna una hilera con las coordenadas de cada dirección: {#d [p,c],...}
	string toString() const;

	// REQ: (0 <= dady.dir) && (dady.dir < 6) && () && (dady.c < N) && (dady.p < N - 1)
	// MOD: *this
	// EFE: agrega una nueva adyacencia al final de la lista con los datos en dady.
	// NOTA: retorna dady.dir == 0 si la insercion es valida y dady.dir = -1 si no es valida y ha sido omitida.
	void agrAdyacencia(DatosAdy& dady);

	private:

	list< DatosAdy > lista;
};

LstAdys::LstAdys()
{

}

void LstAdys::obtDatosAdy(DatosAdy& dady) const
{
	bool adyacenciaEncontrada = false;
	for (auto it = lista.begin(); it != lista.end();it++) {
		if (it->dir == dady.dir) {
			dady.c = it->c;
			dady.p = it->p;
			adyacenciaEncontrada = true;
		}
	}
	if (!adyacenciaEncontrada)
		dady.dir = -1;
}

void LstAdys::obtAdys(vector< DatosAdy >& v_dadys) const
{
	assert(lista.size() > 0);
	DatosAdy dt;
	for (auto it = lista.begin(); it != lista.end();it++) {
		dt.c = it->c;
		dt.p = it->p;
		dt.dir = it->dir;
		v_dadys.push_back(dt);
	}
}

string LstAdys::toString() const
{
	DatosAdy dt;
	ostringstream resultado;
	for (auto it = lista.begin(); it != lista.end();it++) {
		dt.c= it->c;
		dt.p = it->p;
		dt.dir = it->dir;		
		resultado << " { " << dt.c << ", " << dt.p << " }";
	}
	resultado << endl;
	return resultado.str();
	}



void LstAdys::agrAdyacencia(DatosAdy& dady)
{
	lista.push_back(dady);
}