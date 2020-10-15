/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaEnlazada.h
 * Author: spdlc
 *
 * Created on 15 de octubre de 2020, 10:23
 */

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include "Nodo.h"
#include "Exception.h"


template <class T>
class ListaEnlazada {
    private:
        Nodo<T> *cabecera, *cola;
        
        void vaciarListaEnlazada();
        void insertarFinal(Nodo<T>* p);
        
    public:
        ListaEnlazada();
        ListaEnlazada(const ListaEnlazada<T>& orig);
        virtual ~ListaEnlazada();
        
        ListaEnlazada<T>& operator=(const ListaEnlazada<T>& orig);

};

/*------ MÉTODOS PÚBLICOS -------*/

template <class T>
ListaEnlazada<T>::ListaEnlazada() {
    cabecera = cola = nullptr;
}

template <class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T>& orig) {
    //DUDA: Lanzo excepcion o simplemente pongo a nullptr la cabecera y la cola?
    if (orig.cabecera == nullptr && orig.cola == nullptr){
        cabecera = cola = nullptr; //throw Exception("[ListaEnlazada<T>::ListaEnlazada] Intento de copia de una listaEnlazada vacía.");
    }else{
        cabecera = new Nodo<T>(orig.cabecera->GetDato(),nullptr,nullptr);
        Nodo<T> *nuevo = cabecera;
        Nodo<T> *p = orig.cabecera->GetSig();
        while(p!= orig.cola){
            //Coloco el puntero al siguiente sin dato.
            nuevo->SetSig( new Nodo<T>(p->GetDato(),nuevo,nullptr) );
            nuevo = nuevo->GetSig();
            p = p->GetSig();
        }
        //Quedaria copiar el ultimo elemento correspondiente a la cola.
        nuevo->SetSig( new Nodo<T>(cola->GetDato(),nuevo,nullptr) );
        cola = nuevo->GetSig();
    }
}

template <class T>
ListaEnlazada<T>& ListaEnlazada<T>::operator =(const ListaEnlazada<T>& orig){
    if(this != orig){
        
        //Primero se debe vaciar la lista en caso de tener elementos.
        if(cabecera != nullptr)
            vaciarListaEnlazada();
        
        //Ahora, se crea una copia de cada uno de los nodos de la lista origen.
        Nodo<T> *p = orig.cabecera;
        while(p != nullptr){
            insertarFinal(p);
            p = p->GetSig();
        }
    }
}

template <class T>
ListaEnlazada<T>::~ListaEnlazada() {
}

/*------ MÉTODOS PRIVADOS -------*/

template <T>
void ListaEnlazada<class T>::vaciarListaEnlazada(){
    Nodo<class T> *borrado = cabecera;
    while(cabecera != nullptr){
        cabecera = cabecera->GetSig();
        delete borrado;
    }
    if (cabecera == nullptr)
        cola = nullptr;
}

template <class T>
void ListaEnlazada<class T>::insertarFinal(Nodo<T>* p){
    Nodo<T> *nuevo = new Nodo<T>(p->GetDato(),cola,nullptr);
    if(cola != nullptr)
        cola->SetSig(nuevo);
    cola = nuevo;
    
    //CASO ESPECIAL: LA LISTA ESTABA VACIA.
    if(cabecera == nullptr)
        cabecera = nuevo;
}

#endif /* LISTAENLAZADA_H */

