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
#include <list>
#include <map>
#include "Palabra.h"
#include "Usuario.h"

class Palabra;
class Usuario;

class DiccionarioConVerbos {
private:
    std::string nombreDicc;
    std::string nombreDiccVerbos;
    std::map<std::string, Palabra*> terminos;

public:
    DiccionarioConVerbos();
    DiccionarioConVerbos(std::string _nombreDicc, std::string _nombreDiccVerbos);
    DiccionarioConVerbos(const DiccionarioConVerbos& orig);
    virtual ~DiccionarioConVerbos();
    DiccionarioConVerbos& operator=(const DiccionarioConVerbos& orig);
   
    
    /*---- MÉTODO UML PRÁCTICA 5 ----*/
    Palabra* buscarTermino(std::string& termino, Usuario& u);
    Palabra* insertarInexistente(std::string& termino, Usuario& u);
    int tamTerminos();
    void mostrarDiccionario();
    
    Palabra* buscarPalabra(std::string& termino);

    /*GETTERS Y SETTERS.*/
    void SetNombreFich(std::string nombreFich);
    std::string GetNombreFich() const;
    void setNombreDiccVerbos(std::string nombreDiccVerbos);
    std::string getNombreDiccVerbos() const;

};

#endif /* DICCIONARIO_H */

