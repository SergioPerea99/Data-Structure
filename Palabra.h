/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Palabra.h
 * Author: spdlc
 *
 * Created on 5 de octubre de 2020, 19:20
 */

#ifndef PALABRA_H
#define PALABRA_H

#include <iostream>
#include <string>
#include <algorithm>
#include "VDinamico.h"
using namespace std;

class Palabra {
private:
     string palabra;    
     
public:
    Palabra();
    Palabra(string _palabra);
    Palabra(const Palabra& orig);
    virtual ~Palabra();
    
    string GetPalabra() const;
    void SetPalabra(string palabra);

    Palabra& operator=(const Palabra& dato);
    bool operator==(const Palabra& dato);
    bool operator<(const Palabra& dato);
    bool operator>(const Palabra& dato);
    bool operator <=(const Palabra& dato);
    bool operator >=(const Palabra& dato);
    
    /*---- MÉTODOS PRÁCTICA 1 ----*/
    bool palindromo(Palabra& pal);
    bool anagrama(Palabra& pal);
    Palabra reves();
    
    /*---- MÉTODOS PRÁCTICA 2 ----*/
    void limpiar();
    Palabra conversionMinus();

};

#endif /* PALABRA_H */

