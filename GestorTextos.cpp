/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GestorTextos.cpp
 * Author: spdlc
 * 
 * Created on 20 de octubre de 2020, 18:02
 */

#include <ctype.h>

#include "GestorTextos.h"


GestorTextos::GestorTextos(): diccionario("dicc-espanol-sin.txt"), texto("quijote-sin-simbolos.txt"){
    
}

GestorTextos::GestorTextos(const GestorTextos& orig) {
    diccionario = orig.diccionario;
    texto = orig.texto;
}

/**
 * @brief Chequear texto.
 * @post A partir de 2 nombres de textos pasados como parametros, uno referenciará al diccionario y el otro corresponderá al texto. Una vez
 * se haya insertado todas las palabras en el diccionario se comparará una a una las palabras del texto. Cada vez que se encuentre
 * una palabra del texto la cuál es limpiada (y puesta en minúscula auxiliarmente), se añadirá en una lista de inexistentes palabras en el 
 * objeto referente al Documento; es decir, en el texto.
 */
void GestorTextos::chequearTexto () {
    
    ifstream is("quijote-sin-simbolos.txt");
    texto.setNombreFich("quijote-sin-simbolos.txt");
    string palabra;
    Palabra pal;
    clock_t t_ini = clock();
    int no_validadas = 0, total = 0, p;
    while (is) {
        is >> palabra;
        pal.SetPalabra(palabra);
        ++total;
        /*Ahora limpio la palabra para comprobar si existe en el diccionario.*/
        pal.limpiar();

        if (!getDiccionario().buscarDicotomica(pal.conversionMinus())) {
            ++no_validadas;
            getTexto().addInexistente(pal);
        }
    }
    cout << "Total palabras: " << total << " --------- Total de palabras no_validadas: " << no_validadas << endl;
    cout << "Tiempo para chequear el texto: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
        
}

/**
 * @brief Destructor.
 */
GestorTextos::~GestorTextos() {
}


/*---- GETTERS Y SETTERS ----*/

void GestorTextos::setTexto(Documento texto) {
    this->texto = texto;
}

Documento& GestorTextos::getTexto(){
    return texto;
}

void GestorTextos::setDiccionario(Diccionario diccionario) {
    this->diccionario = diccionario;
}

Diccionario& GestorTextos::getDiccionario(){
    return diccionario;
}