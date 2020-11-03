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
    int bal; // -1,0,1 como valores válidos para el AVL.
    
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

/**
 * @brief Constructor por defecto.
 */
template <class T>
Arbol_AVL<T>::Arbol_AVL(){
    raiz = 0;
}

/**
 * @brief Constructor copia.
 * @param orig
 */
template <class T>
Arbol_AVL<T>::Arbol_AVL(const Arbol_AVL& orig){
    if(orig.raiz){
        raiz = new Nodo<T>(orig.raiz);
        
        
    }
}

template <class T>
Arbol_AVL<T>::~Arbol_AVL(){

}

//Copiado de diapositiva. COMPROBADO.
template <class T>
void Arbol_AVL<T>::rotIzqda(Nodo<T>*& p){
    Nodo<T> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if(r->bal < 0)
        q->bal += -r->bal;
    r->bal++;
    if(q->bal > 0)
        r->bal += q->bal;
    
}

//Copiado de diapositiva. COMPROBADO.
template <class T>
void Arbol_AVL<T>::rotDecha(Nodo<T>*& p){
    Nodo<T> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if(l->bal > 0)
        q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0)
        l->bal -= -q->bal;
}

template <class T>
bool Arbol_AVL<T>::inserta(T& dato){
    return inserta(raiz,dato);
}

/**
 * @brief Insertar dato.
 * @post Método privado que inserta un elemento en su correspondiente lugar del arbol.
 * @param c
 * @param dato
 * @return 
 */
template <class T>
int Arbol_AVL<T>::inserta(Nodo<T>*& c, T& dato){
    Nodo<T> *p = c;
    int deltaH = 0;
    if(!p){ /*La recursión llega a una hoja, entonces inserta.*/
        p = new Nodo<T>(dato);
        c = p; deltaH = 1; /*DUDA: La variable deltaH sirve para controlar si se ha insertado o no el elemento.*/
    }
    else if (dato > p->dato){ /*Recursión hacia el hijo de la derecha.*/
        if (inserta(p->der,dato)){
            p->bal--;
            if (p->bal == -1)
                deltaH = 1;
            else if (p->bal == -2){ 
                if (p->der->bal == 1) /*Con esto controla si es rotación doble. Caso 3.*/
                    rotDecha(p->der); /*1º Debe rotar a derechas.*/
                rotIzqda(c); /*Debe de rotar a izquierdas (ya sea rotación doble o no).*/
            }
            else if (dato < p->dato){ /*Recursión hacia el hijo de la izquierda.*/
                if(inserta(p->izq,dato)){
                    p->bal++;
                    if (p->bal == 1)
                        deltaH = 1;
                    else if (p->bal == 2){ /*Con esto controla si es rotación doble. Caso 2.*/
                        if (p->izq->bal == -1)
                            rotIzqda(p->izq);
                        rotDecha(c); /*Debe de rotar a derechas (ya sea rotación doble o no).*/
                    }
                }
            }
            return deltaH;
        }
    }
}

#endif /* ARBOL_AVL_H */

