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

Documento::Documento() {
    nombreFich = "null";
}

Documento::Documento(const Documento& orig) {
    nombreFich = orig.nombreFich;
    inexistentes = orig.inexistentes;
}

ListaEnlazada<Palabra> Documento::getInexistentes(){
    return inexistentes;
}

void Documento::setNombreFich(std::string nombreFich) {
    this->nombreFich = nombreFich;
}

std::string Documento::getNombreFich(){
    return nombreFich;
}

void Documento::addInexistente(Palabra p) {
    /*La lista debe de mantenerse ordenada.*/
    inexistentes.insertaOrdenado(p);
}


Documento::~Documento() {
}

