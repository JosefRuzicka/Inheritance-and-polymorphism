#ifndef OBJETO_H
#define OBJETO_H

#include <string>
using namespace std;

class Objeto
{
	/*
	* Es una clase abstracta de la cual se debe derivar implementando:
	* 	el constructor est�ndar,
	* 	el constructor de copias,
	* 	sus m�todos abstractos
	* para obtener clases derivadas concretas.
	* NO HACER NING�N CAMBIO
	*/

public:

	/* CLONADOR VIRTUAL PURO */

	//EFE: realiza la misma funci�n del constructor de copias: genera una copia de *this en el HEAP.
	//	   A diferencia del constructor de copias que s�lo admite enlace est�tico,
	//	   este m�todo s� permite el enlace din�mico.
	virtual Objeto* clonar() const = 0;

	/* SERIALIZADOR VIRTUAL PURO */

	// EFE: genera una hilera que representa el estado de *this.
	virtual string toString() const = 0;
};

#endif // OBJETO_ORDENABLE_H