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
GestorTextos::GestorTextos(): /*documentos(),*/ diccionario (new DiccionarioConVerbos()){

}

/**
 * @brief Constructor copia.
 * @param orig GestorTextos a ser copiado por el destinatario.
 */
GestorTextos::GestorTextos(const GestorTextos& orig): diccionario (orig.diccionario)/*,documentos (orig.documentos)*/{

}

/**
 * @brief Destructor.
 * @post Destruye los objetos documento creados que habían sido añadidos al vector dinámico documentos.
 */
GestorTextos::~GestorTextos() {
    if (diccionario)
        delete diccionario;
    diccionario = 0;
}


/**
 * @brief Buscar término.
 * @post Buscar a partir de una clave "termino" la cual es el nombre de la Palabra y devolver si es verdadero
 * o falsa dicha búsqueda. Result contendrá la palabra buscada en caso de haberse encontrado.
 * @param termino Clave del map.
 * @param result Palabra que, al ser buscada con el termino, se asigna a dicho parámetro.
 * @return Booleano que indica si se ha encontrado o no.
 */
Palabra* GestorTextos::buscarTermino(std::string& termino, Usuario& u){
    return diccionario->buscarTermino(termino,u);
}

Palabra* GestorTextos::insertarInexistente(std::string& termino, Usuario& u){
    return diccionario->insertarInexistente(termino,u);
}




/*---- GETTERS Y SETTERS ----*/


DiccionarioConVerbos*& GestorTextos::getDiccionario(){
    return diccionario;
}


//Documento* GestorTextos::getDocumento(unsigned int pos){
//    if (pos < documentos.size())
//        if (documentos[pos])
//            return documentos[pos];
//    return nullptr;
//}

