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
DiccionarioConVerbos::DiccionarioConVerbos(): terminos(){
    nombreDicc = "dicc-espanol-sin.txt";
    nombreDiccVerbos = "verbos_conjugados_sin_tildes_desordenados.txt";
    
    /*Primera parte: Cargar las palabras del diccionario en el map.*/
    ifstream is(nombreDicc);
    string palabra;
    Palabra *pal = nullptr;
    while (is) {
        is >> palabra;
        pal = new Palabra(palabra,this);
        pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insert(palab);
    }
    is.close();
    
    /*Segunda parte: cargar los verbos conjugados en el map.*/
    is.open(nombreDiccVerbos);
    while (is) {
        is >> palabra;
        pal = new Palabra(palabra,this);
        pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insert(palab);
    }
    is.close();
    
    cout << terminos.size() << " palabras cargadas en los TERMINOS del diccionario." << endl;
}


/**
 * @brief Constructor parametrizado.
 * @param _nombreFich String que indica el nombre del diccionario.
 */
DiccionarioConVerbos::DiccionarioConVerbos(std::string _nombreDicc, std::string _nombreDiccVerbos): terminos(){
    nombreDicc = _nombreDicc;
    nombreDiccVerbos = _nombreDiccVerbos;
    
    /*Primera parte: Cargar palabras del diccionario en el map.*/
    ifstream is(nombreDicc);
    string palabra;
    Palabra *pal = nullptr;
    while (is) {
        is >> palabra;
        pal = new Palabra(palabra,this);
        pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insert(palab);
    }
    is.close();
    
    /*Segunda parte: cargar los verbos conjugados en el map.*/
    is.open(nombreDiccVerbos);
    while (is) {
        is >> palabra;
        pal = new Palabra(palabra,this);
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
DiccionarioConVerbos::DiccionarioConVerbos(const DiccionarioConVerbos& orig) {
    nombreDicc = orig.nombreDicc;
    nombreDiccVerbos = orig.nombreDiccVerbos;    
    terminos = orig.terminos;
}

/**
 * @brief Destructor.
 * @post Se destruye, en caso de haber sido reservado memoria para ello, los verbos
 * los cuales formaban parte del diccionario.
 */
DiccionarioConVerbos::~DiccionarioConVerbos() {
    map<std::string, Palabra*>::iterator it = terminos.begin();
    while(it != terminos.end()){
        terminos.erase(it); /*DUDA: Si he eliminado con erase pero he creado un new de Palabras en esta clase para almacenarlo en esos nodos del mapa, ¿con el erase no haría falta liberar su memoria?*/
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
bool DiccionarioConVerbos::buscarTermino(string termino, Palabra* result){
    map<std::string, Palabra*>::iterator ite = terminos.find(termino);
    if(ite != terminos.end()){
        result = ite->second;
        return true;
    }else
        return false;
}


/**
 * @brief Buscar familia de una palabra.
 * @post A partir de una subcadena raiz, devolver una lista de todas las palabras
 * que contienen como subcadena raiz la misma que la pasada como parámetro.
 * @param raiz String a buscar como subcadena en el map.
 * @return Lista de palabras que forman la familia.
 */
list<Palabra> DiccionarioConVerbos::buscarFamilias(std::string raiz){
    map<std::string, Palabra*>::iterator it = terminos.find(raiz);
    list<Palabra> copiar;
    std::string comprobar = it->first; /*Creo una variable para no hacer operaciones con el iterador.*/
    while(comprobar.substr(0,raiz.length()-1) == raiz){ /*Supongo que al iterar hacia abajo o encuentra el final o sale por donde empezó.*/
        copiar.push_back(*it->second); /*Copio la palabra en la lista ya que sigue en el bucle que comprueba que es de la familia.*/
        it = terminos.lower_bound(it->first); /*Paso al siguiente dato.*/
        comprobar = it->first; /*Copio la nueva clave, para ver en el condicional si sigue siendo de la familia.*/
    }
    return copiar;
}


Palabra* DiccionarioConVerbos::insertarInexistente(Palabra& dato){
    Palabra *aniadir = new Palabra(dato); /*DUDA: ¿La palabra inexistente sólo tendrá asignado el documento de donde viene pero no el diccionario al que se está añadiendo?*/
    terminos.insert(pair<std::string,Palabra*>(aniadir->GetPalabra(),aniadir));
    aniadir->incrementarOcurrencia(); /*Numero de veces que ha aparecido: 1.*/
    return aniadir;
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


map<std::string,Palabra*>::iterator DiccionarioConVerbos::it_Begin(){
    return terminos.begin();
}

map<std::string,Palabra*>::iterator DiccionarioConVerbos::it_End(){
    return terminos.end();
}