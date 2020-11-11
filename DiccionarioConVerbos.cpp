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

#include "DiccionarioConVerbos.h"
#include "Documento.h"

/**
 * @brief Constructor por defecto.
 */
DiccionarioConVerbos::DiccionarioConVerbos(): terminos(){
    nombreDicc = "dicc-espanol-sin.txt";
    nombreDiccVerbos = "verbos_conjugados_sin_tildes_desordenados.txt";
    /*Primera parte: Cargar el diccionario en el Gestor de Textos.*/
    ifstream is(nombreDicc);
    string palabra;
    Palabra *pal = nullptr;
    while (is) {
        is >> palabra;
        Palabra *pal = new Palabra(palabra);
        pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insert(palab);
    }
    
    cout << terminos.size() << " palabras cargadas en los TERMINOS del diccionario." << endl;
    is.close();
}


/**
 * @brief Constructor parametrizado.
 * @param _nombreFich String que indica el nombre del diccionario.
 */
DiccionarioConVerbos::DiccionarioConVerbos(std::string _nombreDicc, std::string _nombreDiccVerbos): terminos(){
    nombreDicc = _nombreDicc;
    nombreDiccVerbos = _nombreDiccVerbos;
    /*Primera parte: Cargar el diccionario en el Gestor de Textos.*/
    ifstream is(nombreDicc);
    string palabra;
    Palabra *pal = nullptr;
    while (is) {
        is >> palabra;
        pal = new Palabra(palabra);
        pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insert(palab);
    }
    
    cout << terminos.size() << " palabras cargadas en los TERMINOS del diccionario." << endl;
    is.close();
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

bool DiccionarioConVerbos::buscar(string termino, Palabra *result){
    std::map<std::string, Palabra*>::iterator ite = terminos.find(termino);
    if(ite != terminos.end()){
        result = ite->second;
        return true;
    }else
        return false;
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
