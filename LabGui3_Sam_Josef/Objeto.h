#ifndef OBJETO_H
#define OBJETO_H

#include <string>
using namespace std;

class Objeto
{
	/*
	* Es una clase abstracta de la cual se debe derivar implementando:
	* 	el constructor estándar,
	* 	el constructor de copias,
	* 	sus métodos abstractos
	* para obtener clases derivadas concretas.
	* NO HACER NINGÚN CAMBIO
	*/

public:

	/* CLONADOR VIRTUAL PURO */

	//EFE: realiza la misma función del constructor de copias: genera una copia de *this en el HEAP.
	//	   A diferencia del constructor de copias que sólo admite enlace estático,
	//	   este método sí permite el enlace dinámico.
	virtual Objeto* clonar() const = 0;

	/* SERIALIZADOR VIRTUAL PURO */

	// EFE: genera una hilera que representa el estado de *this.
	virtual string toString() const = 0;
};

#endif // OBJETO_ORDENABLE_H