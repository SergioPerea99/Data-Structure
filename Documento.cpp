/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Documento.cpp
 * Author: spdlc
 * 
 * Created on 20 de octubre de 2020, 18:40
 */

#include "Documento.h"

/**
 * @brief Constructor por defecto.
 */
Documento::Documento() {
    nombreFich = "null";
}

/**
 * @brief Constructor copia.
 * @param orig Documento a ser copiado.
 */
Documento::Documento(const Documento& orig) {
    nombreFich = orig.nombreFich;
    inexistentes = orig.inexistentes;
}


/**
 * @brief Añadir palabra inexistente.
 * @post Añade en la estructura de la lista enlazada simple las palabras que no han sido encontradas en el vector de palabras del diccionario.
 * @pre Debe de corresponder a una lista ordenada, por lo que se insertará de forma ordenada.
 * @param p Palabra a añadir.
 */
void Documento::addInexistente(Palabra p) {
    /*La lista debe de mantenerse ordenada.*/
    inexistentes.insertaOrdenado(p);
}

/*---- GETTERS Y SETTERS ----*/
ListaEnlazada<Palabra>& Documento::getInexistentes(){
    return inexistentes;
}

void Documento::setNombreFich(std::string nombreFich) {
    this->nombreFich = nombreFich;
}

std::string Documento::getNombreFich(){
    return nombreFich;
}

/**
 * @brief Destructor.
 */
Documento::~Documento() {
}

