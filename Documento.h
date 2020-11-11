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
#include "DiccionarioConVerbos.h"


class Documento {
private:
    std::string nombreFich;
    ListaEnlazada<Palabra> inexistentes;
    
    /*Atributos PRÁCTICA 3*/
    DiccionarioConVerbos *dicc;
    
public:
    Documento();
    Documento(std::string _texto, DiccionarioConVerbos* _dicc);
    Documento(const Documento& orig);
    virtual ~Documento();
    
    /*---- MÉTODOS DEL UML PRACTICA 2 ----*/
    void addInexistente(Palabra p);
    
    /*---- MÉTODOS NECESARIOS PRACTICA 3  ----*/
    Documento& operator=(const Documento& dato);
    bool operator==(const Documento& dato);
    void chequearTexto(unsigned int num_practica);
    
    /*---- GETTERS Y SETTERS ----*/
    ListaEnlazada<Palabra>& getInexistentes();
    void setNombreFich(std::string nombreFich);
    std::string getNombreFich();
    DiccionarioConVerbos* getDicc() const;
    void setDicc(DiccionarioConVerbos* dicc);
    
    
    
};

#endif /* DOCUMENTO_H */

