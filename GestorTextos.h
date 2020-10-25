/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GestorTextos.h
 * Author: spdlc
 *
 * Created on 20 de octubre de 2020, 18:02
 */

#ifndef GESTORTEXTOS_H
#define GESTORTEXTOS_H

#include "Diccionario.h"
#include "Documento.h"
#include <fstream>

class GestorTextos {
private:
    Diccionario diccionario;
    Documento texto;
public:
    GestorTextos();
    GestorTextos(const GestorTextos& orig);
    virtual ~GestorTextos();
    
    /*---- MÉTODOS DEL UML PRACTICA 2 ----*/
    void chequearTexto(std::string _documento, std::string _texto);
    
    /*---- GETTERS Y SETTERS ----*/
    void setTexto(Documento texto);
    Documento& getTexto();
    void setDiccionario(Diccionario diccionario);
    Diccionario& getDiccionario();
};

#endif /* GESTORTEXTOS_H */

