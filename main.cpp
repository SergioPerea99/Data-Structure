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
#include "Exception.h"

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
long buscarPalindromos(VDinamico<ParPalabras> &parPalabras, VDinamico<Palabra> &vPalabras, long cantidad){
    ParPalabras aux;
    long cont = 0;
    clock_t t_ini = clock();
    //vPalabras.ordenar();
    for (long i= 0; i < vPalabras.tam(); i++) {
        aux.SetPal1(vPalabras[i].GetPalabra());
        for (long j = i+1; j < vPalabras.tam(); j++) {
            aux.SetPal2(vPalabras[j].GetPalabra());
            if(vPalabras[i].palindromo(vPalabras[j])){
                parPalabras.insertar(aux);
                if(cont < cantidad){
                    cout<<parPalabras[cont].GetPal1()<<" ----- "<<parPalabras[cont].GetPal2()<<endl;
                    ++cont;
                }
            }
        }
    }
    
    cout << "Tiempo de encontrar todos los palindromos: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
    return parPalabras.tam();
}


/**
 * @brief Buscar Anagramas.
 * @post Función específica para encontrar los anagramas indicados como parametro de la función. Su funcionamiento
 * se basa en la comprobacion de si es o no anagrama un elemento del vector respecto a todos sus siguientes en el vector.
 * @param vPalabras Vector dinámico de palabras. 
 * @param cantidad Número de anagramas que se quieren encontrar y mostrar.
 */
void buscarAnagramas(VDinamico<Palabra>& vPalabras, long cantidad){
    clock_t t_ini = clock();
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
}

int main(int argc, char** argv) {
    
    comprobar();
    try{
        /*-----INSTANCIA DE DATOS EN EL VECTOR DINAMICO-----*/
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

        cout<<endl<<endl;
        int opcion;
        cout<<"ELIGE LA OPCION QUE QUIERA REALIZAR"<<endl;
        cout<<"1: Vector de palíndromos."<<endl;
        cout<<"2: Encontrar anagramas."<<endl;
        cout<<"Tecla != {1,2}: EXIT."<<endl;
        cin>>opcion;

        long cont, cantidad;
        VDinamico<ParPalabras> parPalabras;
        switch(opcion){
            /*-----BUSQUEDA DE PALINDROMOS-----*/
            case 1:
                cout<<"Le aviso que la instancia de todos los palíndromos tarda alrededor de 20 minutos en debug (16 minutos en release)."<<endl;
                do{
                    cout<<"¿Cuántos palíndromos quiere mostrar por pantalla? ";
                    cin>>cantidad;
                }while(cantidad < 0);
                cout<<endl<<"Comenzando la instancia de TODOS los palíndromos y muestra de "<<cantidad<<" palíndromos..."<<endl;
                cont = buscarPalindromos(parPalabras,vPalabras,cantidad);
                for(int i = 0; i < parPalabras.tam(); i++)
                    cout<<"["<<parPalabras[i].GetPal1()<<","<<parPalabras[i].GetPal2()<<"], ";
                cout<<endl<<endl<<"Cantidad de palindromos encontrados: "<<cont<<endl;
                break;

            /*-----BUSQUEDA DE ANAGRAMAS-----*/    
            case 2:
                do{
                    cout<<"INTRODUCE LA CANTIDAD DE ANAGRAMAS QUE QUIERE ENCONTRAR: ";
                    cin>>cantidad;
                }while(cantidad < 0);
                cout<<endl<<"Comenzando la busqueda de "<<cantidad<<" anagramas..."<<endl;
                buscarAnagramas(vPalabras,cantidad);

                break;
                
            default:
                break;
        }

    }catch(Exception& e){
        cout<<"SALTO DE EXCEPCION EN: "<<e.GetExcepcion()<<endl;
    }

    return 0;
}


//long busquedaChar(VDinamico<Palabra> &vOrdenado, string buscar,int i){
//    
//    int inf=i;
//    int sup=vOrdenado.tam()-1;
//    int curIn;
//
//    while(inf <= sup){
//        curIn = (inf+sup)/2;
//        //Suponiendo que el tipo T tiene el correspondiente operador de == y del operador <.
////        char a = vOrdenado[curIn].GetPalabra()[0];
////        char b = buscar[buscar.length()-1];
//        if (vOrdenado[curIn].GetPalabra()[0] == buscar[buscar.length()-1]){
//            return curIn;
//        }else if (vOrdenado[curIn].GetPalabra()[0] < buscar[buscar.length()-1]){
//            inf = curIn + 1;
//        }else{
//            sup = curIn-1;
//        }
//    }
//    return -1;
//}
//
///**
// * @bief Busqueda de palindromos eficiente.
// * @post A raiz de un vector ordenado (IMPORTANTE), se hace una busqueda coherente de los palindromos partiendo de la ultima letra de la palabra
// * que quiere encontrar su palindromo. Con esta ultima letra hago busqueda binaria de ello y me posiciono en ese char de partida para empezar a comprobar
// * si es palindromo o no.
// * @param parPalabras Vector de palindromos encontrados.
// * @param vPalabras Vector de palabras ORDENADO.
// * @param cantidad Cantidad a querer mostrar por pantalla.
// * @return 
// */
//long palindromosEficiente(VDinamico<ParPalabras> &parPalabras, VDinamico<Palabra> &vOrdenado, long cantidad){
//    ParPalabras aux;
//    long cont = 0,pos;
//    clock_t t_ini = clock();
//    string primera;
//    vOrdenado.ordenar();
//    for (long i= 0; i < vOrdenado.tam(); i++) {
//        aux.SetPal1(vOrdenado[i].GetPalabra());
//        primera = vOrdenado[i].GetPalabra();
//        pos = busquedaChar(vOrdenado,primera,i);
//        if (pos != -1){
//            while(pos < vOrdenado.tam()){
//                aux.SetPal2(vOrdenado[pos].GetPalabra());
//                if(vOrdenado[i].palindromo(vOrdenado[pos])){                 
//                    parPalabras.insertar(aux);
//                    if(cont < cantidad){
//                        cout<<parPalabras[cont].GetPal1()<<"   "<<parPalabras[cont].GetPal2()<<endl;
//                        ++cont;
//                    }
//                    
//                }
//                ++pos;
//            }
//        }
//    }
//    
//    cout << "Tiempo de encontrar todos los palindromos: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
//    return parPalabras.tam();
//}