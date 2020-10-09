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

Exception::Exception(string _excepcion) {
    excepcion = _excepcion;
}

Exception::Exception(const Exception& orig) {
    excepcion = orig.excepcion;
}

Exception::~Exception() {
}

void Exception::SetExcepcion(string excepcion) {
    this->excepcion = excepcion;
}

string Exception::GetExcepcion() const {
    return excepcion;
}

