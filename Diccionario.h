/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Diccionario.h
 * Author: spdlc
 *
 * Created on 20 de octubre de 2020, 18:06
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <iostream>

#include "VDinamico.h"
#include "Palabra.h"

class Diccionario {
private:
    std::string nombreFich;
    VDinamico<Palabra> terminos;

public:
    Diccionario();
    Diccionario(std::string _nombreFich);
    Diccionario(const Diccionario& orig);
    virtual ~Diccionario();
    
    /*---- MÉTODOS DEL UML PRACTICA 2 ----*/
    bool buscarDicotomica(Palabra buscar);
    
    
    /*GETTERS Y SETTERS.*/
    VDinamico<Palabra>& GetTerminos();
    void SetNombreFich(std::string nombreFich);
    std::string GetNombreFich() const;
    
    


};

#endif /* DICCIONARIO_H */

