/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Documento.cpp
 * Author: spdlc
 * 
 * Created on 20 de octubre de 2020, 18:40
 */

#include "Documento.h"

/**
 * @brief Constructor por defecto.
 */
Documento::Documento() : inexistentes(){
    nombreFich = "quijote-sin-simbolos.txt";
    dicc = nullptr;
}

Documento::Documento(std::string _texto, Diccionario* _dicc): inexistentes(){
    nombreFich = _texto;
    dicc = _dicc;
}

/**
 * @brief Constructor copia.
 * @param orig Documento a ser copiado.
 */
Documento::Documento(const Documento& orig) {
    nombreFich = orig.nombreFich;
    inexistentes = orig.inexistentes;
    dicc = orig.dicc;
}


/**
 * @brief Añadir palabra inexistente.
 * @post Añade en la estructura de la lista enlazada simple las palabras que no han sido encontradas en el vector de palabras del diccionario.
 * @pre Debe de corresponder a una lista ordenada, por lo que se insertará de forma ordenada.
 * @param p Palabra a añadir.
 */
void Documento::addInexistente(Palabra p) {
    /*La lista debe de mantenerse ordenada.*/
    inexistentes.insertaOrdenado(p);
}


bool Documento::operator ==(const Documento& dato){
    return nombreFich == dato.nombreFich ? true : false;
}

Documento& Documento::operator =(const Documento& dato){
    if(this != &dato){
        nombreFich = dato.nombreFich;
        inexistentes = dato.inexistentes;
    }
    return *this;
}


void Documento::chequearTexto(){
    ifstream is(nombreFich);
    cout<<nombreFich<<endl;
    string palabra;
    Palabra pal;
    clock_t t_ini = clock();
    int no_validadas = 0, total = 0, p;
    while (is) {
        is >> palabra;
        pal.SetPalabra(palabra);
        ++total;
        /*Ahora limpio la palabra para comprobar si existe en el diccionario.*/
        pal.limpiar();

        if (!getDicc()->buscarDicotomica(pal.conversionMinus())) {
            //cout<<"Palabra inexistente -> "<<pal.GetPalabra()<<endl;
            ++no_validadas;
            addInexistente(pal);
        }
    }
    is.close();
    cout << "Total palabras: " << total << " --------- Total de palabras no_validadas: " << no_validadas << endl;
    cout << "Tiempo para chequear el texto: " << ((clock() - t_ini) / CLOCKS_PER_SEC) << " segs." << endl;
}



/*---- GETTERS Y SETTERS ----*/
ListaEnlazada<Palabra>& Documento::getInexistentes(){
    return inexistentes;
}

void Documento::setNombreFich(std::string nombreFich) {
    this->nombreFich = nombreFich;
}

std::string Documento::getNombreFich(){
    return nombreFich;
}

Diccionario* Documento::getDicc() const{
    return dicc;
}

void Documento::setDicc(Diccionario* dicc) {
    this->dicc = dicc;
}

/**
 * @brief Destructor.
 */
Documento::~Documento() {
}

