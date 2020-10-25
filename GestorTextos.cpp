/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GestorTextos.cpp
 * Author: spdlc
 * 
 * Created on 20 de octubre de 2020, 18:02
 */

#include <ctype.h>

#include "GestorTextos.h"


GestorTextos::GestorTextos() {
    
}

void GestorTextos::setTexto(Documento texto) {
    this->texto = texto;
}

Documento* GestorTextos::getTexto(){
    return &texto;
}

void GestorTextos::setDiccionario(Diccionario diccionario) {
    this->diccionario = diccionario;
}

Diccionario* GestorTextos::getDiccionario(){
    return &diccionario;
}

GestorTextos::GestorTextos(const GestorTextos& orig) {
    diccionario = orig.diccionario;
    texto = orig.texto;
}

/**
 * @brief Chequear texto 
 */
void GestorTextos::chequearTexto (string _documento, string _diccionario) {
    
    diccionario.SetNombreFich(_diccionario);
    /*Primera parte: Cargar el diccionario en el Gestor de Textos.*/
    ifstream is(_diccionario);
	string palabra;
        Palabra pal;
	while (is) {
		is >> palabra;
                pal.SetPalabra(palabra);
                diccionario.GetTerminos()->insertar(pal);
	}
        /*Ordenación para poder luego buscar en él con una búsqueda binaria.*/
        diccionario.GetTerminos()->ordenar();
	cout << diccionario.GetTerminos()->tam() << " palabras cargadas en los TERMINOS del diccionario." << endl;
	is.close();
        

        /*Segunda parte: Comprobar palabras válidas del quijote.*/
        texto.setNombreFich(_documento);
        is.open(_documento);
	clock_t t_ini = clock();
	int no_validadas = 0, total = 0, p;
	while (is) {
		is >> palabra;
                pal.SetPalabra(palabra);
		++total;
                /*Ahora limpio la palabra para comprobar si existe en el diccionario.*/
                pal.limpiar();
		if (!getDiccionario()->buscarDicotomica(pal)) {
                    ++no_validadas;
                    getTexto()->addInexistente(pal);
		}
	}
	cout <<"Total palabras: " << total << " --------- Total de palabras no_validadas: " << no_validadas << endl;
	cout << "Tiempo para chequear el texto: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
        
}




GestorTextos::~GestorTextos() {
}

