/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VerbosConjugados.cpp
 * Author: spdlc
 * 
 * Created on 8 de noviembre de 2020, 10:48
 */

#include "VerbosConjugados.h"

VerbosConjugados::VerbosConjugados(){
    nombreFich = "verbos_conjugados_sin_tildes_desordenados.txt";
    ifstream is(nombreFich);
    string palabra;
    Palabra pal;
    while (is) {
        is >> palabra;
        pal.SetPalabra(palabra);
        vconjugados.inserta(pal);
    }
    
    std::cout << vconjugados.numElementos() << " verbos conjugados y una altura de arbol de " <<vconjugados.altura()<<"."<<endl;
    is.close();
}

VerbosConjugados::VerbosConjugados(std::string _nombreFich){
    nombreFich = _nombreFich;
    ifstream is(nombreFich);
    string palabra;
    Palabra pal;
    while (is) {
        is >> palabra;
        pal.SetPalabra(palabra);
        vconjugados.inserta(pal);
            
    }
    
    std::cout << vconjugados.numElementos() << " verbos conjugados y una altura de arbol de " <<vconjugados.altura()<<"."<<endl;
    is.close();
}

VerbosConjugados::VerbosConjugados(const VerbosConjugados& orig) {
    nombreFich = orig.nombreFich;
    vconjugados = orig.vconjugados;
}


bool VerbosConjugados::buscar(Palabra& pal){
    Palabra encontrada;
    return vconjugados.buscaNR(pal,encontrada);
}


VerbosConjugados::~VerbosConjugados() {
}

Arbol_AVL<Palabra>* VerbosConjugados::getVconjugados(){
    return &vconjugados;
}