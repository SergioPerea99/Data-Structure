/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Documento.h
 * Author: spdlc
 *
 * Created on 20 de octubre de 2020, 18:40
 */

#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include "ListaEnlazada.h"
#include "Palabra.h"


class Documento {
private:
    std::string nombreFich;
    ListaEnlazada<Palabra> inexistentes;
public:
    Documento();
    Documento(const Documento& orig);
    virtual ~Documento();
    
    /*---- MÉTODOS DEL UML PRACTICA 2 ----*/
    void addInexistente(Palabra p);
    
    
    /*---- GETTERS Y SETTERS ----*/
    ListaEnlazada<Palabra> getInexistentes();
    void setNombreFich(std::string nombreFich);
    std::string getNombreFich();


};

#endif /* DOCUMENTO_H */

