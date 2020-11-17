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


int main(int argc, char** argv) {
    
    comprobar();
    
    /*-----------------------------------------------------------------------------------------------------*/
    /*------------------------------- MENÚ PRINCIPAL: PRÁCTICA  ------------------------------------------*/
    /*-----------------------------------------------------------------------------------------------------*/
    try{

        std::string nombreFich = "quijote-sin-simbolos.txt";
        GestorTextos gestor1;
        int pos = gestor1.addDocumento(nombreFich);

        gestor1.getDocumento(pos)->chequearTexto();
        
        
        
        /*---- NUMERO DE OCURRENCIAS DE MANCHA Y ESTABAN ----*/
        
        Palabra *mancha = nullptr;
        string manch = "mancha";
        gestor1.getDiccionario()->buscarTermino(manch,mancha);
        
        if(mancha)
            cout<<"Ocurrencias de mancha -> "<<mancha->GetOcurrencias()-1<<endl;
        
        Palabra *estaban = nullptr;
        string _estaban = "estaban";
        gestor1.getDiccionario()->buscarTermino(_estaban,estaban);
        
        if(estaban)
            cout<<"Ocurrencias de estaban -> "<<estaban->GetOcurrencias()-1<<endl; //RESTO 1 PORQUE CADA VEZ QUE BUSCA EL TERMINO Y LO ENCUENTRA INCREMENTA SU OCURRENCIA.
        
        
        /*---- BUSCAR Y MOSTRAR POR CONSOLA LA FAMILIA DE PALABRAS QUE SE QUIERA POR CONSOLA ----*/
        
        string _buscar;
        cout << "FAMILIA DE PALABRAS A QUERER BUSCAR : ";
        cin>>_buscar;
        list<Palabra> *familia = new list<Palabra>();
        gestor1.buscarFamilias(_buscar, familia);

        list<Palabra>::iterator it = familia->begin();
        while (it != familia->end()) {
            cout << it->GetPalabra() << "  ";
            ++it;
        }
        
        delete familia;
        familia = nullptr;
        
    }catch(exception &e){
        cout<<e.what()<<endl;
    }
    
    
    return 0;
}
