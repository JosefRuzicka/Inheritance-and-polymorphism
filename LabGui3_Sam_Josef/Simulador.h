#pragma once

#include "RedNodos.h"
#include "Nodo.h"


class Simulador {
	// Representa el proceso de simulación de la infección en la red de computadoras.

public:

	// EFE: Construye un simulador que transformará al grafo g.
	Simulador(RedNodos& g);

	// Destruye a *this retornando toda la memoria asignada dinámicamente.
	~Simulador();


	// REQ: el grafo asociado (el pasado al constructor) esté bien construido.
	// MOD: el grafo asociado.    
	// EFE: inicializa el simulador con los siguientes parámetros:
	//      ios o initial-outbreak-size [1..N], N cantidad de vértices: cantidad
	//           de vértices contagiados al comienzo de la simulación.
	//      vsc o virus-spread-chance [0..0.1]: probabilidad de contagio.
	//      vcf o virus-check-frecuency [1..20]: frecuencia de chequeo antivirus.
	//      rc o recovery-chance [0..0.1]: probabilidad de eliminación de infección.
	//      grc o gain-resistance-chance [0..1]: probabilidad de generar resistencia.
	//		el contador de tics se inicializa en cero.
	void iniciarSimulacion(int ios, double vsc, int vcf, double rc, double grc);

	// REQ: el grafo asociado (el pasado al constructor) esté bien construido.
	// MOD: el grafo asociado.
	// EFE: aplica al grafo asociado una transformación con base en las reglas de 
	//      la simulación especificadas.
	void simular();

private:
	RedNodos& red_nodos;
	int ios;
	double vsc;
	int vcf;
	double rc;
	double grc;
	int cont_tics;
	vector<int> vecSus;
	vector<int> vecInf;
};

Simulador::Simulador(RedNodos& g) : red_nodos(g) {
	this->red_nodos = g;
}

Simulador::~Simulador() {

}

void Simulador::iniciarSimulacion(int ios, double vsc, int vcf, double rc, double grc) {
	this->ios = ios;
	this->vsc = vsc;
	this->vcf = vcf;
	this->rc = rc;
	this->grc = grc;
	cont_tics = 1;
	int nodo = 0;

	while (red_nodos.obtTotVrtInfectados() < ios) {
		for (int i = 0; i < ios; i++) {
			nodo = rand() % red_nodos.obtTotVrt();
			if (red_nodos[nodo].obtEstado() != Nodo::E::I) {
				red_nodos[nodo].modEstado(Nodo::E::I);
				vecInf.push_back(nodo);//Llenamos el vector de infectados
			}
			else {
				i--;
			}
		}

	}

	//Llenamos el vectr de susceptibles
	vecSus.reserve(red_nodos.obtTotVrt());
	for (int i = 0; i < red_nodos.obtTotVrt(); i++) {
		if (red_nodos[i].obtEstado() == Nodo::E::S) {
			vecSus.push_back(i);
		}

	}
}

void Simulador::simular() {

	//Creamos un vector de suceptibles e infectados para que el programa no revisara todos los nodos y asi se hicieran los tics mas rapido.
	//Size es para saber el tamaño inicial de el vector de suceptibles
	vecSus.shrink_to_fit();
	int size = red_nodos.obtTotVrt() - red_nodos.obtTotVrtInfectados() - red_nodos.obtTotVrtResistentes();
	int contagios;//calculamos con la probabilidad de contagio, cuantos nodos aproximadamente se tienen que contagiar por tic.
	if (red_nodos.obtTotVrtInfectados() == ios) {
		contagios = vsc * red_nodos.obtTotVrt();

	}
	else {
		contagios = round((red_nodos.obtTotVrt() - (red_nodos.obtTotVrtInfectados() + red_nodos.obtPrcVrtResistentes())) * vsc);
	}
	if (contagios > size)
	{
		contagios = size;
	}
	int contar = 0;//Contador para saber cuando dejar de contagiar, osea cuando contar == contagios
	vector< int > vectorAdys;//Para guardar adyacencias
	vector< int > vectorAdys2;//Para guardar adyacencias
	int pruebita;// variable  para guardar el vesus.size() inicial y no el modificado;
	for (int i = 0; i <= size; i++) {
		//recorremos las adys del nodo susceptible, para ver si existen nodos infectados y poder infectar el susceptible y sus adyacencias susceptibles
		if (red_nodos.obtTotVrtSusceptibles() >= 1 && i < vecSus.size()) {
			
			pruebita = i;
			for (int ady = 0; ady < red_nodos.obtCntVrtAdys(vecSus.at(pruebita)); ady++) {
				vectorAdys.clear();
				red_nodos.obtIdVrtAdys(vecSus.at(pruebita), vectorAdys);
				if (red_nodos[vectorAdys.at(ady)].obtEstado() == Nodo::I && contar < contagios) {
					//Si hay un infectado entonces se infectan sus adyacencias siempre y cuando contar < contagios
					vectorAdys2.clear();
					red_nodos.obtIdVrtAdys(vectorAdys.at(ady), vectorAdys2);
					for (int j = 0; j < red_nodos.obtCntVrtAdys(vectorAdys.at(ady)); j++) {
						if (red_nodos[vectorAdys2.at(j)].obtEstado() == Nodo::S) {
							red_nodos[vectorAdys2.at(j)].modEstado(Nodo::I);
							contar++;
							vecInf.push_back(vectorAdys2.at(j));//Si infectamos un noso lometemos en el vector de infectados
							for (int k = 0; k < vecSus.size(); k++)//Y lo borramos del vector de susceptibles
								if (vecSus.at(k) == vectorAdys2.at(j))
								{
									vecSus.erase(vecSus.begin() + k);
									if (vecSus.size() <= pruebita && vecSus.size() != 0 && pruebita > 0) {
										pruebita--;
									}
									break;


								}
						}
						if (contar == contagios) {//Si contar es igual a contagios entonces dejamos de infectar nodos
							break;
						}
					}

					if (contar == contagios) {
						i = size;
						break;

					}
				}
			}

		}
	}

	//Si contador de tics es igual a la frecuencia de chequeo entonces generamos susceptibilidad y resistencia para cada nodo
	if (cont_tics == vcf) {
		for (int i = 0; i < vecInf.size(); i++) {
			if (((rand() % 11) * 0.10) <= rc) {
				red_nodos[vecInf.at(i)].modEstado(Nodo::S);
				int var = vecInf.at(i);
				vecSus.push_back(vecInf.at(i));
				vecInf.erase(vecInf.begin() + i);
				//generacion de resistencia
				if (((rand() % 11) * 0.10) <= grc) {//si se genero susceptibilidad, intentamos generar resistencia
					red_nodos[var].modEstado(Nodo::R);
					vecSus.erase(vecSus.begin() + (vecSus.size() - 1));
				}

			}
		}
	}


	//aumentamos contadorTics o lo reseteamos
	if (cont_tics == vcf) {
		cont_tics = 1;
	}
	else {
		cont_tics++;
	}

}