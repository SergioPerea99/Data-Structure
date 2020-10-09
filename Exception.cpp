/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.cpp
 * Author: spdlc
 * 
 * Created on 9 de octubre de 2020, 17:53
 */

#include "Exception.h"

/**
 * @brief Constructor parametrizado.
 * @param _excepcion String a asignar al atributo.
 */
Exception::Exception(string _excepcion) {
    excepcion = _excepcion;
}

/**
 * @brief Constructor de copia.
 * @param orig Exception a copiar.
 */
Exception::Exception(const Exception& orig) {
    excepcion = orig.excepcion;
}

/**
 * @brief Destructor.
 */
Exception::~Exception() {
}

/**
 * @brief Setter del atributo excepcion.
 * @param excepcion String a asignar al valor del atributo.
 */
void Exception::SetExcepcion(string excepcion) {
    this->excepcion = excepcion;
}

/**
 * @brief Getter del atributo excepcion.
 * @return String que indica el valor del atributo.
 */
string Exception::GetExcepcion() const {
    return excepcion;
}

