/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Usuario.cpp
 * Author: spdlc
 * 
 * Created on 20 de diciembre de 2020, 10:48
 */

#include "Usuario.h"

Usuario::Usuario():
nif("null"), clave("null"), nombre("null"), frase("null"),latitud(0.0), longitud(0.0), enlaceZiri(nullptr)
{
}


Usuario::Usuario(std::string _nif, std::string _clave, std::string _nombre, std::string _frase, float _latitud, float _longitud, Ziri* enlZiri):
nif(_nif), clave(_clave), nombre(_nombre), frase(_frase),latitud(_latitud), longitud(_longitud)
{
}

Usuario::Usuario(const Usuario& orig):
nif(orig.nif), clave(orig.clave), nombre(orig.nombre), frase(orig.frase),latitud(orig.latitud), longitud(orig.longitud)
{
}

Usuario::~Usuario() {
}


bool Usuario::login(std::string nif, std::string pass) {
    return enlaceZiri->nuevoUsuarioConectado(nif); //DUDA: PARA QUE SIRVE PASAR LA CONTRASEÑA?
}

bool Usuario::logoff(){
    std::string _nif = nif;
    return enlaceZiri->desconectarUsuario(_nif);
}

void Usuario::escribeMensaje(){
    std::string _frase;
    enlaceZiri->recibeMensajeUsuario(_frase,(*this));
}



float Usuario::getLongitud() const {
    return longitud;
}

float Usuario::getLatitud() const {
    return latitud;
}

std::string Usuario::getFrase() const {
    return frase;
}

std::string Usuario::getNombre() const {
    return nombre;
}

std::string Usuario::getClave() const {
    return clave;
}

std::string Usuario::getNif() const {
    return nif;
}