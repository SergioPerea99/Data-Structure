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


GestorTextos::GestorTextos():diccionario("dicc-espanol-sin.txt"), documentos(){
}

GestorTextos::GestorTextos(const GestorTextos& orig) {
    diccionario = orig.diccionario;
    documentos = orig.documentos;
}

/**
 * @brief Chequear texto.
 * @post A partir de 2 nombres de textos pasados como parametros, uno referenciará al diccionario y el otro corresponderá al texto. Una vez
 * se haya insertado todas las palabras en el diccionario se comparará una a una las palabras del texto. Cada vez que se encuentre
 * una palabra del texto la cuál es limpiada (y puesta en minúscula auxiliarmente), se añadirá en una lista de inexistentes palabras en el 
 * objeto referente al Documento; es decir, en el texto.
 */
//void GestorTextos::chequearTexto (int pos) {
//    ifstream is(documentos[pos].getNombreFich());
//    string palabra;
//    Palabra pal;
//    clock_t t_ini = clock();
//    int no_validadas = 0, total = 0, p;
//    while (is) {
//        is >> palabra;
//        pal.SetPalabra(palabra);
//        ++total;
//        /*Ahora limpio la palabra para comprobar si existe en el diccionario.*/
//        pal.limpiar();
//
//        if (!getDiccionario().buscarDicotomica(pal.conversionMinus())) {
//            ++no_validadas;
//            documentos[pos].addInexistente(pal);
//        }
//    }
//    cout << "Total palabras: " << total << " --------- Total de palabras no_validadas: " << no_validadas << endl;
//    cout << "Tiempo para chequear el texto: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
//        
//}

/**
 * @brief Insertar documento.
 * @post Añade un documento al final de los elementos del vector. Es importante saber
 * que desde la misma acción de añadir el documento, se está añadiendo el diccionario
 * asociado a ese documento.
 * @param nombreFich String que se quiere añadir a la estructura como Documento.
 */
int GestorTextos::addDocumento(std::string nombreFich){
    Documento *doc = new Documento(nombreFich, getDiccionario()); 
    documentos.insertar(doc,documentos.tam()); 
    return documentos.tam()-1;
}

/**
 * @brief Buscar documento.
 * @post Busca un documento de forma secuencial en el vector dinámico que almacena los 
 * documentos del gestor de textos.
 * @param nombreFich Nombre del documento que se quiere buscar.
 * @return Documento que se ha buscado, en caso de no encontrarlo se lanza una excepción.
 */
Documento* GestorTextos::buscarDocumento(std::string nombreFich){
    Documento *texto_buscar =  new Documento(nombreFich,getDiccionario());
    if(documentos.buscar(texto_buscar)){
        delete texto_buscar;
        return texto_buscar;
    }
    delete texto_buscar;
    return nullptr;
}



/**
 * @brief Destructor.
 */
GestorTextos::~GestorTextos() {
    for (int i = 0; i < documentos.tam(); i++)
        delete documentos[i];
}


/*---- GETTERS Y SETTERS ----*/



void GestorTextos::setDiccionario(Diccionario& diccionario) {
    this->diccionario = diccionario;
}

Diccionario* GestorTextos::getDiccionario(){
    return &diccionario;
}


VDinamico<Documento*> GestorTextos::getDocumentos(){
    return documentos;
}