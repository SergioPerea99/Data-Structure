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

#include "DiccionarioConVerbos.h"


class Documento {
private:
    std::string nombreFich;
    DiccionarioConVerbos *dicc;
    
public:
    Documento();
    Documento(std::string _texto, DiccionarioConVerbos*& _dicc);
    Documento(const Documento& orig);
    virtual ~Documento();
    Documento& operator=(const Documento& dato);
    bool operator==(const Documento& dato);

    /*---- MÉTODOS NECESARIOS PRACTICA 3  ----*/
    void chequearTexto();
    
    /*---- GETTERS Y SETTERS ----*/
    void setNombreFich(std::string nombreFich);
    std::string getNombreFich();
    DiccionarioConVerbos* getDicc() const;
    void setDicc(DiccionarioConVerbos* dicc);
    
};

#endif /* DOCUMENTO_H */

