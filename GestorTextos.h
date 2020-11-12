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
#include "Documento.h"
#include <fstream>
#include <vector>

class GestorTextos {
private:
    vector<Documento*> documentos;
    DiccionarioConVerbos *diccionario;
    //vector<DiccionarioConVerbos*> diccionarios;
public:
    GestorTextos();
    GestorTextos(const GestorTextos& orig);
    virtual ~GestorTextos();
    
    /*---- MÉTODOS DEL UML PRACTICA 3 ----*/
    int addDocumento(std::string nombreFich);
    Documento* buscarDocumento(std::string nombreFich);
    
    /*---- MÉTODOS DEL UML PRACTICA 4 ----*/
    //int addDiccionario(std::string nombreDicc, std::string nombreDiccVerbos);
    bool buscarTermino(std::string termino, Palabra* result);
    list<Palabra> buscarFamilias(std::string raiz);
    
    /*---- GETTERS Y SETTERS ----*/
    DiccionarioConVerbos* getDiccionario();
    Documento* getDocumento(unsigned int pos);
};

#endif /* GESTORTEXTOS_H */

