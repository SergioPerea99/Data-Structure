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
#include <list>

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
        
        /*1. Carga los datos de todos los usuarios del fichero adjunto en Ziri*/
        /*2. Conectar a todos los usuarios excepto los 50 últimos*/
        Ziri ziri; //Conectando previamente a todos menos los 50 últimos.
        ziri.login();
        /*3. Intenta conectar al usuario que si existe con NIF = 34923452L y  clave pU7Pqq.*/
        std::string nif = "34923452L";
        std::string pass = "pU7Pqq";
        try{
            ziri.nuevoUsuarioConectado(nif,pass);
        }catch (invalid_argument& e){
            cout<<e.what()<<endl;
        }
        /*4. Hacer que los usuarios conectados escriban un mensaje*/
        for (int i = 0; i < ziri.tamUserConectados(); i++) {
            ziri.userConectado(i).escribeMensaje();
        }
        
        /*5. Muestra por pantalla los usuarios conectados que han escrito la palabra "casa"*/
        std::string analizar = "casa";
        std::list<Usuario>* list_users = ziri.analizarTermino(analizar);
        if (list_users){
            for (std::list<Usuario>::iterator it = list_users->begin(); it != list_users->end(); it++){
                cout<<(*it).getNif()<<" :: "<<(*it).getFrase()<<endl;
            }
           cout<<"NÚMERO DE USUARIOS QUE HAN DICHO LA PALABRA "<<analizar<<" -> "<<list_users->size()<<endl;
           cout<<endl;
        }
        
        
        /*6. Muestra por consola los datos de todos los usuarios que han escrito un mensaje en el rango de Jaén*/
        std::string buscar = "ganas";
        list_users = ziri.buscarTerminoRango(buscar,37,3,38,4);
        if (list_users){
            for (std::list<Usuario>::iterator it = list_users->begin(); it != list_users->end(); it++){
                cout<<(*it).getNif()<<" :: "<<(*it).getFrase()<<endl;
            }
           cout<<"NÚMERO DE USUARIOS EN EL RANGO DE JAÉN QUE HAN DICHO LA PALABRA "<<buscar<<" -> "<<list_users->size();
           cout<<" ( respecto al numero total de ocurrencias = "<<ziri.getGestor()->getDiccionario()->buscarPalabra(buscar)->GetOcurrencias()<<" )"<<endl;
           cout<<endl;
        }
        
        buscar = "extranjero";
        list_users = ziri.buscarTerminoRango(buscar,37,3,38,4);
        if (list_users){
            for (std::list<Usuario>::iterator it = list_users->begin(); it != list_users->end(); it++){
                cout<<(*it).getNif()<<" :: "<<(*it).getFrase()<<endl;
            }
           cout<<"NÚMERO DE USUARIOS EN EL RANGO DE JAÉN QUE HAN DICHO LA PALABRA "<<buscar<<" -> "<<list_users->size();
           cout<<" ( respecto al numero total de ocurrencias = "<<ziri.getGestor()->getDiccionario()->buscarPalabra(buscar)->GetOcurrencias()<<" )"<<endl;
           cout<<endl;
        }
        
        buscar = "es";
        list_users = ziri.buscarTerminoRango(buscar,37,3,38,4);
        if (list_users){
            for (std::list<Usuario>::iterator it = list_users->begin(); it != list_users->end(); it++){
                cout<<(*it).getNif()<<" :: "<<(*it).getFrase()<<endl;
            }
           cout<<"NÚMERO DE USUARIOS EN EL RANGO DE JAÉN QUE HAN DICHO LA PALABRA "<<buscar<<" -> "<<list_users->size();
           cout<<" ( respecto al numero total de ocurrencias = "<<ziri.getGestor()->getDiccionario()->buscarPalabra(buscar)->GetOcurrencias()<<" )"<<endl;
           cout<<endl;
        }
        
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
