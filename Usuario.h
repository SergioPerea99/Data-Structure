/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Usuario.h
 * Author: spdlc
 *
 * Created on 20 de diciembre de 2020, 10:48
 */

#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>

#include "Ziri.h"

class Ziri;

class Usuario {
private:
    std::string nif, clave, nombre, frase;
    float latitud, longitud;
    Ziri* enlaceZiri;
public:
    Usuario();
    Usuario(std::string _nif, std::string _clave, std::string _nombre, std::string _frase, float _latitud, float _longitud, Ziri* enlZiri);
    Usuario(const Usuario& orig);
    Usuario& operator=(const Usuario& u); //TODO: HACER OPERADOR DE ASIGNACION
    bool operator==(const Usuario& u); //TODO: CREAR OPERADOR ==
    virtual ~Usuario();
    
    //TODO: POR HACER ESTOS MÉTODOS.
    bool login(std::string nif, std::string pass);
    bool logoff();
    void escribeMensaje();
    
    /*---- GETTERS Y SETTERS ----*/
    float getLongitud() const;
    float getLatitud() const;
    std::string getFrase() const;
    std::string getNombre() const;
    std::string getClave() const;
    std::string getNif() const;
    
    

};

#endif /* USUARIO_H */

