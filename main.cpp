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
#include "MallaRegular.h"

using namespace std;

int main(int argc, char** argv) {
    
    /*-----------------------------------------------------------------------------------------------------*/
    /*------------------------------- MENÚ PRINCIPAL: PRÁCTICA 4 ------------------------------------------*/
    /*-----------------------------------------------------------------------------------------------------*/
    
    
    
    try{
        
        /*---- CHEQUEAR EL QUIJOTE Y UN SEGUNDO TEXTO ----*/
        
        MallaRegular<Casilla<Usuario>> malla(0,0,5,5,2,2);
        
        Usuario u("77433569","","","",0,0,nullptr);
        Usuario u2("77433569","","","",0,0,nullptr);
       
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
