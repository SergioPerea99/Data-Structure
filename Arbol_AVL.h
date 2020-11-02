/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arbol_AVL.h
 * Author: spdlc
 *
 * Created on 2 de noviembre de 2020, 15:09
 */

#ifndef ARBOL_AVL_H
#define ARBOL_AVL_H

template <class T>
class Nodo{
public:
    Nodo<T> *izq, *der;
    T dato;
    char bal; // -1,0,1 como valores válidos para el AVL.
    
    Nodo(T& ele){
        izq = der = nullptr;
        bal = 0;
        dato = ele;
    }
};

template <class T>
class Arbol_AVL {
private:
    Nodo<T> *raiz;
    int inserta(Nodo<T>* &c, T& dato);
    void rotDecha(Nodo<T>* &p);
    void rotIzqda(Nodo<T>* &p);
public:
    Arbol_AVL();
    Arbol_AVL(const Arbol_AVL& orig);
    virtual ~Arbol_AVL();
    
    bool inserta(T& dato);

};

template <class T>
Arbol_AVL<T>::Arbol_AVL(){
    raiz = 0;
}

template <class T>
Arbol_AVL<T>::Arbol_AVL(const Arbol_AVL& orig){
    
}

template <class T>
Arbol_AVL<T>::~Arbol_AVL(){

}

template <class T>
bool Arbol_AVL<T>::inserta(T& dato){
    return inserta(raiz,dato);
}

template <class T>
void Arbol_AVL<T>::rotIzqda(Nodo<T>*& p){
    Nodo<T> *q = p, *r;
    p = r = q->der;
    
}

template <class T>
void Arbol_AVL<T>::rotDecha(Nodo<T>*& p){

}
#endif /* ARBOL_AVL_H */

