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

#include "Palabra.h"

Palabra::Palabra() {
    palabra = "";
}

Palabra::Palabra(string _palabra){
    palabra = _palabra;
}

Palabra::Palabra(const Palabra& orig) {
    palabra = orig.palabra;
}

Palabra::~Palabra() {
}

string Palabra::GetPalabra() const {
    return palabra;
}

void Palabra::SetPalabra(string palabra) {
    this->palabra = palabra;
}

bool Palabra::operator ==(const Palabra& dato){
    if (palabra == dato.GetPalabra())
        return true;
    return false;
}

bool Palabra::operator <(const Palabra& dato){
    if (palabra < dato.GetPalabra())
        return true;
    return false;
}

bool Palabra::operator >(const Palabra& dato){
    if (palabra > dato.GetPalabra())
        return true;
    return false;
}

Palabra& Palabra::operator =(const Palabra& dato){
    palabra = dato.palabra;
    return *this;
}

bool Palabra::operator <=(const Palabra& dato){
    if (palabra <= dato.GetPalabra())
        return true;
    return false;
}

bool Palabra::operator >=(const Palabra& dato){
    if(palabra >= dato.GetPalabra())
        return true;
    return false;
}



bool Palabra::palindromo(Palabra& pal){
    Palabra aux(pal.reves());
    if(aux.GetPalabra() == palabra)
        return true;
    return false;
}


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