/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: spdlc
 *
 * Created on 30 de septiembre de 2020, 16:22
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <exception>
#include <locale.h>

#include "VDinamico.h"
#include "Palabra.h"
#include "ParPalabras.h"
#include "ListaEnlazada.h"
#include "Diccionario.h"
#include "GestorTextos.h"

using namespace std;

void comprobar() {
	vector<string> dicc;
        
	ifstream is("dicc-espanol-sin.txt");
	string palabra;

	while (is) {
		is >> palabra;
		dicc.push_back(palabra);
	}
	cout << dicc.size() << " palabras cargadas" << endl;

	is.close();
	is.open("quijote-sin-simbolos.txt");

	clock_t t_ini = clock();

	int validadas = 0, total = 0, p;
	while (is) {
		is >> palabra;
		++total;

		if (binary_search(dicc.begin(), dicc.end(), palabra)) {
			++validadas;
		}
	}
	cout <<"Total palabras: " << total << " validadas: " << validadas << endl;
	cout << "Tiempo implementación 1: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
}

/**
 * @brief Cargar Palabras de un fichero.
 * @post Función que, a partir del vector dinámico creado, inserta las palabras encontradas en el fichero indicado.
 * @param vPalabras Vector de palabras insertadas a partir del fichero.
 */
void cargarPalabras(VDinamico<Palabra> &vPalabras) {
	ifstream is("dicc-espanol.txt");
	string palabra;
        Palabra pal;
        cout <<" -----------------------------------------------------" << endl;
	while (is) {
		is >> palabra;
                
                pal.SetPalabra(palabra);
                vPalabras.insertar(pal);
		//dicc.push_back(palabra);
	}
	cout << vPalabras.tam() << " palabras cargadas en el vector Dinámico." << endl;

	is.close();
	is.open("quijote.txt");

	clock_t t_ini = clock();

	int validadas = 0, total = 0, p;
	while (is) {
		is >> palabra;
                pal.SetPalabra(palabra);
		++total;

		if (vPalabras.busquedaBin(pal) != -1) {
			++validadas;
		}
	}
	cout <<"Total palabras: " << total << " validadas: " << validadas << endl;
	cout << "Tiempo implementación 2: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
}


int main(int argc, char** argv) {
    
    comprobar();
    
    /*-----------------------------------------------------------------------------------------------------*/
    /*------------------------------- MENÚ PRINCIPAL: PRÁCTICA 2 ------------------------------------------*/
    /*-----------------------------------------------------------------------------------------------------*/
    try{
        cout<<endl<<endl;
        cout<<" ---------INICIO PROGRAMA PRINCIPAL PRACTICA 2--------"<<endl;
        //Diccionario diccionario("Diccionario de palabras.txt");
        //cargarPalabras(diccionario.GetTerminos());
        GestorTextos gestor1;
        gestor1.getDiccionario()->SetNombreFich("Diccionario de palabras.txt");
        gestor1.chequearTexto("quijote-sin-simbolos.txt","dicc-espanol-sin.txt");

        
        Iterador<Palabra> it = gestor1.getTexto()->getInexistentes()->iterador();
        int i = 0;
        while(!it.fin() && i < 300){
            cout<<it.dato().GetPalabra()<<endl;
            it.siguiente();
            i++;
        }

        cout<<"NUMERO DE PALABRAS INEXISTENTES : "<<gestor1.getTexto()->getInexistentes()->tama()<<endl;
    }catch(exception &e){
        cout<<e.what()<<endl;
    }

    return 0;
}


//        Palabra pal("hola");
//        Palabra pal2("hola2");
//        Palabra pal3("adios2");
//        Palabra pal4("adios1");
        
//        gestor1.getTexto()->getInexistentes()->insertaOrdenado(pal);
//        gestor1.getTexto()->addInexistente(pal);
//        gestor1.getTexto()->getInexistentes()->insertaOrdenado(pal2);
//        gestor1.getTexto()->addInexistente(pal2);
//        gestor1.getTexto()->getInexistentes()->insertaOrdenado(pal3);
//        gestor1.getTexto()->addInexistente(pal3);
//        gestor1.getTexto()->getInexistentes()->insertaOrdenado(pal4);
//        gestor1.getTexto()->addInexistente(pal4);
