/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.h
 * Author: spdlc
 *
 * Created on 9 de octubre de 2020, 17:53
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

using namespace std;

class Exception {
private:
    string excepcion;
public:
    Exception(string _excepcion);
    Exception(const Exception& orig);
    virtual ~Exception();
    
    void SetExcepcion(string excepcion);
    string GetExcepcion() const;

};

#endif /* EXCEPTION_H */

