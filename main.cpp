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
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <exception>
#include <map>

#include "VDinamico.h"
#include "Palabra.h"
#include "ParPalabras.h"
#include "ListaEnlazada.h"
#include "DiccionarioConVerbos.h"
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

//int eliminarNombresPropios(GestorTextos& gestor1, int pos){
//
//    Iterador<Palabra> it = gestor1.getDocumento(pos)->getInexistentes().iterador();
//    Iterador<Palabra> aux = it;
//    int borrados = 0;
//    cout << "[ ";
//    while (!it.fin()) {
//        if (it.dato().GetPalabra()[0] >= 65 && it.dato().GetPalabra()[0] <= 90) {
//            cout << it.dato().GetPalabra() << "___";
//            aux = it;
//            it.siguiente();
//            gestor1.getDocumento(pos)->getInexistentes().borra(aux);
//            ++borrados;
//        } else
//            it.siguiente();
//
//    }
//    return borrados;
//}


int main(int argc, char** argv) {
    
    comprobar();
    
    /*-----------------------------------------------------------------------------------------------------*/
    /*------------------------------- MENÚ PRINCIPAL: PRÁCTICA  ------------------------------------------*/
    /*-----------------------------------------------------------------------------------------------------*/
    try{

        std::string nombreFich = "quijote-sin-simbolos.txt";
        GestorTextos gestor1;
        int pos = gestor1.addDocumento(nombreFich);

//        map<std::string, Palabra*>::iterator it = gestor1.getDiccionario()->it_Begin();
//        while (it != gestor1.getDiccionario()->it_End()){
//            cout<<*it->second<<endl;
//            it++;
//        }
        gestor1.getDocumento(pos)->chequearTexto();
        

        
        
    }catch(exception &e){
        cout<<e.what()<<endl;
    }
    
    
    return 0;
}
