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
#include <exception>
#include "VDinamico.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int tamV = 5;
    VDinamico<int> vDinamico;
    
    //---------- INSERTAR ELEMENTOS EN UN VECTOR -----------//

    vDinamico.insertar(2);
    int i = 0;
    int tam = vDinamico.getTamL()*8;
    while(i < tam){
        vDinamico.insertar(i,i);
        i++;
    }
    
    for (int i = 0; i < vDinamico.getTamL(); i++) 
        cout<<vDinamico[i];
    cout<<endl;
    
    cout<<"TAMAÑO LÓGICO DEL VECTOR : "<<vDinamico.getTamL()<<endl;
    cout<<"TAMAÑO FÍSICO DEL VECTOR : "<<vDinamico.getTamF()<<endl<<endl<<endl;
    
    //---------- BORRAR ELEMENTOS EN UN VECTOR -----------//
    for (int i = 0; i < 3; i++)
        vDinamico.borrar(i);

    vDinamico.ordenar();
    for (int i = 0; i < vDinamico.getTamL(); i++) 
        cout<<vDinamico[i];
    cout<<endl;
    cout<<"TAMAÑO LÓGICO DEL VECTOR : "<<vDinamico.getTamL()<<endl;
    cout<<"TAMAÑO FÍSICO DEL VECTOR : "<<vDinamico.getTamF()<<endl;
    
    int buscar = 5;
    int encontrado = vDinamico.busquedaBin(buscar);
    if(encontrado)
        cout<<"ENCONTRADO el elemento "<<buscar<<", en la posición "<<encontrado+1<<"."<<endl;
    
    return 0;
}

