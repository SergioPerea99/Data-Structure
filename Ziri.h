/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ziri.h
 * Author: spdlc
 *
 * Created on 20 de diciembre de 2020, 11:01
 */

#ifndef ZIRI_H
#define ZIRI_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include "Usuario.h"
#include "MallaRegular.h"
#include "GestorTextos.h"

class Usuario;
class GestorTextos;

class Ziri {
private:
    GestorTextos* gestor;
    std::map<std::string,Usuario> usuariosNIF;
    std::list<Usuario> conectados;
    MallaRegular<Usuario*> usuarioUTM;
    
    void chequearTexto(std::string frase, Usuario& u);
public:
    Ziri();
    Ziri(const Ziri& orig);
    virtual ~Ziri();
    
    Usuario* nuevoUsuarioConectado(std::string& nif,std::string& pass);
    bool desconectarUsuario(std::string& nif);
    
    void recibeMensajeUsuario(std::string& frase, Usuario& u);
    std::list<Usuario>* analizarTermino(std::string& palabra);
    
    //TODO
    std::list<Usuario>* buscarTerminoRango(std::string& palabra, float rxmin, float rymin, float rxmax, float rymax);
    
    
    /*---- MÉTODOS NECESARIOS PARA EL PROGRAMA DE PRUEBA ----*/
    void login();
    int tamUserConectados();
    Usuario& userConectado(unsigned int pos);
    GestorTextos* getGestor();
};

#endif /* ZIRI_H */

