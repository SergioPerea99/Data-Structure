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
#include <vector>

#include "GestorTextos.h"

/**
 * @brief Constructor por defecto.
 */
GestorTextos::GestorTextos():diccionarios(), documentos(){
}

/**
 * @brief Constructor copia.
 * @param orig GestorTextos a ser copiado por el destinatario.
 */
GestorTextos::GestorTextos(const GestorTextos& orig) {
    diccionarios = orig.diccionarios;
    documentos = orig.documentos;
}


/**
 * @brief Insertar documento.
 * @post Añade un documento al final de los elementos del vector. Es importante saber
 * que desde la misma acción de añadir el documento, se está añadiendo el diccionario
 * asociado a ese documento.
 * @param nombreFich String que se quiere añadir a la estructura como Documento.
 */
int GestorTextos::addDocumento(std::string nombreFich){
    Documento *doc = new Documento(nombreFich, getDiccionario(0)); /*Ya que solo metemos uno, le corresponde al primer elemento.*/
    documentos.push_back(doc);
    return documentos.size()-1;
}

/**
 * @brief Insertar documento.
 * @post Añade un documento al final de los elementos del vector. Es importante saber
 * que desde la misma acción de añadir el documento, se está añadiendo el diccionario
 * asociado a ese documento.
 * @param nombreFich String que se quiere añadir a la estructura como Documento.
 */
int GestorTextos::addDiccionario(std::string nombreDicc, std::string nombreDiccVerbos){
    DiccionarioConVerbos *doc = new DiccionarioConVerbos(nombreDicc,nombreDiccVerbos); 
    diccionarios.push_back(doc);
    return diccionarios.size()-1;
}


/**
 * @brief Buscar documento.
 * @post Busca un documento de forma secuencial en el vector dinámico que almacena los 
 * documentos del gestor de textos.
 * @param nombreFich Nombre del documento que se quiere buscar.
 * @return Documento que se ha buscado, en caso de no encontrarlo se lanza una excepción.
 */
Documento* GestorTextos::buscarDocumento(std::string nombreFich){
    Documento *texto_buscar =  new Documento(nombreFich,getDiccionario(0));
    for(int i = 0; i < documentos.size(); i++){
        if (*documentos[i] == *texto_buscar){
            delete texto_buscar;
            return documentos[i];
        }
    }
    delete texto_buscar;
    return nullptr;
}

/**
 * @brief Destructor.
 * @post Destruye los objetos documento creados que habían sido añadidos al vector dinámico documentos.
 */
GestorTextos::~GestorTextos() {
    for (int i = 0; i < documentos.size(); i++){
        if(documentos[i])
            delete documentos[i];
        documentos[i] = 0;
    }
    for(int j = 0; j < diccionarios.size(); j++){
        if(diccionarios[j])
            delete diccionarios[j];
        diccionarios[j] = 0;
    }
}


/*---- GETTERS Y SETTERS ----*/





DiccionarioConVerbos* GestorTextos::getDiccionario(unsigned int pos){
    return diccionarios[pos];
}


Documento* GestorTextos::getDocumento(unsigned int pos){
    return documentos[pos];
}

