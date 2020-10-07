/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParPalabras.cpp
 * Author: spdlc
 * 
 * Created on 6 de octubre de 2020, 19:52
 */

#include "ParPalabras.h"

ParPalabras::ParPalabras() {
    pal1 = "null1";
    pal2 = "null2";
}

ParPalabras::ParPalabras(string _pal1, string _pal2){
    pal1 = _pal1;
    pal2 = _pal2;
}

ParPalabras::ParPalabras(const ParPalabras& orig) {
    pal1 = orig.pal1;
    pal2 = orig.pal2;
}

ParPalabras::~ParPalabras() {
}

void ParPalabras::SetPal2(string pal2) {
    this->pal2 = pal2;
}

string ParPalabras::GetPal2() const {
    return pal2;
}

void ParPalabras::SetPal1(string pal1) {
    this->pal1 = pal1;
}

string ParPalabras::GetPal1() const {
    return pal1;
}

bool ParPalabras::operator ==(const ParPalabras& dato){
    if(dato.pal1 == pal1 && dato.pal2 == pal2)
        return true;
    return false;
}