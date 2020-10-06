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
    
    
    //Operadores necesarios para usar la búsqueda binaria con este tipo Palabra.
    
    Palabra& operator=(const Palabra& dato);

    
    bool operator==(const Palabra& dato);
    bool operator<(const Palabra& dato);
    bool operator>(const Palabra& dato);
    

};

#endif /* PALABRA_H */

