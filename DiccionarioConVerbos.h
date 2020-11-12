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

#include "VDinamico.h"
#include "Palabra.h"

class DiccionarioConVerbos {
private:
    /*---- ATRIBUTOS PRÁCTICA 4 ----*/
    std::string nombreDicc;
    std::string nombreDiccVerbos;
    map<std::string, Palabra*> terminos;

public:
    DiccionarioConVerbos();
    DiccionarioConVerbos(std::string _nombreDicc, std::string _nombreDiccVerbos);
    DiccionarioConVerbos(const DiccionarioConVerbos& orig);
    virtual ~DiccionarioConVerbos();

    /*---- MÉTODOS NECESARIO PRACTICA 3 ----*/
    DiccionarioConVerbos& operator=(const DiccionarioConVerbos& orig);
   
    
    /*---- MÉTODO UML PRÁCTICA 4 ----*/
    bool buscarTermino(std::string& termino, Palabra *result);
    list<Palabra> buscarFamilias(std::string raiz);
    Palabra* insertarInexistente(Palabra& dato);

    /*GETTERS Y SETTERS.*/
    void SetNombreFich(std::string nombreFich);
    std::string GetNombreFich() const;
   
    void setNombreDiccVerbos(std::string nombreDiccVerbos);
    std::string getNombreDiccVerbos() const;
    
    map<std::string,Palabra*>::iterator it_Begin(); 
    map<std::string,Palabra*>::iterator it_End();
    

};

#endif /* DICCIONARIO_H */

