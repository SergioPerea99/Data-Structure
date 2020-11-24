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

class DiccionarioConVerbos;
class Documento;

class Palabra {
private:
     string palabra;    
     unsigned int ocurrencias;
     Documento *ultima_aparicion;
     DiccionarioConVerbos *dicc_perteneciente;
public:
    Palabra();
    Palabra(string _palabra, DiccionarioConVerbos *_diccPerteneciente);
    Palabra(const Palabra& orig);
    virtual ~Palabra();
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
    string conversionMinus();
    
    /*---- MÉTODOS PRÁCTICA 4 ----*/
    void incrementarOcurrencia();
    
    /*---- GETTERS Y SETTERS  ----*/
    int GetOcurrencias() const;
    DiccionarioConVerbos* GetDicc_perteneciente() const;
    void SetUltima_aparicion(Documento* ultima_aparicion);
    Documento* GetUltima_aparicion() const;
    string GetPalabra() const;
    void SetPalabra(string palabra);
    
};


std::ostream &operator<<(std::ostream &os, const Palabra &f);

#endif /* PALABRA_H */

