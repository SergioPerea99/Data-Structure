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
#include <vector>

#include "VDinamico.h"
#include "Palabra.h"
#include "ParPalabras.h"
#include "ListaEnlazada.h"
#include "DiccionarioConVerbos.h"
#include "GestorTextos.h"
#include "THashPalabra.h"

using namespace std;

int main(int argc, char** argv) {
    
    /*-----------------------------------------------------------------------------------------------------*/
    /*------------------------------- MENÚ PRINCIPAL: PRÁCTICA 4 ------------------------------------------*/
    /*-----------------------------------------------------------------------------------------------------*/
    
    
    
    try{
        
        /*---- CHEQUEAR EL QUIJOTE Y UN SEGUNDO TEXTO ----*/

        std::string nombreFich = "quijote-sin-simbolos.txt";
        GestorTextos gestor1;
        
        cout<<"MAXIMO DE COLISIONES : "<<gestor1.getDiccionario()->maxColisiones_THASH()<<endl;
        cout<<"PROMEDIO DE COLISIONES : "<<gestor1.getDiccionario()->promColisiones_THASH()<<endl;
        cout<<"FACTOR DE CARGA (REAL): "<<(float)gestor1.getDiccionario()->tamTerminos()/gestor1.getDiccionario()->tamTablaHASH()<<endl;
        
        int pos = gestor1.addDocumento(nombreFich);
        
        /*--- INSERTAR LA PALABRA WIFI Y MOSTRAR EL NÚMERO DE COLISIONES ---*/
        Palabra wifi("wifi",gestor1.getDiccionario());
        gestor1.getDiccionario()->insertarPalabra(wifi);
        
        
        /*--- ELIMINAR TODAS LAS PALABRAS QUE COMIENCEN POR W ---*/
        string cadena_buscar = "w";
        vector<Palabra> *borradas = gestor1.getDiccionario()->borrarPalabras_substr(cadena_buscar);
       
        cout<<endl<<"Palabras borradas : "<<borradas->size()<<endl;
        for (Palabra i : *borradas)
            cout<<"Palabra borrada --> "<<i.GetPalabra()<<endl;
        
        Palabra waterpolo("waterpolo",gestor1.getDiccionario());
        Palabra windsurf("windsurf",gestor1.getDiccionario());
        
        if(gestor1.getDiccionario()->insertarPalabra(waterpolo))
            cout<<endl<<"PALABRA "<<waterpolo.GetPalabra()<<" INSERTADA CORRECTAMENTE."<<endl;
        
        if(gestor1.getDiccionario()->insertarPalabra(windsurf))
            cout<<"PALABRA "<<windsurf.GetPalabra()<<" INSERTADA CORRECTAMENTE."<<endl;
        
        delete borradas; //Liberar la memoria reservada para el vector<Palabra>
        
    }catch (invalid_argument &e){
        cout<<e.what()<<endl;
    }
    catch (logic_error &e){
        cout<<e.what()<<endl;
    }
    catch (runtime_error &e){
        cout<<e.what()<<endl;
    }
    catch(exception &e){
        cout<<e.what()<<endl;
    }
    
    
    return 0;
}
