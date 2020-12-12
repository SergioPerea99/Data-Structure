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
DiccionarioConVerbos::DiccionarioConVerbos(): terminos(520513,0.601),nombreDicc("dicc-espanol-sin.txt"), nombreDiccVerbos("verbos_conjugados_sin_tildes_desordenados.txt"){
    
    /*Primera parte: Cargar las palabras del diccionario en el map.*/
    ifstream is(nombreDicc);
    string palabra;
    Palabra *pal = nullptr;
    while (is) {
        is >> palabra;
        Palabra pal (palabra,this);
        unsigned long clave = djb2((unsigned char*)pal.GetPalabra().c_str());
        terminos.insertar(clave,pal);
    }
    is.close();
    
    /*Segunda parte: cargar los verbos conjugados en el map.*/
    is.open(nombreDiccVerbos);
    while (is) {
        is >> palabra;
        Palabra pal (palabra,this);
        unsigned long clave = djb2((unsigned char*)pal.GetPalabra().c_str());
        terminos.insertar(clave,pal);
    }
    is.close();
    
    cout <<"DICCIONARIO: "<< terminos.numPalabras() << " palabras cargadas en los TERMINOS del diccionario." << endl;
}


/**
 * @brief Constructor parametrizado.
 * @param _nombreFich String que indica el nombre del diccionario.
 */
DiccionarioConVerbos::DiccionarioConVerbos(std::string _nombreDicc, std::string _nombreDiccVerbos, unsigned long tam_dicc, unsigned long tam_diccVerbos): terminos(tam_dicc+tam_diccVerbos,0.601), nombreDicc (_nombreDicc), nombreDiccVerbos(_nombreDiccVerbos) {
    
    /*Primera parte: Cargar palabras del diccionario en el map.*/
    ifstream is(nombreDicc);
    string palabra;
    Palabra *pal = nullptr;
    while (is) {
        is >> palabra;
        //pal = new Palabra(palabra,this);
        Palabra pal (palabra,this);
        //pair<std::string, Palabra*> palab(palabra,pal);
        unsigned long clave = djb2((unsigned char*)pal.GetPalabra().c_str());
        terminos.insertar(clave,pal);
    }
    is.close();
    
    /*Segunda parte: cargar los verbos conjugados en el map.*/
    is.open(nombreDiccVerbos);
    while (is) {
        is >> palabra;
        //pal = new Palabra(palabra,this);
        Palabra pal (palabra,this);
        //pair<std::string, Palabra*> palab(palabra,pal);
        unsigned long clave = djb2((unsigned char*)pal.GetPalabra().c_str());
        terminos.insertar(clave,pal);
    }
    is.close();
    
    cout << terminos.numPalabras() << " palabras cargadas en los TERMINOS del diccionario." << endl;
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
bool DiccionarioConVerbos::buscarTermino(unsigned long clave, string& termino, Palabra* &result){
    return terminos.buscar(clave,termino,result);
}

/**
 * @brief Método privado djb2.
 * @post Método encargado de la conversión de una clave de cadena de caracteres a una clave numérica.
 * @param str Cadena de caracteres.
 * @return Clave numérica.
 */
unsigned long DiccionarioConVerbos::djb2(unsigned char* str){
    unsigned long hash = 5381;
    int c;
    
    while (c = *str++) hash = ((hash << 5) + hash) + c;
    return hash;
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


int DiccionarioConVerbos::tamTerminos() const{
    return terminos.numPalabras();
}

long DiccionarioConVerbos::tamTablaHASH() const{
    return terminos.tamTabla();
}

int DiccionarioConVerbos::maxColisiones_THASH() const{
    return terminos.MaxColisiones();
}

float DiccionarioConVerbos::promColisiones_THASH() const{
    return terminos.promedioColisiones();
}