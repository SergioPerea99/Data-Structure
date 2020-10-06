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

#include "Palabra.h"

Palabra::Palabra() {
    palabra = "null";
}

Palabra::Palabra(string _palabra){
    palabra = _palabra;
}

Palabra::Palabra(const Palabra& orig) {
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
    if(this != &dato){
        palabra = dato.palabra;
    }
    return *this;
}

