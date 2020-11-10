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

#include <iostream>

template <class T>
class Nodo {
    public:
        T dato;
        Nodo *sig;
        
        Nodo(const T& aDato, Nodo<T> *aSig) {
            dato = aDato;
            sig = aSig;
        };
        Nodo(const Nodo<T>& orig) {
            dato = orig.dato;
            sig = orig.sig;
        };
        
        virtual ~Nodo(){}

        T GetDato() const {
            return dato;
        };
     
};

template <class T>
class Iterador{
    public:
        Nodo<T> *nodo;
        
        Iterador(Nodo<T> *aNodo){ nodo = aNodo;};
        Iterador(const Iterador& orig){ nodo = orig.nodo;};
        virtual ~Iterador(){};
        
        bool fin(){ return nodo == nullptr;};
        void siguiente(){ nodo = nodo->sig;};
        T& dato(){ return nodo->dato;};


};


template <class T>
class ListaEnlazada {
    private:
        Nodo<T> *cabecera, *cola;
        int tam;
        bool ordenado();
    public:
        int tama();
        ListaEnlazada();
        ListaEnlazada(const ListaEnlazada<T>& orig);
        ListaEnlazada<T>& operator=(const ListaEnlazada<T>& orig);
        
        T& Inicio();
        T& Fin();
        
        Iterador<T> iterador(); //Sin & debido a que se crea dentro del método por lo que debo devolver una copia.
        
        void borraInicio();
        void borraFin();
        void borra(Iterador<T>&i);
        
        void insertaInicio(const T& dato);
        void insertaFin(const T& dato);
        void inserta(Iterador<T> i,const T& dato);
        void insertaOrdenado(const T& dato);

        virtual ~ListaEnlazada();
};

/*------ MÉTODOS PÚBLICOS -------*/
/**
 * @brief Constructor por defecto.
 */
template <class T>
ListaEnlazada<T>::ListaEnlazada() {
    cabecera = cola = nullptr;
    tam = 0;
}

/**
 * @brief Constructor copia.
 * @post Copiar la lista pasada por parametro. En caso de estar vacía, se ponen a nullptr tanto la cabecera como la cola.
 * @param orig ListaEnlazada a copiar.
 */
template <class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T>& orig) {
    //DUDA: Lanzo excepcion o simplemente pongo a nullptr la cabecera y la cola?
    if (orig.cabecera == nullptr && orig.cola == nullptr){
        cabecera = cola = nullptr; //throw Exception("[ListaEnlazada<T>::ListaEnlazada] Intento de copia de una listaEnlazada vacía.");
    }else{
        cabecera = new Nodo<T>(orig.cabecera->dato,nullptr);
        Nodo<T> *nuevo = cabecera;
        Nodo<T> *p = orig.cabecera->sig;
        while(p!= orig.cola){
            //Coloco el puntero al siguiente sin dato.
            nuevo->sig = new Nodo<T>(p->dato,nullptr);
            nuevo = nuevo->sig;
            p = p->sig;
        }
        //Quedaria copiar el ultimo elemento correspondiente a la cola.
        nuevo->sig = new Nodo<T>(cola->dato,nullptr);
        cola = nuevo->sig;
    }
    tam = orig.tam;
}

/**
 * @brief Operador de asignación.
 * @post Asignación de cada uno de los valores de una lista en la lista destino. Previa limpieza
 * de la lista antes de ser asignado cada uno de los elementos de la lista origen.
 * @param orig ListaEnlazada de la que se asignarán los elementos.
 * @return ListaEnlazada. Sirve para poder hacer una asignación en cascada.
 */
template <class T>
ListaEnlazada<T>& ListaEnlazada<T>::operator =(const ListaEnlazada<T>& orig){
    
    //Primero se debe vaciar la lista en caso de tener elementos.
    while(cabecera != nullptr)
        borraInicio();

    //Ahora, se crea una copia de cada uno de los nodos de la lista origen.
    Nodo<T> *p = orig.cabecera;
    while(p != nullptr){
        insertaFin(p->dato);
        p = p->sig;
    }
    
    return *this;
}

/**
 * @brief Dato de inicio.
 * @post Dará el dato tipo T que hay en el inicio de una lista enlazada mediante la cabecera de ella.
 * @throw Excepción en caso de que no exista dato en la cabecera de la lista enlazada.
 * @return Dato de tipo T.
 */
template <class T>
T& ListaEnlazada<T>::Inicio(){
    if (cabecera != nullptr){
        return cabecera->dato;
    }else{
        throw std::invalid_argument("[ListaEnlazada<T>::Inicio] No existen elementos en la lista");
    }
}

/**
 * @brief Fin.
 * @post Dará el dato tipo T que hay en el final de una lista enlazada mediante la cola de ella.
 * @throw Excepción en caso de que no exista dato en la lista enlazada.
 * @return Devuelve el dato tipo T.
 */
template <class T>
T& ListaEnlazada<T>::Fin(){
    if (cola != nullptr){
        return cola->dato;
    }else{
        throw std::invalid_argument("[ListaEnlazada<T>::Fin] No existen elementos en la lista");
    }
}

/**
 * @brief Iterador para la Lista.
 * @post Se genera un iterador que apunte al elemento de la cabecera de la lista.
 * En caso de no haber elementos, devolverá un iterador el cual está apuntando a nullptr,
 * por lo que indicará que la lista se encuentra vacía.
 * @return Iterador.
 */
template <class T>
Iterador<T> ListaEnlazada<T>::iterador(){
    Iterador<T> it(cabecera);
    return it;
}



/**
 * @brief Borrar primer elemento de una lista. 
 */
template <class T>
void ListaEnlazada<T>::borraInicio(){
    if(cabecera){
        Nodo<T> *borrado = cabecera;
        cabecera = cabecera->sig;
        delete borrado;
        
        if (cabecera == nullptr)
            cola = nullptr;
        --tam;
    }
}

/**
 * @brief Borrar el ultimo elemento de la lista.
 * @post Comprobaciones de si es ultimo elemento o no para poder eliminar de una forma u otra.
 */
template <class T>
void ListaEnlazada<T>::borraFin(){
    //COMPRUEBO QUE NO ESTÉ VACÍA.
    if(cola){
        Nodo<T>*aux = cabecera;
        while (aux->sig != cola)
            aux = aux->sig;
        
        delete cola;
        cola = aux;
        
        if(cola == nullptr)
            cabecera = nullptr;
        --tam;
    }
    
}
/**
 * @brief Borrar un elemento.
 * @post Borrar un elemento indicado por un iterador pasado por parámetro.
 * @throw Excepcion en caso de que el nodo apunte a nulo en el iterador pasado como parametro.
 * @param i Iterador.
 */
template <class T>
void ListaEnlazada<T>::borra(Iterador<T>& i){
    Nodo<T>* p = i.nodo; //NO HACER OPERACIONES INTERNAS CON EL ITERADOR.
    if(p){
        if(p == cabecera)
            borraInicio();
        else if(p == cola)
            borraFin();
        else{
            Nodo<T>*aux = cabecera;
            while(aux->sig != p)
                aux = aux->sig;
            
            aux->sig = p->sig;

            delete p;
            --tam;
        }
    }else{
        throw std::invalid_argument("[ListaEnlazada<T>::borra] NO EXISTE NODO QUE BORRAR A PARTIR DEL ITERADOR PASADO COMO PARAMETRO.");
    }
}

/**
 * @brief Insertar en la cabecera.
 * @param dato Dato a insertar de tipo T.
 */
template <class T>
void ListaEnlazada<T>::insertaInicio(const T& dato){
    Nodo<T>*aux = new Nodo<T>(dato,cabecera);
    cabecera = aux;
    
    //CASO ESPECIAL: LA LISTA ESTABA VACIA.
    if(cola == nullptr)
        cola = aux;
    ++tam;
}

/**
 * @brief Añadir un elemento al final de la lista.
 * @param dato Elemento tipo T a añadir.
 */
template <class T>
void ListaEnlazada<T>::insertaFin(const T& dato){
    Nodo<T> *nuevo = new Nodo<T>(dato,nullptr);
    if(cola)
        cola->sig = nuevo;
    cola = nuevo;
    
    //CASO ESPECIAL: LA LISTA ESTABA VACIA.
    if(cabecera == nullptr)
        cabecera = nuevo;
    ++tam;
}

/**
 * @brief Insertar justo anterior al iterador.
 * @post Inserta un elemento en la lista justo anterior al elemento que está apuntando
 * el iterador.
 * @param i Iterador.
 * @param dato Elemento a insertar de tipo T.
 */
template <class T>
void ListaEnlazada<T>::inserta(Iterador<T> i,const T& dato){
    Nodo<T> *p = i.nodo; //NO HACER OPERACIONES INTERNAS CON EL ITERADOR.
    if(p){
        if (p == cabecera){
            insertaInicio(dato);
        }else if (p == cola){
            insertaFin(dato);
        }else{
            
            Nodo<T>* aux = cabecera;
            while (aux->sig != p)
                aux = aux->sig;
            
            Nodo<T> *insertar = new Nodo<T>(dato,p);
            aux->sig = insertar;
        
        }
    }else{
        throw std::invalid_argument("[ListaEnlazada<T>::inserta] EL NODO AL QUE APUNTA EL ITERADOR ES NULO.");
    }
    ++tam;
}

/**
 * @brief Insertar de forma ordenada.
 * @post Se inserta un elemento tipo T en una lista de forma ordenada, en caso de encontrarse ya dicho elemento
 * se saldrá del método y no realizará ninguna operación o llamada a otro método.
 * @pre Antes de insertar el elemento, debe la lista de encontrarse ordenada.
 * @param dato Elemento a insertar de tipo T.
 */
template <class T>
void ListaEnlazada<T>::insertaOrdenado(const T& dato){
    if(ordenado()){
        Nodo<T>*p = cabecera;
        while(p && p->dato < dato)
            p = p->sig;

        /*En caso de ser el mismo dato, no insertarlo.*/
        if(p && p->dato == dato)
            return;

        if(p == cabecera)
            insertaInicio(dato);
        else if(p == nullptr)
            insertaFin(dato);
        else{
            
            Nodo<T>* aux = cabecera;
            while (aux->sig != p)
                aux = aux->sig;
            
            Nodo<T> *insertar = new Nodo<T>(dato,p);
            aux->sig = insertar;
            ++tam;
        }
    }else
        throw std::invalid_argument("[ListaEnlazada<T>::insertaOrdenado] Lista no ordenada.");

}

template <class T>
int ListaEnlazada<T>::tama(){
    return tam;
}

/**
 * @brief Destructor de la ListaEnlazada.
 * @post Este destructor llamará a los correspondientes destructores de los Nodos.
 */
template <class T>
ListaEnlazada<T>::~ListaEnlazada() {
    if(cabecera){
        Nodo<T>* p = cabecera;
        while(p != nullptr){
            p = p->sig;
            delete cabecera;
            cabecera = p;
        }
        cola = nullptr;
    }
}

/*----------- METODOS PRIVADOS ------------*/

template <class T>
bool ListaEnlazada<T>::ordenado(){
    Nodo<T> *p = cabecera;
    while(p){
        if(p->sig)
            if(p->dato > p->sig->dato)
                return false;
        p = p->sig;
    }
    return true; 
}

#endif /* LISTAENLAZADA_H */

