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
#include <ctype.h>

#include "Palabra.h"
#include "VDinamico.h"

#include "DiccionarioConVerbos.h"
#include "Documento.h"

/**
 * @brief Constructor por defecto.
 */
Palabra::Palabra(): palabra (""), ocurrencias (0), dicc_perteneciente (nullptr), ultima_aparicion (nullptr){

}

/**
 * @brief Constructor parametrizado.
 * @param _palabra String a asignar al atributo.
 */
Palabra::Palabra(string _palabra, DiccionarioConVerbos *_diccPerteneciente): palabra (_palabra), ocurrencias(0), dicc_perteneciente(_diccPerteneciente), ultima_aparicion (nullptr){

}

/**
 * @brief Constructor de copia.
 * @param orig Palabra que se quiere copiar.
 */
Palabra::Palabra(const Palabra& orig): palabra (orig.palabra), ocurrencias (orig.ocurrencias), dicc_perteneciente (orig.dicc_perteneciente), ultima_aparicion (orig.ultima_aparicion){

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

/**
 * @brief Limpiar Palabra.
 * @post Limpia una palabra de los caracteres que no corresponden al alfabeto.
 */
void Palabra::limpiar(){
    
    int incorrectos = 0;
    for (int i = 0 ; i < palabra.length(); i++){
        if(!isalpha(palabra[i])){
            incorrectos++;
        }else
            break;
        
    }
    palabra.erase(palabra.begin(),palabra.begin()+incorrectos);
    incorrectos = 0;
    for (int i = palabra.length()-1 ; i >= 0; i--){
        if (!isalpha(palabra[i]) ){
            incorrectos++;
        }else
            break;
    }
    palabra.erase(palabra.end()-incorrectos,palabra.end());
   
}

/**
 * @brief Pasar a Minúsculas una palabra.
 * @post A partir de la Palabra que llama al método, se genera una copia auxiliar de ella en minúsculas todas sus letras.
 * @return Palabra auxiliar devuelta con todas las letras en minúscula.
 */
string Palabra::conversionMinus(){
    string minus = GetPalabra();
    std::transform(minus.begin(),minus.end(),minus.begin(), ::tolower);
    return minus;
}

/**
 * @brief Destructor.
 */
Palabra::~Palabra() {
}
    

/*---- OPERADORES DE ASIGNACIÓN, COMPROBACIÓN Y MUESTRAS POR PANTALLA ----*/

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
 * @brief Operador de mostrar por pantalla.
 * @post A partir del atributo string de la Palabra que es lo que se quiere mostrar,
 *  se recoge su valor en un ostream para poder realizar la muestra por pantalla de ello.
 * @param os
 * @param f
 * @return 
 */
ostream &operator<<(ostream &os, const Palabra &f)
{
	os << f.GetPalabra();
	return os;
}


/*---- GETTERS Y SETTERS ----*/

/**
 * @brief Getter de atributo palabra.
 * @return String.
 */
string Palabra::GetPalabra() const{
    return palabra;
}

/**
 * @brief Setter de atributo palabra.
 * @param palabra String a asignar al atributo.
 */
void Palabra::SetPalabra(string palabra) {
    palabra = palabra;
}

void Palabra::incrementarOcurrencia() {
    ++ocurrencias;
}

int Palabra::GetOcurrencias() const {
    return ocurrencias;
}

DiccionarioConVerbos* Palabra::GetDicc_perteneciente() const {
    return dicc_perteneciente;
}

void Palabra::SetUltima_aparicion(Documento* ultima_aparicion) {
    this->ultima_aparicion = ultima_aparicion;
}

Documento* Palabra::GetUltima_aparicion() const {
    return ultima_aparicion;
}