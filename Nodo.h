/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.h
 * Author: spdlc
 *
 * Created on 15 de octubre de 2020, 10:27
 */

#ifndef NODO_H
#define NODO_H

template <class T>
class Nodo {
    public:
        T dato;
        Nodo *sig;
    
        Nodo(T& aDato, Nodo<T> *aSig);
        Nodo(const Nodo<T>& orig);
        virtual ~Nodo();
     
};
template <class T>
Nodo<T>::Nodo(T& aDato, Nodo<T> *aSig) {
    dato = aDato;
    sig = aSig;
}


template <class T>
Nodo<T>::Nodo(const Nodo<T>& orig) {
    dato = orig.dato;
    sig = orig.sig;
}
template <class T>
Nodo<T>::~Nodo() {
}

#endif /* NODO_H */

