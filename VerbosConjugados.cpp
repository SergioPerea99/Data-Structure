/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VerbosConjugados.cpp
 * Author: spdlc
 * 
 * Created on 8 de noviembre de 2020, 10:48
 */

#include "VerbosConjugados.h"

/**
 * @brief Constructor por defecto.
 * @post Se crea un árbol a partir del documento indicado interiormente en el constructor, ya que 
 * no tiene el parámetro que indica de que fichero coger los verbos conjugados.
 */
VerbosConjugados::VerbosConjugados(){
    nombreFich = "verbos_conjugados_sin_tildes_desordenados.txt";
    ifstream is(nombreFich);
    string palabra;
    Palabra pal;
    while (is) {
        is >> palabra;
        pal.SetPalabra(palabra);
        vconjugados.inserta(pal);
    }
    
    std::cout << vconjugados.numElementos() << " verbos conjugados y una altura de arbol de " <<vconjugados.altura()<<"."<<endl;
    is.close();
}

/**
 * @brief Constructor parametrizado.
 * @post Se crea a partir del nombre del fichero que contiene los verbos conjugados el
 * árbol que los contendrá.
 * @param _nombreFich Nombre del fichero de que contiene los verbos conjugados.
 */
VerbosConjugados::VerbosConjugados(std::string _nombreFich){
    nombreFich = _nombreFich;
    ifstream is(nombreFich);
    string palabra;
    Palabra pal;
    while (is) {
        is >> palabra;
        pal.SetPalabra(palabra);
        vconjugados.inserta(pal);
            
    }
    
    std::cout << vconjugados.numElementos() << " verbos conjugados y una altura de arbol de " <<vconjugados.altura()<<"."<<endl;
    is.close();
}

/**
 * @brief Constructor copia.
 * @param orig VerbosConjugados a ser copiado por el destinatario.
 */
VerbosConjugados::VerbosConjugados(const VerbosConjugados& orig) {
    nombreFich = orig.nombreFich;
    vconjugados = orig.vconjugados;
}

/**
 * @brief Buscar palabra.
 * @post Busca una palabra en el árbol de palabras de forma recursiva (también podría ser usado la búsqueda iterativa)
 * llamando al método correspondiente para ello y devolviendo si se ha encontrado o no.
 * @param pal Palabra a ser buscada.
 * @return Booleano que indica si se ha encontrado o no.
 */
bool VerbosConjugados::buscar(Palabra& pal){
    Palabra encontrada;
    return vconjugados.buscaNR(pal,encontrada);
}

/**
 * ,@brief Destructor.
 */
VerbosConjugados::~VerbosConjugados() {
}

/*---- GETTERS Y SETTERS ----*/

Arbol_AVL<Palabra>* VerbosConjugados::getVconjugados(){
    return &vconjugados;
}