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
#include <list>
#include "Usuario.h"
using namespace std;

class Usuario;

class Palabra {
private:
     string termino;    
     unsigned int ocurrencias;
     list<Usuario> dichaPor;
public:
    Palabra();
    Palabra(string _palabra);
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
    
    /*---- MÉTODOS PRÁCTICA 5 ----*/
    bool buscarUsuario(Usuario& u);
    bool insertarUsuario(Usuario& u);
    list<Usuario>& usadoPorUsers();
    
    /*---- GETTERS Y SETTERS  ----*/
    int GetOcurrencias() const;
    list<Usuario>::iterator listUserInicio();
    string GetPalabra() const;
    void SetPalabra(string palabra);
    
};


std::ostream &operator<<(std::ostream &os, const Palabra &f);

#endif /* PALABRA_H */

