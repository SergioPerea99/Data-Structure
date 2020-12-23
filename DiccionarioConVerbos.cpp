/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Diccionario.cpp
 * Author: spdlc
 * 
 * Created on 20 de octubre de 2020, 18:06
 */

#include <time.h>
#include <list>

#include "DiccionarioConVerbos.h"
#include "Documento.h"

/**
 * @brief Constructor por defecto.
 */
DiccionarioConVerbos::DiccionarioConVerbos(): terminos(),nombreDicc("dicc-espanol-sin.txt"), nombreDiccVerbos("verbos_conjugados_sin_tildes_desordenados.txt"){
    
    /*Primera parte: Cargar las palabras del diccionario en el map.*/
    ifstream is(nombreDicc);
    string palabra;
    Palabra *pal = nullptr;
    while (is) {
        is >> palabra;
        pal = new Palabra(palabra);
        pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insert(palab);
    }
    is.close();
    
    /*Segunda parte: cargar los verbos conjugados en el map.*/
    is.open(nombreDiccVerbos);
    while (is) {
        is >> palabra;
        pal = new Palabra(palabra);
        pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insert(palab);
    }
    is.close();
    
    cout <<"DICCIONARIO: "<< terminos.size() << " palabras cargadas en los TERMINOS del diccionario." << endl;
}


/**
 * @brief Constructor parametrizado.
 * @param _nombreFich String que indica el nombre del diccionario.
 */
DiccionarioConVerbos::DiccionarioConVerbos(std::string _nombreDicc, std::string _nombreDiccVerbos): terminos(), nombreDicc (_nombreDicc), nombreDiccVerbos(_nombreDiccVerbos) {
    
    /*Primera parte: Cargar palabras del diccionario en el map.*/
    ifstream is(nombreDicc);
    string palabra;
    Palabra *pal = nullptr;
    while (is) {
        is >> palabra;
        pal = new Palabra(palabra);
        pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insert(palab);
    }
    is.close();
    
    /*Segunda parte: cargar los verbos conjugados en el map.*/
    is.open(nombreDiccVerbos);
    while (is) {
        is >> palabra;
        pal = new Palabra(palabra);
        pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insert(palab);
    }
    is.close();
    
    cout << terminos.size() << " palabras cargadas en los TERMINOS del diccionario." << endl;
}

/**
 * @brief Constructor copia.
 * @param orig Diccionario a copiar.
 */
DiccionarioConVerbos::DiccionarioConVerbos(const DiccionarioConVerbos& orig) : nombreDicc(orig.nombreDicc) , 
        nombreDiccVerbos(orig.nombreDiccVerbos), 
        terminos (orig.terminos){
    
}

/**
 * @brief Destructor.
 * @post Se destruye, en caso de haber sido reservado memoria para ello, los verbos
 * los cuales formaban parte del diccionario.
 */
DiccionarioConVerbos::~DiccionarioConVerbos() {
    map<std::string, Palabra*>::iterator it = terminos.begin();
    while(it != terminos.end()){
        delete it->second;
        terminos.erase(it); 
        it = terminos.lower_bound(it->first); 
    }
}


/**
 * @brief Operador de asignación.
 * @param orig Diccionario a ser asignado por el destinatario.
 * @return 
 */
DiccionarioConVerbos& DiccionarioConVerbos::operator =(const DiccionarioConVerbos& orig){
    if (this != &orig){
        nombreDicc = orig.nombreDicc;
        nombreDiccVerbos = orig.nombreDiccVerbos;
        terminos = orig.terminos;
        
    }
}

/**
 * @brief Buscar un término.
 * @post Busca la clave pasada como parámetro en el map de forma que si la encuentra, asigna el valor del dato en result y devuelve un true.
 * @param termino Clave a buscar.
 * @param result Palabra encontrada, en caso de encontrarse.
 * @return Booleano que indica si se ha encontrado o no.
 */
Palabra* DiccionarioConVerbos::buscarTermino(string& termino, Usuario& u){
    map<std::string, Palabra*>::iterator ite = terminos.find(termino);
    if(ite != terminos.end()){
        ite->second->incrementarOcurrencia();
        ite->second->insertarUsuario(u); //Insertamos (si no está ya) el usuario a la lista de usuarios de esta palabra.
        return ite->second;
    }else
        return nullptr; //TODO: PUEDE QUE HAYA QUE AQUI AÑADIR LA PALABRA AL MAPA Y EL USUARIO A LA LISTA DE LA PALABRA NUEVA AÑADIDA
}


Palabra* DiccionarioConVerbos::insertarInexistente(std::string& termino, Usuario& u){
    Palabra *aniadir = new Palabra(termino);
    pair<std::string, Palabra*> palab(aniadir->GetPalabra(),aniadir);
    aniadir->insertarUsuario(u); //Inserta el usuario que ha usado la palabra en la lista de usuarios que han usado esa palabra.
    aniadir->incrementarOcurrencia(); /*Numero de veces que ha aparecido: 1.*/
    return aniadir;
}

Palabra* DiccionarioConVerbos::buscarPalabra(std::string& termino){
    std::map<std::string,Palabra*>::iterator it = terminos.find(termino);
    if(it != terminos.end())
        return (*it).second;
    return nullptr;
}

/*---- GETTERS Y SETTERS ----*/

void DiccionarioConVerbos::SetNombreFich(std::string nombreFich) {
    nombreDicc = nombreFich;
}

std::string DiccionarioConVerbos::GetNombreFich() const {
    return nombreDicc;
}

void DiccionarioConVerbos::setNombreDiccVerbos(std::string nombreDiccVerbos) {
    nombreDiccVerbos = nombreDiccVerbos;
}

std::string DiccionarioConVerbos::getNombreDiccVerbos() const {
    return nombreDiccVerbos;
}


int DiccionarioConVerbos::tamTerminos(){
    return terminos.size();
}


void DiccionarioConVerbos::mostrarDiccionario(){
    std::map<std::string,Palabra*>::iterator it = terminos.begin();
    while (it != terminos.end()){
        cout<<"["<<it->second->GetPalabra()<<"]  ";
        it++;
    }
}