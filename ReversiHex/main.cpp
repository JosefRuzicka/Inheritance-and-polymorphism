#include <iostream>
#include <exception>
using namespace std;

#include "TableroReversiHex.h"

/**
* Main, lleva a cabo el juego, llama y utiliza las demás clases.
* Authors Josef Ruzicka y Samantha Romero, con código base del profesor Alan Calderón
* version 3.0
* since   2020-04-05
*/

// REQ: que en nombre se guarde alguno de los nombres de los jugadores.
// MOD: c y p
// EFE: retorna por referencia la (c,p) de la jugada nueva del jugador correspondiente a nombre.
void pideJugada(const TableroReversiHex& tr, int N, string nombre, TableroReversiHex::Ficha color, int& c, int& p);

int main()
{
	string nombre_negras = "";
	string nombre_blancas = "";
	int N = -1;
	int p = -1;
	int c = -1;

	while ((N % 2 == 0) || (N < 5))
	{
		cout << "Digite la cantidad mAxima de posiciones que debe ser impar y mayor que cuatro: ";
		cin >> N;
		cout << endl;
	}

	TableroReversiHex trh(N);

	while (nombre_negras == "")
	{
		cout << "Digite el nombre quien juega las NEGRAS: ";
		cin >> nombre_negras;
	}

	while (nombre_blancas == "")
	{
		cout << "Digite el nombre quien juega las BLANCAS: ";
		cin >> nombre_blancas;
	}

	cout << trh.toString() << endl << endl;

	while (!trh.verFin())
	{
		//turno jugador de fichas negras
		if (!trh.verPasan(TableroReversiHex::negra)) {
			pideJugada(trh, N, nombre_negras, TableroReversiHex::negra, c, p);
			trh.colocarFlanqueando(c, p, TableroReversiHex::negra);
			cout << trh.toString() << endl << endl;
		}
		else {
			cout << "no hay jugadas posibles para " << nombre_negras;
			cout << endl;
		}
		//turno jugador de fichas blancas
		if (!trh.verPasan(TableroReversiHex::blanca)) {
			pideJugada(trh, N, nombre_blancas, TableroReversiHex::blanca, c, p);
			trh.colocarFlanqueando(c, p, TableroReversiHex::blanca);
			cout << trh.toString() << endl << endl;
		}
		else {
			cout << "no hay jugadas posibles para " << nombre_blancas;
			cout << endl;
		}
	}
	cout << "Fin del juego";
	cout << endl;
	//se determina el ganador.
	if (trh.quienGana() == TableroReversiHex::Ficha::blanca)
		cout << "gana blanca";
	else if (trh.quienGana() == TableroReversiHex::Ficha::negra)
		cout << "gana negra";
	else
		cout << "empate";
	cout << endl;
}

void pideJugada(const TableroReversiHex& tr, int N, string nombre, TableroReversiHex::Ficha color, int& c, int& p)
{
	bool validez = false;
	while ((c < 0) || (p < 0) || !validez || ((c % 2 == 0) && ((c > N + 1) || (p >= N))) || (c % 2 == 1) && ((c > N) || (p >= N - 1)))
	{
		cout << nombre << " por favor digite la columna de su jugada: "; cin >> c;
		cout << nombre << " por favor digite la posicion de su jugada: "; cin >> p;
		cout << endl;

		validez = tr.validarJugada(c, p, color);
		if (!validez)
			cout << nombre << ": SU JUGADA NO ES VALIDA!" << endl;
	}
}

