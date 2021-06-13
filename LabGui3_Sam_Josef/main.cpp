/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 /*
  * File:   main.cpp
  * Author: Alan
  * Modificado por: Samantha Romero Pérez y Josef Ruzicka
  * Created on 11 de septiembre de 2018, 05:36 PM
  */


#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include "RedNodos.h"
#include "Simulador.h"
#include "Nodo.h"
#include "GrafoAbst.h"
/*
 *
 */
int main(int argc, char** argv) {

	// lectura de archivo
	ifstream archivo;
	archivo.open("archivo_experimentos.txt");//Abrir el archivo para leer
	string linea;// Guarda cada linea del archivo
	string token[12];//Guarda los datos de cada linea del archivo
	int infec;// cantidad de infectados inicialmente
	int cantidadNodos;
	double porcentAdy;
	double probaContagio;
	int frecuenciaChe;
	double probaRecuperacion;
	double probaResistencia;
	string archivito;// Archivo para abrir red_peq.txt
	int contador;// contador de tics
	int contadorEx;//Contador de experimentos
	double promedioR;
	double promedioI;
	double promedioS;

	if (archivo.fail()) {
		exit(1);
	}
	contadorEx = 0;

	while (!archivo.eof()) {
		contadorEx++;
		ofstream archivoGenerado("ArchivoSalida" + to_string(contadorEx) + ".txt");//Generamos el archivo para el experimento
		ifstream archivoGeneradoif("ArchivoSalida" + to_string(contadorEx) + ".txt");//Archivo de experimento para leer
		contador = 1;// contador de tics por experimento
		// guarda la primera linea del archivo en el string linea
		getline(archivo, linea);
		//guarda los datos de lines en el arreglo token
		for (int i = 0; i < 9; i++) {
			token[i] = linea.substr(0, linea.find_first_of(" "));
			linea = linea.substr(linea.find_first_of(" ") + 1);
		}
		//si el token en la posicion 6 contiene un 1 significa que la linea del archivo tiene un int con la cantidad de nodos entonces lo guardamos en cantidadNodos
		if (stoi(token[6]) == 1) {
			cantidadNodos = stoi(token[7]);
			//cantidadNodos = 20;
			porcentAdy = stod(token[8]);
			infec = ((cantidadNodos * 0.01) * stoi(token[0]));
		}
		//Llenamos las variables con los datos del experimento
		probaContagio = stod(token[1]);
		frecuenciaChe = stoi(token[2]);
		probaRecuperacion = stod(token[3]);
		probaResistencia = stod(token[4]);
		//Entra en el if si no hay un archivo en la linea, y se usa el constructor que no tiene archivo
		if (stoi(token[6]) == 1) {
			RedNodos red(cantidadNodos, porcentAdy);
			Simulador sim1(red);
			cout << endl;
			sim1.iniciarSimulacion(infec, probaContagio, frecuenciaChe, probaRecuperacion, probaResistencia);
			//Hace las simulaciones hasta que los infectados sean cero, por experimento.
			while (red.obtTotVrtInfectados() != 0) {
				sim1.simular();
				//Calculamos los promedios de cada variable.
				if (contador == 1) {
					promedioI = red.obtTotVrtInfectados();
					promedioR = red.obtPrcVrtResistentes();
					promedioS = red.obtTotVrtSusceptibles();
				}
				else {
					promedioI = round((promedioI + red.obtTotVrtInfectados()) * 0.5);
					promedioR = round((promedioR + red.obtTotVrtResistentes()) * 0.5);
					promedioS = round((promedioS + red.obtTotVrtSusceptibles()) * 0.5);
				}
				archivoGenerado << red.obtTotVrtInfectados() << ", ";//Total de infectados
				archivoGenerado << red.obtTotVrtResistentes() << ", ";// Total de Resistentes
				archivoGenerado << red.obtTotVrtSusceptibles() << ", ";// Total de Susceptibles
				archivoGenerado << round(red.obtPrcVrtInfectados() * 100) << ", ";// Porcentanje de infectados
				archivoGenerado << round(red.obtPrcVrtResistentes() * 100) << ", ";// Porcentanje de Resistentes
				archivoGenerado << round(red.obtPrcVrtSusceptibles() * 100) << ", ";// Porcentanje de susceptibles
				archivoGenerado << promedioI << ", ";// Promedio de infectados
				archivoGenerado << promedioR << ", ";// Promedio de Resistentes
				archivoGenerado << promedioS << ", ";// Promedio de Susceptibles
				archivoGenerado << endl;
				cout << endl;
				//Imprimimos en consola
				cout << "Numero de tics:  " << contador << endl;
				cout << "Nodos Resistentes " << red.obtTotVrtSusceptibles() << endl;
				cout << "Nodos Resistentes " << red.obtTotVrtResistentes() << endl;
				cout << "Nodos infectados: " << red.obtTotVrtInfectados() << endl;
				cout << "Porcentanje de infectados: " << round(red.obtPrcVrtInfectados() * 100) << endl;
				cout << "Porcentanje de Resistentes:" << round(red.obtPrcVrtResistentes() * 100) << endl;
				cout << "Porcentanje de susceptibles: " << round(red.obtPrcVrtSusceptibles() * 100) << endl;
				cout << "Promedio de infectados: " << promedioI << endl;
				cout << "Promedio de Resistentes: " << promedioR << endl;
				cout << "Promedio de Susceptibles: " << promedioS << endl;
				contador++;
			}
		}
		// Se hace todo lo anterior pero para el caso del constructor de archivos
		else {
			archivito = token[7];
			ifstream a;
			a.open(archivito);//Abrimos el archivo
			if (a.fail()) {
				exit(1);
			}
			getline(a, linea);
			cantidadNodos = stoi(linea);
			a.close();
			RedNodos red2(a);
			Simulador sim2(red2);
			infec = ((cantidadNodos * 0.01) * stoi(token[0]));
			sim2.iniciarSimulacion(infec, probaContagio, frecuenciaChe, probaRecuperacion, probaResistencia);
			while (red2.obtTotVrtInfectados() != 0) {
				sim2.simular();
				//Calculamos los promedios de cada variable
				if (contador == 1) {
					promedioI = red2.obtTotVrtInfectados();
					promedioR = red2.obtTotVrtResistentes();
					promedioS = red2.obtTotVrtSusceptibles();
				}
				else if (contador != 1) {
					promedioI = round((promedioI + red2.obtTotVrtInfectados()) * 0.5);
					promedioR = round((promedioR + red2.obtTotVrtResistentes()) * 0.5);
					promedioS = round((promedioS + red2.obtTotVrtSusceptibles()) * 0.5);
				}
				//Metemos los datos en el archivo generado.
				archivoGenerado << red2.obtTotVrtInfectados() << ", ";//Total de infectados
				archivoGenerado << red2.obtTotVrtResistentes() << ", ";// Total de Resistentes
				archivoGenerado << red2.obtTotVrtSusceptibles() << ", ";// Total de Susceptibles
				archivoGenerado << round(red2.obtPrcVrtInfectados() * 100) << ", ";// Porcentanje de infectados
				archivoGenerado << round(red2.obtPrcVrtResistentes() * 100) << ", ";// Porcentanje de Resistentes
				archivoGenerado << round(red2.obtPrcVrtSusceptibles() * 100) << ", ";// Porcentanje de susceptibles
				archivoGenerado << promedioI << ", ";// Promedio de infectados
				archivoGenerado << promedioR << ", ";// Promedio de Resistentes
				archivoGenerado << promedioS << ", ";// Promedio de Susceptibles
				archivoGenerado << endl;
				cout << endl;
				//Imprimimos los datos en consola
				cout << "Numero de tics:  " << contador << endl;
				cout << "Nodos Resistentes " << red2.obtTotVrtSusceptibles() << endl;
				cout << "Nodos Resistentes " << red2.obtTotVrtResistentes() << endl;
				cout << "Nodos infectados: " << red2.obtTotVrtInfectados() << endl;
				cout << "Porcentanje de infectados: " << round(red2.obtPrcVrtInfectados() * 100) << endl;
				cout << "Porcentanje de Resistentes:" << round(red2.obtPrcVrtResistentes() * 100) << endl;
				cout << "Porcentanje de susceptibles: " << round(red2.obtPrcVrtSusceptibles() * 100) << endl;
				cout << "Promedio de infectados: " << promedioI << endl;
				cout << "Promedio de Resistentes: " << promedioR << endl;
				cout << "Promedio de Susceptibles: " << promedioS << endl;
				contador++;
			}
		}
		contador = 0;
	}
}