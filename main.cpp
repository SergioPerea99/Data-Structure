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
#include "ParPalabras.h"

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

/**
 * @brief Buscar palindromos.
 * @post Busca, con orden cuadrático, todos los palindromos encontrados en el vector de palabras.
 * @param parPalabras Vector de pares de palabras que forman un palindromo.
 * @param vPalabras Palabras almacenadas.
 * @return Cantidad de palabras con palíndromo.
 */
long buscarPalindromos(VDinamico<ParPalabras> &parPalabras, VDinamico<Palabra> &vPalabras){
    ParPalabras aux;
    long cont = 0;
    clock_t t_ini = clock();
   
    for (long i= 0; i < vPalabras.tam(); i++) {
        aux.SetPal1(vPalabras[i].GetPalabra());
        for (long j = i+1; j < vPalabras.tam(); j++) {
           aux.SetPal2(vPalabras[j].GetPalabra());
            if(vPalabras[i].palindromo(vPalabras[j])){
                parPalabras.insertar(aux);
                cout<<parPalabras[cont].GetPal1()<<"   "<<parPalabras[cont].GetPal2()<<endl;
                ++cont;
            }
        }
    }
    
    cout << "Tiempo de encontrar todos los palindromos: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
    return cont;
}


int main(int argc, char** argv) {
    
    comprobar();
    
    /*-----CARGA DE DATOS EN EL VECTOR DINAMICO-----*/
    VDinamico<Palabra> vPalabras;
    cargarPalabras(vPalabras);
    
    cout<<"TAMAÑO LOGICO DEL VECTOR: "<<vPalabras.tam()<<". TAMAÑO FISICO DEL VECTOR: "<<vPalabras.getTamF()<<endl<<endl; 
    
    
    
    /*-----ORDENAR VECTOR EN CASO DE NO ESTAR ORDENADO-----*/
    if(vPalabras.estaOrdenado())
        cout<<"El vector se encuentra ordenado."<<endl;
    else{
        cout<<"Vector no ordenado. Comenzando a ordenar..."<<endl;
        vPalabras.ordenar();
        
        if(vPalabras.estaOrdenado())
            cout<<"VECTOR ORDENADO CORRECTAMENTE."<<endl;
    }
    
    cout<<endl<<endl;
    
    
    /*-----ORDENAR EL VECTOR AL REVÉS.-----*/
    //He mostrado los 10 primeros elementos del inicio y final del vector, antes (previo vector ordenado) y después de hacer el orden inverso.
    for (int i = 0; i < 10; i++)
        cout<<vPalabras[i].GetPalabra()<<"      "<<vPalabras[vPalabras.tam()-i-1].GetPalabra()<<endl;
    cout<<"Comenzando a ordenar de forma inversa..."<<endl;
    vPalabras.ordenarRev();
    for (int i = 0; i < 10; i++)
        cout<<vPalabras[i].GetPalabra()<<"      "<<vPalabras[vPalabras.tam()-i-1].GetPalabra()<<endl;

    
    
    
    int opcion;
    cout<<"ELIGE LA OPCION QUE QUIERA REALIZAR"<<endl;
    cout<<"1: Vector de palíndromos."<<endl;
    cout<<"2: Encontrar anagramas."<<endl;cin>>opcion;

    long cont;
    VDinamico<ParPalabras> parPalabras;
    switch(opcion){
        /*-----BUSQUEDA DE PALINDROMOS-----*/
        case 1:
            
            cont = buscarPalindromos(parPalabras,vPalabras);
            cout<<"Cantidad de palindromos encontrados: "<<cont<<endl;
            break;
            
        /*-----CREACION DE ANAGRAMAS-----*/    
        case 2:
            
            break;
    }
    
    return 0;
    
}
