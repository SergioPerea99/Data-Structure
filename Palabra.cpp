/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Palabra.cpp
 * Author: spdlc
 * 
 * Created on 5 de octubre de 2020, 19:20
 */

#include <string.h>

#include "Palabra.h"
#include "VDinamico.h"

/**
 * @brief Constructor por defecto.
 */
Palabra::Palabra() {
    palabra = "";
}

/**
 * @brief Constructor parametrizado.
 * @param _palabra String a asignar al atributo.
 */
Palabra::Palabra(string _palabra){
    palabra = _palabra;
}

/**
 * @brief Constructor de copia.
 * @param orig Palabra que se quiere copiar.
 */
Palabra::Palabra(const Palabra& orig) {
    palabra = orig.palabra;
}

/**
 * @brief Destructor.
 */
Palabra::~Palabra() {
}

/**
 * @brief Getter de atributo palabra.
 * @return String.
 */
string Palabra::GetPalabra() const {
    return palabra;
}

/**
 * @brief Setter de atributo palabra.
 * @param palabra String a asignar al atributo.
 */
void Palabra::SetPalabra(string palabra) {
    this->palabra = palabra;
}

/**
 * @brief Operador de comparación de igualdad.
 * @param dato Palabra a comparar.
 * @return Booleano.
 */
bool Palabra::operator ==(const Palabra& dato){
    if (palabra == dato.GetPalabra())
        return true;
    return false;
}

/**
 * @brief Operador de comparación <.
 * @param dato Palabra a comparar.
 * @return Booleano.
 */
bool Palabra::operator <(const Palabra& dato){
    if (palabra < dato.GetPalabra())
        return true;
    return false;
}

/**
 * @brief Operador de comparación >.
 * @param dato Palabra a comparar.
 * @return Booleano.
 */
bool Palabra::operator >(const Palabra& dato){
    if (palabra > dato.GetPalabra())
        return true;
    return false;
}

/**
 * @brief Operador de asignación.
 * @param dato Palabra a asignar.
 * @return El contenido del objeto de la clase que ha llamado al método.
 */
Palabra& Palabra::operator =(const Palabra& dato){
    palabra = dato.palabra;
    return *this;
}

/**
 * @brief Operador de comparación <=.
 * @param dato Palabra a comparar.
 * @return Booleano.
 */
bool Palabra::operator <=(const Palabra& dato){
    if (palabra <= dato.GetPalabra())
        return true;
    return false;
}

/**
 * @brief Operador de comparación >=.
 * @param dato Palabra a comparar.
 * @return Booleano.
 */
bool Palabra::operator >=(const Palabra& dato){
    if(palabra >= dato.GetPalabra())
        return true;
    return false;
}


/**
 * @brief Palíndromo.
 * @post Método que indica si una palabra respecto a otra es palíndromo o no.
 * @param pal Palabra a comprobar.
 * @return Booleano.
 */
bool Palabra::palindromo(Palabra& pal){
    Palabra aux(pal);
    Palabra aux2 = aux.reves();
    if(aux2.GetPalabra() == palabra)
        return true;
    return false;
}

/**
 * @brief Al revés.
 * @post Método encargado de colocar una palabra de forma inversa (ayudante para el método palíndromo).
 * @return Palabra inversa.
 */
Palabra Palabra::reves(){
    char aux;
    int i = 0, j = palabra.length()-1;
    while(i <= j){
        aux = palabra[i];
        palabra[i++] = palabra[j];
        palabra[j--] = aux;
        
    }
    return *this;
}

/**
 * @brief Anagrama.
 * @post Método que indica si una palabra respecto a otra es anagrama o no.
 * @param pal Palabra a comparar.
 * @return Booleano que indica si es o no anagrama.
 */
bool Palabra::anagrama(Palabra& pal){
    string palabra2 = pal.GetPalabra();
    string palabra1 = palabra;
    std::sort(palabra2.begin(),palabra2.end());
    std::sort(palabra1.begin(),palabra1.end());
    if (palabra1 == palabra2)
        return true;
    return false;
}


