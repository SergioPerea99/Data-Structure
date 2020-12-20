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

#include "DiccionarioConVerbos.h"
#include "Palabra.h"
#include "Usuario.h"
#include <fstream>
#include <iostream>


class DiccionarioConVerbos;
class Palabra;
class Usuario;

class GestorTextos {
private:
    DiccionarioConVerbos* diccionario;

public:
    GestorTextos();
    GestorTextos(const GestorTextos& orig);
    virtual ~GestorTextos();
    
    /*---- MÉTODOS DEL UML PRACTICA 5 ----*/
    Palabra* insertarInexistente(std::string& termino, Usuario& u);
    Palabra* buscarTermino(std::string& termino, Usuario& u);
    
    /*---- GETTERS Y SETTERS ----*/
    DiccionarioConVerbos*& getDiccionario();
};

#endif /* GESTORTEXTOS_H */

