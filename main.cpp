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
        
        gestor1.getDocumento(pos)->chequearTexto();
        
        
        
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
