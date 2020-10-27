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

#include "Diccionario.h"

/**
 * @brief Constructor por defecto.
 */
Diccionario::Diccionario() {
    nombreFich = "dicc-espanol-sin.txt";
    /*Primera parte: Cargar el diccionario en el Gestor de Textos.*/
    ifstream is("dicc-espanol-sin.txt");
    string palabra;
    Palabra pal;
    while (is) {
        is >> palabra;
        pal.SetPalabra(palabra);
        GetTerminos().insertar(pal);
    }
    /*Ordenación para poder luego buscar en él con una búsqueda binaria.*/
    GetTerminos().ordenar();
    cout << GetTerminos().tam() << " palabras cargadas en los TERMINOS del diccionario." << endl;
    is.close();
}

/**
 * @brief Constructor parametrizado.
 * @param _nombreFich String que indica el nombre del diccionario.
 */
Diccionario::Diccionario(std::string _nombreFich) {
    nombreFich = _nombreFich;
    /*Primera parte: Cargar el diccionario en el Gestor de Textos.*/
    ifstream is(_nombreFich);
    string palabra;
    Palabra pal;
    while (is) {
        is >> palabra;
        pal.SetPalabra(palabra);
        GetTerminos().insertar(pal);
    }
    /*Ordenación para poder luego buscar en él con una búsqueda binaria.*/
    GetTerminos().ordenar();
    cout << GetTerminos().tam() << " palabras cargadas en los TERMINOS del diccionario." << endl;
    is.close();
}

/**
 * @brief Constructor copia.
 * @param orig Diccionario a copiar.
 */
Diccionario::Diccionario(const Diccionario& orig) {
    nombreFich = orig.nombreFich;
    terminos = orig.terminos;
}

/**
 * @brief Destructor.
 */
Diccionario::~Diccionario() {
}

/**
 * @brief Busqueda dicotómica.
 * @post Busqueda logarítmica que a su vez llamará al búsqueda binaria de la estructura de datos del vector dinámico.
 * @param buscar Dato de tipo Palabra que se quiere buscar.
 * @return Booleano que expresa si se ha encontrado o no.
 */
bool Diccionario::buscarDicotomica(Palabra buscar){
    //Suponemos que el vector de palabras debe de estar ordenado para su llamada.
    int pos = terminos.busquedaBin(buscar);
    if(pos != -1)
        return true;
    return false;
}


/*---- GETTERS Y SETTERS ----*/

VDinamico<Palabra>& Diccionario::GetTerminos(){
    return terminos;
}

void Diccionario::SetNombreFich(std::string nombreFich) {
    this->nombreFich = nombreFich;
}

std::string Diccionario::GetNombreFich() const {
    return nombreFich;
}