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
#include <fstream>

#include "VDinamico.h"
#include "Palabra.h"
#include "VerbosConjugados.h"


class Diccionario {
private:
    std::string nombreFich;
    VDinamico<Palabra> terminos;
    
    /*---- ATRIBUTOS PRÁCTICA 3 ----*/
    VerbosConjugados verbos;
    
public:
    Diccionario();
    Diccionario(std::string _nombreFich);
    Diccionario(const Diccionario& orig);
    virtual ~Diccionario();
    
    /*---- MÉTODOS DEL UML PRACTICA 2 ----*/
    bool buscarDicotomica(const Palabra& buscar);
    
    /*---- MÉTODOS NECESARIO PRACTICA 3 ----*/
    Diccionario& operator=(const Diccionario& orig);
    bool buscar(Palabra& buscar);
    
    /*GETTERS Y SETTERS.*/
    VDinamico<Palabra> GetTerminos() const;
    void SetNombreFich(std::string nombreFich);
    std::string GetNombreFich() const;
    
    


};

#endif /* DICCIONARIO_H */

