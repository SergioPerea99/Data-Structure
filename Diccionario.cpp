/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Diccionario.cpp
 * Author: spdlc
 * 
 * Created on 20 de octubre de 2020, 18:06
 */

#include "Diccionario.h"

Diccionario::Diccionario() {
    nombreFich = "null";
}

Diccionario::Diccionario(std::string _nombreFich) {
    nombreFich = _nombreFich;
}

Diccionario::Diccionario(const Diccionario& orig) {
    nombreFich = orig.nombreFich;
    terminos = orig.terminos;
}

Diccionario::~Diccionario() {
}

VDinamico<Palabra>* Diccionario::GetTerminos(){
    return &terminos;
}

void Diccionario::SetNombreFich(std::string nombreFich) {
    this->nombreFich = nombreFich;
}

std::string Diccionario::GetNombreFich() const {
    return nombreFich;
}

bool Diccionario::buscarDicotomica(Palabra buscar){
    //Suponemos que el vector de palabras debe de estar ordenado para su llamada.
    int pos = terminos.busquedaBin(buscar);
    if(pos != -1)
        return true;
    return false;
}