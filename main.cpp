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
    try{
        /*-----INSTANCIA DE DATOS EN EL VECTOR DINAMICO-----*/
        VDinamico<Palabra> vPalabras;
        cargarPalabras(vPalabras);
        VDinamico<Palabra> copiaParcial(vPalabras,-1,20);

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

        cout<<endl<<endl;
        int opcion;
        cout<<"ELIGE LA OPCION QUE QUIERA REALIZAR"<<endl;
        cout<<"1: Vector de palíndromos."<<endl;
        cout<<"2: Vector de palíndromos EFICIENTE."<<endl;
        cout<<"3: Encontrar anagramas."<<endl;
        cout<<"Tecla != {1,2,3}: EXIT."<<endl;
        cin>>opcion;

        long cont, cantidad;
        VDinamico<ParPalabras> parPalabras;
        clock_t t_ini;
        ParPalabras aux;
        Palabra primera;
        switch(opcion){
            
            /*-----BUSQUEDA DE PALINDROMOS-----*/
            case 1:
                
                cout<<"Le aviso que la instancia de todos los palíndromos tarda alrededor de 20 minutos en debug (16 minutos en release)."<<endl;
                do{
                    cout<<"¿Cuántos palíndromos quiere mostrar por pantalla? ";
                    cin>>cantidad;
                }while(cantidad < 0);
                cout<<endl<<"Comenzando la instancia de TODOS los palíndromos y muestra de "<<cantidad<<" palíndromos..."<<endl;
                //cont = buscarPalindromos(parPalabras,vPalabras,cantidad);
                cont = 0;
                t_ini = clock();
                for (long i= 0; i < vPalabras.tam(); i++) {
                    aux.SetPal1(vPalabras[i].GetPalabra());
                    for (long j = i+1; j < vPalabras.tam(); j++) {
                        aux.SetPal2(vPalabras[j].GetPalabra());
                        if(vPalabras[i].palindromo(vPalabras[j])){
                            if(!parPalabras.buscar(aux) && vPalabras[i].GetPalabra() != vPalabras[j].GetPalabra()){
                                parPalabras.insertar(aux);
                                if(cont < cantidad){
                                    cout<<parPalabras[cont].GetPal1()<<" ----- "<<parPalabras[cont].GetPal2()<<endl;
                                    ++cont;
                                }
                            }
                        }
                    }
                }

                cout << "Tiempo de encontrar todos los palindromos: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
                for(int i = 0; i < parPalabras.tam(); i++)
                    cout<<"["<<parPalabras[i].GetPal1()<<","<<parPalabras[i].GetPal2()<<"], ";
                cout<<endl<<endl<<"Cantidad de palindromos encontrados: "<<parPalabras.tam()<<endl;
                break;

            /*-----BUSQUEDA DE PALINDROMOS EFICIENTE-----*/    
            case 2:
                
                cout<<endl<<"Comenzando la instancia de TODOS los palíndromos..."<<endl;
                //cont = palindromosEficiente(parPalabras,vPalabras,cantidad);
                cont = 0;
                long pos;
                t_ini = clock();
                vPalabras.ordenar();
                for (long i= 0; i < vPalabras.tam(); i++) {
                    aux.SetPal1(vPalabras[i].GetPalabra());       
                    primera = vPalabras[i];       
                    int pos = vPalabras.busquedaBin(primera.reves());
                    if(pos != -1 && i < pos){
                        if(vPalabras[pos].palindromo(vPalabras[i])){
                            aux.SetPal2(vPalabras[pos].GetPalabra());
                            if (!parPalabras.buscar(aux) && vPalabras[i].GetPalabra() != vPalabras[pos].GetPalabra())
                                parPalabras.insertar(aux);
                        }
                    }

                }

                cout << "Tiempo de encontrar todos los palindromos: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
                
                for(int i = 0; i < parPalabras.tam(); i++)
                    cout<<"["<<parPalabras[i].GetPal1()<<","<<parPalabras[i].GetPal2()<<"], ";
                cout<<endl<<endl<<"Cantidad de palindromos encontrados: "<<parPalabras.tam()<<endl;
                break;
                
            default:
                break;
                
            /*-----BUSQUEDA DE ANAGRAMAS-----*/    
            case 3:
                
                do{
                    cout<<"INTRODUCE LA CANTIDAD DE ANAGRAMAS QUE QUIERE ENCONTRAR: ";
                    cin>>cantidad;
                }while(cantidad < 0);
                cout<<endl<<"Comenzando la busqueda de "<<cantidad<<" anagramas..."<<endl;
                //buscarAnagramas(vPalabras,cantidad);
                t_ini = clock();
                int contador = 0;
                for(int i = 0; i < vPalabras.tam() && contador < cantidad; i++){
                    for(int j = i+1; j < vPalabras.tam() && contador < cantidad; j++){
                        if(vPalabras[i].anagrama(vPalabras[j])){
                            cout<<"ANAGRAMA ENCONTRADO: "<<vPalabras[i].GetPalabra()<<" ---- "<<vPalabras[j].GetPalabra()<<endl;
                            ++contador;
                        }
                    }
                }
                cout << "Tiempo de encontrar "<<cantidad<<" anagramas: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
                break;
        }

    }catch(exception& e){
        cout<<"EXCEPCION EN "<<e.what()<<endl;
    }
    
    ListaEnlazada<int> lista_prueba;
    
    for (int i = 1; i < 10; i++) {
        lista_prueba.insertaFin(i);
    }
    cout<<lista_prueba.tama()<<endl;
    
    
    return 0;
}


