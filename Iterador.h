/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Iterador.h
 * Author: spdlc
 *
 * Created on 15 de octubre de 2020, 11:17
 */

#ifndef ITERADOR_H
#define ITERADOR_H

#include "Nodo.h"


template <class T>
class Iterador {
    private:
        Nodo<T> *nodo;
        friend class ListaEnlazada; //Permite que ListaEnlazada pueda acceder a todo lo privado de la clase Iterador. NO AL REVÉS.
    public:
        Iterador(Nodo<T> *aNodo);
        Iterador(const Iterador& orig);
        virtual ~Iterador();
        
        bool fin();
        void siguiente();
        T& dato();


};

template <class T>
Iterador<T>::Iterador(Nodo<T> *aNodo) {
    nodo = aNodo;
}

template <class T>
Iterador<T>::Iterador(const Iterador& orig) {
    nodo = orig.nodo;
}

template <class T>
Iterador<T>::~Iterador() {
}

template <class T>
bool Iterador<T>::fin(){
    return nodo == nullptr;
}

template <class T>
void Iterador<T>::siguiente(){
    nodo = nodo->sig;
}

template <class T>
T& Iterador<T>::dato(){
    return nodo->dato;
}

#endif /* ITERADOR_H */

