/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VerbosConjugados.h
 * Author: spdlc
 *
 * Created on 8 de noviembre de 2020, 10:48
 */

#ifndef VERBOSCONJUGADOS_H
#define VERBOSCONJUGADOS_H

#include <fstream>

#include "Arbol_AVL.h"
#include "Palabra.h"



class VerbosConjugados {
private:
    std::string nombreFich;
    Arbol_AVL<Palabra> vconjugados;
public:
    VerbosConjugados();
    VerbosConjugados(std::string _nombreFich);
    VerbosConjugados(const VerbosConjugados& orig);
    virtual ~VerbosConjugados();
    
    bool buscar (Palabra& pal);

};

#endif /* VERBOSCONJUGADOS_H */

