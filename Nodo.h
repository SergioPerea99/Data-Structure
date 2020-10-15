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
    private:
        T dato;
        Nodo *ant, *sig;
    public:
        Nodo(T& aDato, Nodo<T> *aAnt, Nodo<T> *aSig);
        Nodo(const Nodo<T>& orig);
        virtual ~Nodo();
        
        Nodo* GetSig() const;
        Nodo* GetAnt() const;
        T GetDato() const;
        void SetSig(Nodo* sig);
        void SetAnt(Nodo* ant);
        
    
        
};
template <class T>
Nodo<T>::Nodo(T& aDato, Nodo<T> *aAnt, Nodo<T> *aSig) {
    dato = aDato;
    ant = aAnt;
    sig = aSig;
}


template <class T>
Nodo<T>::Nodo(const Nodo<T>& orig) {
    dato = orig.dato;
    ant = orig.ant;
    sig = orig.sig;
}
template <class T>
Nodo<T>::~Nodo() {
}




/*-------- GETTERS --------*/

template <class T>
Nodo* Nodo::GetSig() const {
    return sig;
}

template <class T>
Nodo* Nodo::GetAnt() const {
    return ant;
}

template <class T>
T Nodo::GetDato() const {
    return dato;
}

/*-------- SETTERS --------*/

template <class T>
void Nodo::SetSig(Nodo* sig) {
    this->sig = sig;
}

template <class T>
void Nodo::SetAnt(Nodo* ant) {
    this->ant = ant;
}

#endif /* NODO_H */

