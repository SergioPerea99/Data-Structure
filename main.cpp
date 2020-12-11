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
    
    THashPalabra hashPal(200); //APARENTEMENTE FUNCIONANDO.
    
//    try{
//        
//        /*---- CHEQUEAR EL QUIJOTE Y UN SEGUNDO TEXTO ----*/
//
//        std::string nombreFich = "quijote-sin-simbolos.txt";
//        GestorTextos gestor1;
//        int pos = gestor1.addDocumento(nombreFich);
//        
//        gestor1.getDocumento(pos)->chequearTexto();
//        
//        cout<<"TAMAÑO DEL DICCIONARIO ACTUAL --> "<<gestor1.getDiccionario()->tamTerminos()<<endl;
//        
//        nombreFich = "cañasYbarro.txt";
//        pos = gestor1.addDocumento(nombreFich);
//        gestor1.getDocumento(pos)->chequearTexto();
//        
//        cout<<"TAMAÑO DEL DICCIONARIO ACTUAL --> "<<gestor1.getDiccionario()->tamTerminos()<<endl;
//        
//        /*---- NUMERO DE OCURRENCIAS DE MANCHA Y ESTABAN ----*/
//        
//        Palabra *mancha = nullptr;
//        string _mancha = "mancha"; //SEGÚN HE COMPROBADO UNA A UNA DEL DOCUMENTO, SALEN 175 (TOTAL 183 CON: 2 MANCHAS,1 MANCHASE, 1 MANCHADO, 4 MANCHADA).
//        gestor1.getDiccionario()->buscarTermino(_mancha,mancha);
//        
//        if(mancha)
//            cout<<"Ocurrencias de mancha -> "<<mancha->GetOcurrencias()-1<<endl;
//        
//        Palabra *estaban = nullptr;
//        string _estaban = "estaban"; //COMRPOBADO QUE TIENE QUE SALIR 175 PORQUE AL BUSCAR SALEN 178 (ESTABAN,ESTABANLE,PRESTABAN,RECUESTABAN).
//        gestor1.getDiccionario()->buscarTermino(_estaban,estaban);
//        
//        if(estaban)
//            cout<<"Ocurrencias de estaban -> "<<estaban->GetOcurrencias()-1<<endl; //RESTO 1 PORQUE CADA VEZ QUE BUSCA EL TERMINO Y LO ENCUENTRA INCREMENTA SU OCURRENCIA.
//        
//        
//        /*---- BUSCAR Y MOSTRAR POR CONSOLA LA FAMILIA DE PALABRAS QUE SE QUIERA POR CONSOLA ----*/
//        
//        cout<<endl<<endl<<"FAMILIA DE PALABRAS DE --> FLOR"<<endl;
//        string _buscar = "flor";
//        list<Palabra> *familia = new list<Palabra>();
//        gestor1.buscarFamilias(_buscar, familia);
//        list<Palabra>::iterator it = familia->begin();
//        while (it != familia->end()) {
//            cout << it->GetPalabra() << "  ";
//            ++it;
//        }
//        delete familia;
//        familia = new list<Palabra>();
//        
//        cout<<endl<<endl<<"FAMILIA DE PALABRAS DE --> SAL"<<endl;
//        _buscar = "sal";
//        gestor1.buscarFamilias(_buscar, familia);
//        it = familia->begin();
//        while (it != familia->end()) {
//            cout << it->GetPalabra() << "  ";
//            ++it;
//        }
//        delete familia;
//        familia = new list<Palabra>();
//        
//        
//        cout<<endl<<endl<<"FAMILIA DE PALABRAS DE --> MAR"<<endl;
//        _buscar = "mar";
//        gestor1.buscarFamilias(_buscar, familia);
//
//        it = familia->begin();
//        while (it != familia->end()) {
//            cout << it->GetPalabra() << "  ";
//            ++it;
//        }
//        delete familia;
//        familia = nullptr;
//        
//        /*---- MOSTRAR POR CONSOLA LAS PALABRAS INEXISTENTES AÑADIDAS AL DICCIONARIO Y DEL DOCUMENTO DEL QUE VIENEN ----*/
//        
//        cout<<endl<<endl<<endl<<endl<<"--------- PALABRAS INEXISTENTES AÑADIDAS AL DICCIONARIO --------"<<endl<<endl;
//        gestor1.getDiccionario()->mostrarDiccionario();
//      
//         
//    }catch (invalid_argument &e){
//        cout<<e.what()<<endl;
//    }
//    catch (logic_error &e){
//        cout<<e.what()<<endl;
//    }
//    catch (runtime_error &e){
//        cout<<e.what()<<endl;
//    }
//    catch(exception &e){
//        cout<<e.what()<<endl;
//    }
    
    
    return 0;
}
