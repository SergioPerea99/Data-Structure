/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParPalabras.h
 * Author: spdlc
 *
 * Created on 6 de octubre de 2020, 19:52
 */

#ifndef PARPALABRAS_H
#define PARPALABRAS_H

#include <iostream>

using namespace std;

class ParPalabras {
private:
    string pal1;
    string pal2;

public:
    ParPalabras();
    ParPalabras(string _pal1, string _pal2);
    ParPalabras(const ParPalabras& orig);
    virtual ~ParPalabras();
    
    
    void SetPal2(string pal2);
    string GetPal2() const;
    void SetPal1(string pal1);
    string GetPal1() const;

    bool operator==(const ParPalabras& dato);
    


};

#endif /* PARPALABRAS_H */

