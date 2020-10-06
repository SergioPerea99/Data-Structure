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

#include "VDinamico.h"
#include "Palabra.h"

using namespace std;

 void comprobar() {
	vector<string> dicc;

	ifstream is("dicc-espanol.txt");
	string palabra;

	while (is) {
		is >> palabra;
		dicc.push_back(palabra);
	}
	cout << dicc.size() << " palabras cargadas" << endl;

	is.close();
	is.open("quijote.txt");

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

  void cargarPalabras(VDinamico<Palabra> &vPalabras) {
	ifstream is("dicc-espanol.txt");
	string palabra;
        Palabra pal;
        
	while (is) {
		is >> palabra;
                
                pal.SetPalabra(palabra);
                vPalabras.insertar(pal);
		//dicc.push_back(palabra);
	}
	cout << vPalabras.tam() << " palabras cargadas" << endl;

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
    
    VDinamico<Palabra> vPalabras;
    
    cargarPalabras(vPalabras);
    
    cout<<"TAMAÑO LOGICO DEL VECTOR: "<<vPalabras.tam()<<". TAMAÑO FISICO DEL VECTOR: "<<vPalabras.getTamF()<<endl<<endl; 
    
    VDinamico<Palabra> copiaPalabras(vPalabras);
    
    cout<<"[ ";
    for(int i = 0; i < vPalabras.tam(); i++)
        cout<<vPalabras[i].GetPalabra()<<"  ";
    cout<<"]."<<endl<<endl;
    //Comprobar si está ordenado, sino lo está se ordena.
    if(copiaPalabras.estaOrdenado())
        cout<<"El vector se encuentra ordenado."<<endl;
    else{
        cout<<"Vector no ordenado. Comenzando a ordenar..."<<endl;
        copiaPalabras.ordenar();
        if(copiaPalabras.estaOrdenado())
            cout<<"VECTOR ORDENADO CORRECTAMENTE."<<endl;
    }
    
    
    return 0;
    
}
