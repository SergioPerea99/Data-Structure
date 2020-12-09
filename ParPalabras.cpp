/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParPalabras.cpp
 * Author: spdlc
 * 
 * Created on 6 de octubre de 2020, 19:52
 */

#include "ParPalabras.h"

/**
 * @brief Construtor por defecto.
 */
ParPalabras::ParPalabras(): pal1 ("null1"), pal2 ("null2"){

}

/**
 * @brief Constructor parametrizado.
 * @param _pal1 String a asignar en un atributo.
 * @param _pal2 String a asignar en un atributo.
 */
ParPalabras::ParPalabras(string _pal1, string _pal2): pal1 (_pal1), pal2 (_pal2){

}

/**
 * @brief Constructor de copia.
 * @param orig ParPalabra que se quiere copiar.
 */
ParPalabras::ParPalabras(const ParPalabras& orig): pal1 (orig.pal1), pal2 (orig.pal2) {

}

/**
 * @brief Destructor.
 */
ParPalabras::~ParPalabras() {
}

/**
 * @brief Setter de atributo pal2.
 * @param pal2 String a asignar al atributo.
 */
void ParPalabras::SetPal2(string pal2) {
    this->pal2 = pal2;
}

/**
 * @brief Getter del atributo pal2.
 * @return String que indica el valor del atributo.
 */
string ParPalabras::GetPal2() const {
    return pal2;
}

/**
 * @brief Setter de atributo pal1.
 * @param pal2 String a asignar al atributo.
 */
void ParPalabras::SetPal1(string pal1) {
    this->pal1 = pal1;
}

/**
 * @brief Getter del atributo pal1.
 * @return String que indica el valor del atributo.
 */
string ParPalabras::GetPal1() const {
    return pal1;
}

/**
 * @brief Operador de comparación ==.
 * @param dato ParPalabras a comparar.
 * @return Booleano.
 */
bool ParPalabras::operator ==(const ParPalabras& dato){
    if(dato.pal1 == pal1 && dato.pal2 == pal2)
        return true;
    return false;
}