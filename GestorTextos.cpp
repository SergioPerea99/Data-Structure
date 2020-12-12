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
GestorTextos::GestorTextos(): documentos(), diccionario (new DiccionarioConVerbos()){

}

/**
 * @brief Constructor copia.
 * @param orig GestorTextos a ser copiado por el destinatario.
 */
GestorTextos::GestorTextos(const GestorTextos& orig): diccionario (orig.diccionario), documentos (orig.documentos) {

}


/**
 * @brief Insertar documento.
 * @post Añade un documento al final de los elementos del vector. Es importante saber
 * que desde la misma acción de añadir el documento, se está añadiendo el diccionario
 * asociado a ese documento.
 * @param nombreFich String que se quiere añadir a la estructura como Documento.
 */
int GestorTextos::addDocumento(std::string nombreFich){
    Documento *doc = new Documento(nombreFich, getDiccionario()); /*Ya que solo metemos uno, le corresponde al primer elemento.*/
    documentos.push_back(doc);
    return documentos.size()-1;
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
    for (Documento* i : documentos)
        if (*i == *texto_buscar)
            return i;
    delete texto_buscar;
    return nullptr;
}


/**
 * @brief Buscar término.
 * @post Buscar a partir de una clave "termino" la cual es el nombre de la Palabra y devolver si es verdadero
 * o falsa dicha búsqueda. Result contendrá la palabra buscada en caso de haberse encontrado.
 * @param termino Clave del map.
 * @param result Palabra que, al ser buscada con el termino, se asigna a dicho parámetro.
 * @return Booleano que indica si se ha encontrado o no.
 */
bool GestorTextos::buscarTermino(unsigned long clave,std::string termino, Palabra* &result){
    //unsigned long clave = djb2((unsigned char*)termino.c_str());
    return diccionario->buscarTermino(clave,termino,result);
}


/**
 * @brief Destructor.
 * @post Destruye los objetos documento creados que habían sido añadidos al vector dinámico documentos.
 */
GestorTextos::~GestorTextos() {
    for (Documento* i : documentos){
        if (i){
            delete i;
            i = nullptr;
        }
    }
    if (diccionario)
        delete diccionario;
    diccionario = 0;
}


unsigned long GestorTextos::djb2(unsigned char* str){
    unsigned long hash = 5381;
    int c;
    
    while (c = *str++) hash = ((hash << 5) + hash) + c;
    return hash;
}


/*---- GETTERS Y SETTERS ----*/


DiccionarioConVerbos*& GestorTextos::getDiccionario(){
    return diccionario;
}


Documento* GestorTextos::getDocumento(unsigned int pos){
    if (pos < documentos.size())
        if (documentos[pos])
            return documentos[pos];
    return nullptr;
}

