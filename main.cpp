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


int main(int argc, char** argv) {
    
    comprobar();
    
    /*-----------------------------------------------------------------------------------------------------*/
    /*------------------------------- MENÚ PRINCIPAL: PRÁCTICA 2 ------------------------------------------*/
    /*-----------------------------------------------------------------------------------------------------*/
    try{
        cout<<endl<<endl;
        cout<<" ---------INICIO PROGRAMA PRINCIPAL PRACTICA 2--------"<<endl;
        GestorTextos gestor1;
        gestor1.getDiccionario()->SetNombreFich("El Quijote + diccionario Español.txt");
        gestor1.chequearTexto("quijote-sin-simbolos.txt","dicc-espanol-sin.txt");

        Iterador<Palabra> it = gestor1.getTexto()->getInexistentes()->iterador();
        int i = 0;
        cout<<"[ ";
        while(!it.fin()){
            cout<<it.dato().GetPalabra()<<", ";
            it.siguiente();
            i++;
        }
        cout<<"]."<<endl;

        cout<<"NUMERO DE PALABRAS INEXISTENTES : "<<gestor1.getTexto()->getInexistentes()->tama()<<endl;
    }catch(exception &e){
        cout<<e.what()<<endl;
    }

    return 0;
}
