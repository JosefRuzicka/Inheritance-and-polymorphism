#pragma once

#define DEBUG
#include <assert.h>     /* para usar assert */
#include <string>
#include <sstream> // permite usar ostringstream en "toString()".
#include <vector>
using namespace std;

#include "LstAdys.h"

/**
* Clase TableroReveriHex, Crea el tablero y realiza en él todas las modificaciones jugada tras jugada.
*
* Authors Josef Ruzicka y Samantha Romero, con código base del profesor Alan Calderón
* version 3.0
* since   2020-04-05
*/

class TableroReversiHex
{
public:
	enum Ficha { nula, blanca, negra };
	// REQ: (N % 2 == 1) && (N > 4).
	// EFE: Construye un tablero de ReversiHex con N columnas.
	//		Las columnas tendrán longitud N y N - 1 intercaladamente.
	//		El tablero hexagonal queda en posición inicial.
	TableroReversiHex(int N);

	// EFE: libera la memoria dinámica asignada al tablero hexagonal.
	// NOTA: es imprescindible, de lo contrario no se liberaría la memoria dinamica asignada.
	~TableroReversiHex();

	/* Métodos observadores públicos */

	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra).
	// EFE: retorna true si la jugada en [c,p] es válida para la fichas del color,
	//		retorna false en caso contrario.
	bool validarJugada(int c, int p, Ficha color) const;

	// EFE: retorna true si el estado actual es un estado final del juego,
	//		retorna false en caso contrario.
	bool verFin() const;

	// REQ: color == blanca || color == negra.
	// EFE: retorna true si las de color no tienen opción para jugar,
	//	 false en caso contrario.
	bool verPasan(Ficha color) const;

	// REQ:(0 <= c < N) && (0 <= p < N).
	// EFE: retorna el valor en [c,p].
	Ficha verFichaEn(int c, int p) const;

	// EFE: retorna una hilera con las adyacencias de cada [c,p].
	string adysToString() const;

	// REQ: (0 <= c < N) && (0 <= p < N).
	// MOD: *this.
	// EFE: coloca en [c,p] la ficha de color.
	void colocarSimple(int c, int p, Ficha color);

	/* Métodos modificadores*/
	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra).
	// MOD: *this.
	// EFE: coloca en [c,p] la ficha de color lo que implica realizar todos los flanqueos correspondientes.
	void colocarFlanqueando(int c, int p, Ficha color);

	// EFE: retorna "nula" si hay un empate y "negra" o "blanca" en caso contrario.
	Ficha quienGana() const;

	// EFE: retorna una hilera apropiada para desplegar el estado del juego por consola.
	string toString() const;

	//REQ: que el tablero exista y el color.
	//MOD: el tablero, si hay jugadas disponibles.
	//EFE: coloca una ficha en una posición determinada por heurísticas si tiene la posibilidad de hacerlo.
	void jugarInteligente(Ficha color);

private:

	/* Métodos observadores de flanqueo privados, se invocarán desde "validarJugada()" */

	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra).
	// EFE: retorna true si color sí flanquea la dirección dir desde [c,p]; false en caso contrario.
	bool verFlanqueaDir(int dir, int c, int p, Ficha color) const;

	/* Métodos modificadores de flanqueo privados, se invocarán desde "colocar()" */

	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra) && verFlanqueaDir(c,p).
	// MOD: *this.
	// EFE: flanquea la direccion dir, desde [c,p].
	void flanqueaDir(int dir, int c, int p, Ficha color);

	// REQ: (0 <= c < N) && (0 <= p < N).
	// EFE: retorna lst por referencia con la lista de adyacencias que le corresponde a la casilla [c,p]
	void generarLstAdys(int c, int p, LstAdys& lst);

	/* REPRESENTACIÓN DEL TABLERO */

	/* Estructura de la celda de cada tablero */
	struct Celda {
		int c;		// columna en que se ubica la celda
		int p;		// posicion en que se ubica la celda
		Ficha cf;	// color de la ficha ubicada en la celda.
		LstAdys lista_adys; // lista de adyacencias de una casilla del tablero hexagonal
		Celda() :c(0), p(0), cf(Ficha::nula) {}; // declaración y definción del constructor estándar de la estructura
		Celda(int c, int p, Ficha color) : c(c), p(p), cf(color) {}; // constructor no estándar
	};

	/* Variables del tablero*/
	int N;			// guarda la cantidad maxima de columnas que debe ser impar.

	/* puntero a puntero */
	// Representa la cantidad variable de N columnas, cada una, intercaladamente, con N o N - 1 posiciones.
	// Puntero a un arreglo simple de punteros por eso "**".
	vector< vector< Celda > > columnas;
};

/* CODIGO DE LOS METODOS */

TableroReversiHex::TableroReversiHex(int N) : columnas(N) // reserva espacio para N columnas.
{
	this->N = N;
	assert((N % 2 == 1) && (N > 4));		// durante la depuración nos ayuda a encontrar errores

	// se asigna memoria a los arreglos que representan las columnas
	Celda c_inicial;
	for (int i = 0; i < N; i++)
		// se crea un vector en cada posición de columnas, con N o N - 1 celdas.
		columnas[i] = vector< Celda >(N - i % 2, c_inicial);

	//Inicializador de las fichas, se verifica si (N-5)%4 = 0 para saber si comienzan 6 o 4 fichas.
	if ((N - 5) % 4 == 0 || N == 5) {
		colocarSimple(1 + (N - 5) / 2, 1 + (N - 5) / 2, TableroReversiHex::Ficha::blanca);
		colocarSimple(4 + (N - 5) / 2, 2 + (N - 5) / 2, TableroReversiHex::Ficha::blanca);
		colocarSimple(1 + (N - 5) / 2, 2 + (N - 5) / 2, TableroReversiHex::Ficha::blanca);
		colocarSimple(3 + (N - 5) / 2, 1 + (N - 5) / 2, TableroReversiHex::Ficha::negra);
		colocarSimple(3 + (N - 5) / 2, 2 + (N - 5) / 2, TableroReversiHex::Ficha::negra);
		colocarSimple(0 + (N - 5) / 2, 2 + (N - 5) / 2, TableroReversiHex::Ficha::negra);
	}
	else {
		colocarSimple(4 + (N - 7) / 2, 3 + (N - 7) / 2, TableroReversiHex::Ficha::blanca);
		colocarSimple(3 + (N - 7) / 2, 3 + (N - 7) / 2, TableroReversiHex::Ficha::blanca);
		colocarSimple(3 + (N - 7) / 2, 2 + (N - 7) / 2, TableroReversiHex::Ficha::negra);
		colocarSimple(2 + (N - 7) / 2, 3 + (N - 7) / 2, TableroReversiHex::Ficha::negra);
	}

	// se crean las adyacencias de cada [columna, posicion]
	for (int c = 0; c < N; c++) {
		int p_max = (c % 2 == 0) ? N : N - 1;
		for (int p = 0; p < p_max; p++) {
			generarLstAdys(c, p, columnas[c][p].lista_adys);
			if (!(columnas[c][p].cf == blanca) && !(columnas[c][p].cf == negra))
				columnas[c][p].cf = nula;
		}
	}
}

TableroReversiHex::~TableroReversiHex()
{
	//cambiamos el vector por uno vacio que ocupa menos memoria
	vector< vector< Celda > > vectorVacio;
	columnas.swap(vectorVacio);
}



bool TableroReversiHex::validarJugada(int c, int p, TableroReversiHex::Ficha color) const
{
	bool respuesta = false;
	int dir = 0;
	while (dir <= 5 && respuesta == false) {
		if (verFlanqueaDir(dir, c, p, color))
			respuesta = true;
		dir++;
	}

	return respuesta;
}

bool TableroReversiHex::verFin() const
{
	bool resultado = false;
	if (verPasan(blanca) && verPasan(negra))
		resultado = true;
	return resultado;
}

bool TableroReversiHex::verPasan(Ficha color) const
{
	bool resultado = true;
	for (int c = 0; c < N; c++) {
		int p_max = (c % 2 == 0) ? N : N - 1;
		for (int p = 0; p < p_max; p++) {
			if (columnas[c][p].cf == nula && validarJugada(c, p, color) && resultado == true)
				resultado = false;
		}
	}
	return resultado;
}

TableroReversiHex::Ficha TableroReversiHex::quienGana() const
{
	int blancas = 0;
	int negras = 0;
	Ficha resultado;
	//cuenta las fichas de cada color
	for (int c = 0; c < N; c++) {
		int p_max = (c % 2 == 0) ? N : N - 1;
		for (int p = 0; p < p_max; p++) {
			if (verFichaEn(c, p) == negra) {
				negras++;
			}
			else if (verFichaEn(c, p) == blanca) {
				blancas++;
			}
		}
	}
	//define el ganador, o el empate.
	if (blancas > negras)
		resultado = blanca;
	else if (blancas < negras)
		resultado = negra;
	else if (blancas == negras)
		resultado = nula;

	return resultado;
}

TableroReversiHex::Ficha TableroReversiHex::verFichaEn(int c, int p) const
{
	assert((0 <= c) && (c < N));
	assert((0 <= p) && ((c % 2 == 0) && (p < N) || (c % 2 == 1) && (p < N - 1)));
	return columnas[c][p].cf;
}

string TableroReversiHex::adysToString() const
{
	ostringstream salida;
	// se generan las hileras con las adyacencias de cada [columna,posicion]
	for (int c = 0; c < N; c++) {
		int posicion_max = (c % 2 == 0) ? N : N - 1;
		for (int p = 0; p < posicion_max; p++) {
			salida << "Adyacencias de [" << c << "," << p << "]: ";
			salida << columnas[c][p].lista_adys.toString();
		}
		salida << endl;
	}
	return salida.str();
}

void TableroReversiHex::colocarSimple(int c, int p, Ficha color)
{
	assert((0 <= c) && (c < N));
	assert((0 <= p) && ((c % 2 == 0) && (p < N) || (c % 2 == 1) && (p < N - 1)));
	Celda cld;
	cld.c = c;
	cld.p = p;
	cld.cf = color;
	columnas[c][p] = cld; // OJO: las celdas ya existen por eso es posible la asignación
}

void TableroReversiHex::colocarFlanqueando(int c, int p, Ficha color)
{
	assert((0 <= c) && (c < N));
	assert((0 <= p) && ((c % 2 == 0) && (p < N) || (c % 2 == 1) && (p < N - 1)));
	Celda cld;
	cld.c = c;
	cld.p = p;
	cld.cf = color;
	int dir = 0;
	if (validarJugada(c, p, color))
		columnas[c][p] = cld;
	//captura las fichas flanqueadas.
	while (dir <= 5) {
		if (verFlanqueaDir(dir, c, p, color))
			flanqueaDir(dir, c, p, color);
		dir++;
	}
}

string TableroReversiHex::toString() const
{
	string sepr_ext_arriba_base = string(" /-\\");
	string sepr_ext_abajo_base = string(" \\-/");
	string sepr_ext_arriba = "   ";
	string sepr_ext_abajo = "   ";
	string sepr_int_arriba_base_1 = string("-\\");
	string sepr_int_arriba_base_2 = string("-/");
	string sepr_int_arriba = string(" /");
	string sepr_int_abajo_base_1 = string("-/");
	string sepr_int_abajo_base_2 = string("-\\");
	string sepr_int_abajo = string(" \\");
	string indices = "     0 1 2 3 4 5 6 7 8 9 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c d e f g h i j k l m n o p q r s t u v w x y z";
	string nums_columnas = "";
	ostringstream salida; // es un buffer de memoria con caracteres listos para ser desplegados por consola

	/* se preparan todas las hileras */
	for (int i = 0; i < (N + 1) / 2; i++) {
		sepr_ext_arriba = sepr_ext_arriba + sepr_ext_arriba_base;
		sepr_ext_abajo = sepr_ext_abajo + sepr_ext_abajo_base;
	}
	for (int i = 0; i < (N + 1) / 2; i++) {
		sepr_int_arriba = sepr_int_arriba + ((i % 2 == 0) ? sepr_int_arriba_base_1 : sepr_int_arriba_base_2);
	}
	for (int i = 0; i < (N + 1) / 2; i++) {
		sepr_int_abajo = sepr_int_abajo + ((i % 2 == 0) ? sepr_int_abajo_base_1 : sepr_int_abajo_base_2);
	}
	nums_columnas = indices.substr(0, (5 + 2 * (N)));

	/* se construye la salida */
	salida << nums_columnas << endl;
	for (int p = 0; p < N; p++)
	{
		salida << sepr_ext_arriba << endl;
		salida << "  ";
		salida << indices[5 + 2 * p] << "|";
		for (int c = 0; c < N; c = c + 2)
		{
			salida << " ";
			if (columnas[c][p].cf != nula)
				salida << ((columnas[c][p].cf == negra) ? "N" : "B");
			else salida << " ";
			salida << " |";
		}
		salida << endl;
		salida << sepr_ext_abajo;
		if (p < N - 1) {
			salida << endl;
			salida << "  ";
			salida << indices[5 + 2 * p] << "  |";
			for (int c = 1; c < N - 1; c = c + 2)
			{
				salida << " ";
				if (columnas[c][p].cf != nula)
					salida << ((columnas[c][p].cf == negra) ? "N" : "B");
				else salida << " ";
				salida << " |";
			}
		}
		salida << endl;
	}
	return salida.str(); // se accede el contenido del buffer y se retorna como hilera
}

bool TableroReversiHex::verFlanqueaDir(int dir, int c, int p, Ficha color) const
{
		assert((0 <= c) && (c < N));
		assert((0 <= p) && ((c % 2 == 0) && (p < N) || (c % 2 == 1) && (p < N - 1)));
		assert(color != nula);
		bool resultado = false;

		// código para determinar si hay flanqueo o no
		bool encuentra_color = false;
		bool encuentra_otro_color = false;
		Ficha otro_color;
		int cc = c;
		int pp = p;

		if (color == negra)
			otro_color = blanca;
		else otro_color = negra;

		//arriba a la derecha.
		cc = c;
		pp = p;
		if (dir == 0 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
			cc = c + 1;
			pp = p;
			if (c % 2 == 0)
				pp = p - 1;

			while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && columnas[cc][pp].cf == otro_color) {
				encuentra_otro_color = true;
				if (cc % 2 == 0)
					pp--;
				cc++;
			}
			if (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && columnas[cc][pp].cf == color)
				encuentra_color = true;

			if (encuentra_color && encuentra_otro_color)
				resultado = true;
		}
		//derecha.
		cc = c;
		pp = p;
		if (dir == 1 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
			cc = c + 2;

			while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && columnas[cc][pp].cf == otro_color) {
				encuentra_otro_color = true;
				cc = cc + 2;
			}
			if (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && columnas[cc][pp].cf == color)
				encuentra_color = true;

			if (encuentra_color && encuentra_otro_color)
				resultado = true;
		}
		//abajo a la derecha.
		cc = c;
		pp = p;
		if (dir == 2 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
			cc = c + 1;
			pp = p;
			if (c % 2 != 0)
				pp++;

			while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && ((cc % 2 == 0) && (pp < N) || (cc % 2 == 1) && (pp < N - 1)) && columnas[cc][pp].cf == otro_color) {
				encuentra_otro_color = true;
				if (cc % 2 != 0)
					pp++;
				cc++;
			}
			if (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && ((cc % 2 == 0) && (pp < N) || (cc % 2 == 1) && (pp < N - 1)) && columnas[cc][pp].cf == color)
				encuentra_color = true;

			if (encuentra_color && encuentra_otro_color)
				resultado = true;
		}
		//abajo a la izquierda.
		cc = c;
		pp = p;
		if (dir == 3 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
			cc = c - 1;
			pp = p;
			if (c % 2 != 0)
				pp++;

			while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && ((cc % 2 == 0) && (pp < N) || (cc % 2 == 1) && (pp < N - 1)) && columnas[cc][pp].cf == otro_color) {
				encuentra_otro_color = true;
				if (cc % 2 != 0)
					pp++;
				cc--;
			}
			if (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && ((cc % 2 == 0) && (pp < N) || (cc % 2 == 1) && (pp < N - 1)) && columnas[cc][pp].cf == color)
				encuentra_color = true;

			if (encuentra_color && encuentra_otro_color)
				resultado = true;
		}
		//izquierda.
		cc = c;
		pp = p;
		if (dir == 4 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
			cc = c - 2;

			while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && ((cc % 2 == 0) && (pp < N) || (cc % 2 == 1) && (pp < N - 1)) && columnas[cc][pp].cf == otro_color) {
				encuentra_otro_color = true;
				cc = cc - 2;
			}
			if (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && ((cc % 2 == 0) && (pp < N) || (cc % 2 == 1) && (pp < N - 1)) && columnas[cc][pp].cf == color)
				encuentra_color = true;

			if (encuentra_color && encuentra_otro_color)
				resultado = true;
		}
		//arriba a la Izquierda.
		cc = c;
		pp = p;
		if (dir == 5 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
			cc = c - 1;
			pp = p;
			if (c % 2 == 0)
				pp = p - 1;

			while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && ((cc % 2 == 0) && (pp < N) || (cc % 2 == 1) && (pp < N - 1)) && columnas[cc][pp].cf == otro_color) {
				encuentra_otro_color = true;
				if (cc % 2 == 0)
					pp--;
				cc--;
			}
			if (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && ((cc % 2 == 0) && (pp < N) || (cc % 2 == 1) && (pp < N - 1)) && columnas[cc][pp].cf == color)
				encuentra_color = true;

			if (encuentra_color && encuentra_otro_color)
				resultado = true;
		}
		return resultado;
}

void TableroReversiHex::flanqueaDir(int dir, int c, int p, TableroReversiHex::Ficha color)
{
	assert((0 <= c) && (c < N + 1));
	assert((0 <= p) && ((c % 2 == 0) && (p < N) || (c % 2 == 1) && (p < N - 1)));
	assert(color != nula);
	assert(verFlanqueaDir(dir, c, p, color));

	Ficha otro_color;

	// determina cuál es el otro color
	if (color == negra)
		otro_color = blanca;
	else otro_color = negra;

	// código para flanquear en la dirección dir:
	int cc = c;
	int pp = p;

	//arriba a la derecha.
	if (dir == 0 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
		cc = c + 1;
		pp = p;
		if (c % 2 == 0)
			pp = p - 1;

		while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && columnas[cc][pp].cf == otro_color) {
			columnas[cc][pp].cf = color;
			if (cc % 2 == 0)
				pp--;
			cc++;
		}
	}
	//derecha.
	if (dir == 1 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
		cc = c + 2;

		while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && columnas[cc][pp].cf == otro_color) {
			columnas[cc][pp].cf = color;
			cc = cc + 2;
		}
	}
	//abajo a la derecha.
	if (dir == 2 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
		cc = c + 1;
		pp = p;
		if (c % 2 != 0)
			pp++;

		while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && columnas[cc][pp].cf == otro_color) {
			columnas[cc][pp].cf = color;
			if (cc % 2 != 0)
				pp++;
			cc++;
		}
	}
	//abajo a la izquierda.
	if (dir == 3 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
		cc = c - 1;
		pp = p;
		if (c % 2 != 0)
			pp++;

		while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && columnas[cc][pp].cf == otro_color) {
			columnas[cc][pp].cf = color;
			if (cc % 2 != 0)
				pp++;
			cc--;
		}
	}
	//izquierda.
	if (dir == 4 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
		cc = c - 2;

		while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && columnas[cc][pp].cf == otro_color) {
			columnas[cc][pp].cf = color;
			cc = cc - 2;
		}
	}
	//arriba a la Izquierda.
	if (dir == 5 && c >= 0 && p >= 0 && (c < N) && (p < N)) {
		cc = c - 1;
		pp = p;
		if (c % 2 == 0)
			pp = p - 1;

		while (cc >= 0 && pp >= 0 && (cc < N) && (pp < N) && columnas[cc][pp].cf == otro_color) {
			columnas[cc][pp].cf = color;
			if (cc % 2 == 0)
				pp--;
			cc--;
		}
	}
}

void TableroReversiHex::generarLstAdys(int c, int p, LstAdys& lst)
{
	// En vez de logica condicional compleja se abarcan todos los casos con la matriz deltas.
	int deltas[6][3] = { {+1, -1, 0},{2, 0, 0}, {+1, 0, +1}, {-1, 0, +1}, {-2, 0, 0}, {-1, -1, 0} };
	int p_max = (c % 2 == 0) ? N : N - 1;
	int delta_c = 0;	// cambio en columna para obtener una nueva direccion
	int delta_p = 0;	// cambio en posicion para obtener una nueva direccion
	LstAdys::DatosAdy datos_ady; // OJO: se puede acceder porque un tipo público en LstAdys, pero siempre respeta su encapsulamiento.

	// se consideran todas las direcciones posibles:
	for (int dir = 0; dir < 6; dir++) {
		delta_c = deltas[dir][0];
		delta_p = deltas[dir][1 + (c % 2)];
		if ((p == N - 1) && ((dir == 2) || (dir == 3)))		// identifica posiciones altas de cada columna
			delta_p++;
		if ((0 <= (c + delta_c)) && ((c + delta_c) < N) && (0 <= (p + delta_p)) && ((p + delta_p) < N)) {
			datos_ady.dir = dir;
			datos_ady.c = c + delta_c;
			datos_ady.p = p + delta_p;
			lst.agrAdyacencia(datos_ady);
		}
	}
}

void TableroReversiHex::jugarInteligente(TableroReversiHex::Ficha color) {
	assert(color != nula);
	//assert(!verPasan(color));
	//verifica si hay jugadas (esto lo hacemos en el main, pero para efectos del torneo no sabemos cómo va a ser el main del profesor.)
	if (!verPasan(color)) {
		//Atributos utilizados por el método desde la heuristica 1.
		vector <int> jugada;
		Ficha otro_color;
		bool jugadaElegida = false;
		int p_elegido = 0;
		int c_elegido = 0;

		//definimos nuestro color.
		if (color == negra)
			otro_color = blanca;
		else otro_color = negra;

		//buscamos jugadas disponibles en fila 0 y 4 y las agregamos al vector de jugadas
		int p = 0;
		while (!jugadaElegida && p < N) {
			//busca en columna 0
			if (validarJugada(0, p, color) && columnas[0][p].cf == nula) {

				jugada = { 0, p, 0 };
				jugadaElegida = true;
			}
			//busca en columna 4, si no encontramos ya una  jugada en la columna 0
			if (jugadaElegida == false && validarJugada(N - 1, p, color) && columnas[N - 1][p].cf == nula) {

				jugada = { N - 1, p, 0 };
				jugadaElegida = true;
			}
			p++;
		}

		//realizamos la jugada, si encontramos una.
		if (jugadaElegida) {
			c_elegido = jugada.at(0);
			p_elegido = jugada.at(1);
			colocarFlanqueando(c_elegido, p_elegido, color);
		}

		//segunda Heuristica, agrega al vector las jugadas desde c == 2 hasta c == N-2 y elige la que tenga más flanqueos posibles en su próximo turno.
		//Atributos utilizados por la heuristica 2.
		vector <vector <int> > vectorJugadas;
		int cc;
		int pp;
		Ficha ele;
		Ficha ele2;
		int adyacencias = 6;

		if (!jugadaElegida) {
			adyacencias = 6;
			for (int c = 2; c < N - 2; c++) {
				int posicion_max = (c % 2 == 0) ? N : N - 1;
				for (int p = 0; p < posicion_max; p++) {
					if (columnas[c][p].cf == nula) {
						for (int dir = 0; dir < 6; dir++) {
							//revisa todas direcciones de la poscision x y calcula cuantas veces podemos flanquear y cuantas veces podemos ser flanqueados.
							if (verFlanqueaDir(dir, c, p, color) == true) {
								//si la jugada esta disponible revisa que la ficha en direccion este nula y la contraria con ficha del contrincante y viceversa, para saber si nos flanquean.
								if (dir == 0 || dir == 3) {
									// Este if verifica que p==0 y c par y tambien que c sea menor a n -1 de lo contraio la posicion no existe y da error al comparar.
									if ((!(p == 0 && c % 2 == 0)) && c < N - 1) {

										if (c % 2 == 0) {
											cc = c + 1;
											pp = p - 1;

										}
										else {
											cc = c + 1;
											pp = p;
										}
										// si dir== 0 entonces revisamos que dir == ficha contraria y que su direccion contrntria sea nula.
										// si dir == 3 entonces revisamos que dir == nula y que su direccion contratria sea ficha contraria.
										if (dir == 0) {
											ele = otro_color;
											ele2 = nula;
										}
										else {
											ele = nula;
											ele2 = otro_color;
										}
										if (columnas[cc][pp].cf == ele) {
											// El sieguiente if verifica que c sea mayor a 0 y p menor a n-1, de lo contario la posicion no existe y no podriamos hacer la comparacion.
											if (c > 0 && p < N - 1) {
												if (c % 2 == 0) {
													cc = c - 1;
													pp = p;
													// si nos pueden flanquer se le resta a adyacencias 1, el cual se resta cada que podemos ser flamqueados en una direccion.
													if (columnas[cc][pp].cf == ele2) {
														adyacencias--;
													}
												}
												else {
													cc = c - 1;
													pp = p + 1;
													// si nos pueden flanquer se le resta a adyacencias 1, el cual se resta cada que podemos ser flamqueados en una direccion.
													if (columnas[cc][pp].cf == ele2) {
														adyacencias--;
													}
												}
											}
										}
									}
								}
								else if (dir == 4 || dir == 1) {
									// El siguiente if verifica que c se sea mayor a 2 de lo contario la columna no se lo podria restar 2 porque daria una posicion que no existe.
									if (c >= 2) {
										cc = c - 2;
										pp = p;

										// si dir== 4 entonces revisamos que dir == ficha contraria y que su direccion contrntria sea nula.
										// si dir == 1 entonces revisamos que dir == nula y que su direccion contratria sea ficha contraria.
										if (dir == 4) {
											ele = otro_color;
											ele2 = nula;
										}
										else {
											ele = nula;
											ele2 = otro_color;
										}

										if (columnas[cc][pp].cf == ele) {
											// El siguiente if verifica que c sea par y menor a n - 1, de lo contrario al sumarle 2 daria una posicion inexistente.
											if (c % 2 == 0 && c < N - 1) {
												cc = c + 2;
												pp = p;
												// si nos pueden flanquer se le resta a adyacencias 1, el cual se resta cada que podemos ser flamqueados en una direccion.
												if (columnas[cc][pp].cf == ele2) {
													adyacencias--;
												}
											}
											//El siguiente if verifica en este caso que c sea impar y menor n - 2, de lo contrario al sumarle 2 daria una posicion inexistente.
											else if (c % 2 != 0 && c < N - 2) {
												cc = c + 2;
												pp = p;
												// si nos pueden flanquer se le resta a adyacencias 1, el cual se resta cada que podemos ser flamqueados en una direccion.
												if (columnas[cc][pp].cf == ele2) {
													adyacencias--;
												}
											}
										}
									}
								}

								else if (dir == 5 || dir == 2) {
									//El siguiente if verifica que c sea mayor a 0 y p menor a n - 1 y p mayor cero, porque de lo contrario no podriamos comparar dado que serian posiciones inexistentes.
									if (c > 0 && p < N - 1 && p > 0) {
										if (c % 2 == 0) {
											pp = p - 1;
											cc = c - 1;
										}
										else
										{
											cc = c - 1;
											pp = p;
										}

										// si dir== 5 entonces revisamos que dir == ficha contraria y que su direccion contrntria sea nula.
										// si dir == 2 entonces revisamos que dir == nula y que su direccion contratria sea ficha contraria.
										if (dir == 5) {
											ele = otro_color;
											ele2 = nula;
										}
										else {
											ele = nula;
											ele2 = otro_color;
										}

										if (columnas[cc][pp].cf == ele) {
											if (c < N - 1) {
												if (c % 2 == 0) {
													cc = c + 1;
													pp = p;
													// si nos pueden flanquer se le resta a adyacencias 1, el cual se resta cada que podemos ser flamqueados en una direccion.
													if (columnas[cc][pp].cf == ele2) {
														adyacencias--;
													}
												}
												else {
													cc = c + 1;
													pp = p + 1;
													// si nos pueden flanquer se le resta a adyacencias 1, el cual se resta cada que podemos ser flamqueados en una direccion.
													if (columnas[cc][pp].cf == ele2) {
														adyacencias--;
													}
												}
											}
										}
									}
								}
							}
						}
						//Agrega a la lista las jugadas que pueden hacer flanqueos, con su respectivo numero de adyacencias
						if (validarJugada(c, p, color)) {
							jugada = { c, p, adyacencias };
							vectorJugadas.push_back(jugada);
							jugada.clear();
							jugadaElegida = true;
							adyacencias = 6;
						}
					}
				}
			}
			// Tercera heurística, si no encontramos una jugada que vaya de acuerdo a nuestra estrategia entonces buscamos cualquier jugada disponible y la jugamos.
			if (!jugadaElegida) {
				for (int c = 0; c < N; c++) {
					int posicion_max = (c % 2 == 0) ? N : N - 1;
					for (int p = 0; p < posicion_max; p++) {
						if (columnas[c][p].cf == nula && validarJugada(c, p, color)) {
							jugada = { c, p, 0 };
							vectorJugadas.push_back(jugada);
							//igualamos c y p al maximo para terminar el loop si ya encontramos una jugada.
							p = posicion_max;
							c = N;
						}
					}
				}
			}
			// Revisamos en el vector cual jugada tiene mas adyacencias(que significa que es la jugada en la cual nos flanquean menos) y la elegimos para jugarla.
			int variable = 0;
			int posicionVector = 0;
			for (vector <vector <int> >::iterator list_iter = vectorJugadas.begin();
				list_iter != vectorJugadas.end(); list_iter++) {

				if (vectorJugadas.at(posicionVector).at(2) > variable) {
					variable = vectorJugadas.at(posicionVector).at(2);
				}
				posicionVector++;
			}
			posicionVector = 0;
			for (vector <vector <int> >::iterator list_iter = vectorJugadas.begin();
				list_iter != vectorJugadas.end(); list_iter++) {
				if (vectorJugadas.at(posicionVector).at(2) == variable) {
					c_elegido = vectorJugadas.at(posicionVector).at(0);
					p_elegido = vectorJugadas.at(posicionVector).at(1);
				}
				posicionVector++;
			}
			colocarFlanqueando(c_elegido, p_elegido, color);
			jugadaElegida = true;
		}
	}
}
