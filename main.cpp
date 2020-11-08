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

int eliminarNombrePropio(GestorTextos& gestor1, int pos){

    Iterador<Palabra> it = gestor1.getDocumentos()[pos]->getInexistentes().iterador();
    Iterador<Palabra> aux = it;
    int borrados = 0;
    cout << "[ ";
    while (!it.fin()) {
        if (it.dato().GetPalabra()[0] >= 65 && it.dato().GetPalabra()[0] <= 90) {
            cout << it.dato().GetPalabra() << "___";
            aux = it;
            it.siguiente();
            gestor1.getDocumentos()[pos]->getInexistentes().borra(aux);
            ++borrados;
        } else
            it.siguiente();

    }
    return borrados;
}


int main(int argc, char** argv) {
    
    comprobar();
    
    /*-----------------------------------------------------------------------------------------------------*/
    /*------------------------------- MENÚ PRINCIPAL: PRÁCTICA 2 ------------------------------------------*/
    /*-----------------------------------------------------------------------------------------------------*/
    try{
        
        cout<<endl<<endl;
        cout<<" ---------INICIO PROGRAMA PRINCIPAL PRACTICA 3--------"<<endl;
        
        

        /*---- COMPROBACION EN TIEMPO DE COMO SERÍA LA BÚSQUEDA DE PALABRAS INEXISTENTES SIN VERBOS CONJUGADOS (PRACTICA 2) ----.*/
        
        GestorTextos gestor1;
        
        std::string nombreFich = "quijote-sin-simbolos.txt";
        int pos = gestor1.addDocumento(nombreFich);
        
        Diccionario * dic = gestor1.getDocumentos()[pos]->getDicc();
        
        gestor1.getDocumentos()[pos]->chequearTexto();
        //gestor1.chequearTexto(pos);
        
        /*SACO POR PANTALLA TODOS LOS ELEMENTOS DE LA LISTA DE INEXISTENTES INICIAL (SIN CONTAR REPETIDOS).*/
        cout<<endl<<endl;
        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"---------------      PALABRAS INEXISTENTES      -----------------------"<<endl;
        Iterador<Palabra> it = gestor1.getDocumentos()[pos]->getInexistentes().iterador();
        int i = 0;
        cout<<"[ ";
        while(!it.fin()){
            cout<<it.dato().GetPalabra()<<", ";
            it.siguiente();
            i++;
        }
        cout<<"]."<<endl<<endl<<endl;
        
        /*ELIMINO Y MUESTRO POR PANTALLA LOS ELEMENTOS QUE SON NOMBRES PROPIOS*/
        cout<<"---------------------------------------------------------------------"<<endl;
        cout<<"---------------      PALABRAS ELIMINADAS      -----------------------"<<endl;
        int borrados = eliminarNombrePropio(gestor1, pos);
        cout<<"]."<<endl<<endl<<endl<<endl;
        
        /*MUESTRO POR PANTALLA LA LISTA DE PALABRAS INEXISTENTES SIN REPETIDOS Y SIN NOMBRES PROPIOS.*/
        cout<<"-------------------------------------------------------------------------------"<<endl;
        cout<<"---------------      PALABRAS INEXISTENTES FINALES      -----------------------"<<endl;
        it = gestor1.getDocumentos()[pos]->getInexistentes().iterador();
        cout<<"[ ";
        while(!it.fin()){
            cout<<it.dato().GetPalabra()<<", ";
            it.siguiente();
        }
        cout<<"]."<<endl<<endl<<endl;
        
        cout<<"NOMBRES PROPIOS ELIMINADOS : "<<borrados<<endl;
        cout<<"NUMERO DE PALABRAS INEXISTENTES (SIN NOMBRES PROPIOS NI REPETIDOS): "<<gestor1.getDocumentos()[pos]->getInexistentes().tama()<<endl;
    
    }catch(exception &e){
        cout<<e.what()<<endl;
    }
    
    
    return 0;
}
