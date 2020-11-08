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

#include <iostream>

template <class T>
class NodoAVL{
public:
    NodoAVL<T> *izq, *der;
    T dato;
    int bal; // -1,0,1 como valores válidos para el AVL.
    
    NodoAVL(T& ele){
        izq = der = nullptr;
        bal = 0;
        dato = ele;
    }
};

template <class T>
class Arbol_AVL {
private:
    NodoAVL<T> *raiz;
    unsigned int contador; //Atributo para contar el número de elementos del arbol.
    
    int inserta(NodoAVL<T>* &c, T& dato);
    
    void rotDecha(NodoAVL<T>* &p);
    void rotIzqda(NodoAVL<T>* &p);
    
    unsigned int calcularAltura(NodoAVL<T>* p);
    
    void copiaRecursivamente(NodoAVL<T> *actual, NodoAVL<T> *copiar);
    void destruyeRecursivamente(NodoAVL<T> *borrar);
    NodoAVL<T>* buscaRecursivamente(NodoAVL<T> *buscar, T& dato);
    void inordenRecursivo(NodoAVL<T> *p);
public:
    Arbol_AVL();
    Arbol_AVL(const Arbol_AVL& orig);
    virtual ~Arbol_AVL();
    Arbol_AVL<T>& operator=(const Arbol_AVL& orig);
    
    /*Operaciones y búsquedas.*/
    bool inserta(T& dato);
    bool buscaNR(T& dato, T& result);
    bool buscarIt(T& dato, T& result);
    
    /*Información sobre el árbol*/
    void recorreInorden();
    unsigned int altura();
    unsigned int numElementos();
    
};

/**
 * @brief Constructor por defecto.
 */
template <class T>
Arbol_AVL<T>::Arbol_AVL(){
    raiz = 0;
    contador = 0;
}

/**
 * @brief Constructor copia.
 * @post Constructor público el cual llama a un método privado encargado de realizar
 * la recursividad en preorden para copiar el árbol origen. En caso de estar vacío,
 * poner los valores de por defecto.
 * @param orig Arbol a copiar.
 */
template <class T>
Arbol_AVL<T>::Arbol_AVL(const Arbol_AVL& orig){
    if(orig.raiz)
        copiaRecursivamente(raiz,orig.raiz); /*Llamada a método privado recursivo.*/
    else{
        raiz = 0;
        contador = 0;
    }
    
}

/**
 * @brief Operador de asignación.
 * @post Operador que asigna un árbol a otro de forma que si el destinatario tiene
 * nodos en su árbol primero debe destruirlos y luego copiar todos los del arbol a copiar.
 * @param orig Árbol a ser asignado al destinatario.
 * @return Árbol destinatario con su nueva asignación. Sirve para el uso en cascada del operador.
 */
template <class T>
Arbol_AVL<T>& Arbol_AVL<T>::operator =(const Arbol_AVL& orig){
    if (this != &orig){
        if(raiz) 
            destruyeRecursivamente(raiz); /*Compruebo que si tiene nodos, primero los elimine recursivamente.*/
        copiaRecursivamente(raiz,orig.raiz); /*Copio elemento a elemento usando el método recursivo.*/
    }
    return *this;
    
}



/**
 * @brief Destructor del árbol.
 * @post Destructor que llama a método privado recursivo encargado de eliminar nodo
 * a nodo del árbol a destruir.
 */
template <class T>
Arbol_AVL<T>::~Arbol_AVL(){
    if(raiz)
        destruyeRecursivamente(raiz);
    raiz = 0; /*Posible caso en el que se haya eliminado elementos hasta eliminar el raíz y no haberlo apuntado a nullptr.*/
}



template <class T>
bool Arbol_AVL<T>::inserta(T& dato){
    T resultado;
    if(buscaNR(dato,resultado))/*Primero compruebo si ya se encuentra insertado.*/
        return false;
    else{
        inserta(raiz,dato);
        ++contador;
        return true;
    }
}

/**
 * @brief Insertar dato.
 * @post Método privado que inserta un elemento en su correspondiente lugar del arbol.
 * @param c
 * @param dato
 * @return 
 */
template <class T>
int Arbol_AVL<T>::inserta(NodoAVL<T>*& c, T& dato){
    NodoAVL<T> *p = c;
    int deltaH = 0;
    if(!p){ /*La recursión llega a una hoja, entonces inserta.*/
        p = new NodoAVL<T>(dato);
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
        }
    }else if (dato < p->dato){ /*Recursión hacia el hijo de la izquierda.*/
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
    


/**
 * @brief Búsqueda pública de un elemento recursivo.
 * @post Método público encargado de llamar al método privado que realiza la recursividad
 * necesaria para encontrar o no dicho elemento pasado como parametro.
 * @param dato Elemento a ser buscado.
 * @param result DUDA: Para mi no me sirve devolve el result, o eso creo.
 * @return Booleano que indica si lo ha encontrado o no.
 */
template <class T>
bool Arbol_AVL<T>::buscaNR(T& dato, T& result){
    NodoAVL<T>* encontrado = buscaRecursivamente(raiz,dato);
    if(encontrado)
        return true;
    else
        return false;
}


/**
 * @brief Búsqueda iterativa de un elemento.
 * @post Método que busca un elemento en el árbol de forma iterativa sin el uso 
 * de la recursión y lo que sus problemas conlleva.
 * @param dato Elemento a buscar.
 * @param result
 * @return Booleano que indica si se ha encontrado o no.
 */
template <class T>
bool Arbol_AVL<T>::buscarIt(T& dato, T& result){
    if(raiz){
        NodoAVL<T> *buscar = raiz;
        while(buscar){
            if(buscar->dato == dato)
                return true;
            if(dato < buscar->dato)
                buscar = buscar->izq;
            else
                buscar = buscar->der;
        }
        return false;
    }
    return false; /*En caso de estar vacío el árbol, devuelve falso.*/
}



template <class T>
void Arbol_AVL<T>::recorreInorden(){
    inordenRecursivo(raiz);
}

/**
 * @brief Altura del árbol.
 * @post Método público para mostrar la altura de un arbol.
 * @return Entero que indica la altura. En caso de no tener raíz, devuelve 0.
 */
template <class T>
unsigned int Arbol_AVL<T>::altura(){
    if(raiz)
        return calcularAltura(raiz) - 1;
    else
        return 0;
}


/**
 * @brief Número de elementos del árbol.
 * @return Entero que indica el número de elementos.
 */
template <class T>
unsigned int Arbol_AVL<T>::numElementos(){
    return contador;
}








/*---- MÉTODOS PRIVADOS ----*/


/**
 * @brief Constructor copia RECURSIVO.
 * @post Construcción de un árbol a partir de la copia del pasado como parámetro 
 * y de forma recursiva.
 * @param actual Nodo en el cual se debe de realizar la copia.
 * @param copiar Nodo a ser copiado por otro.
 */
template <class T>
void Arbol_AVL<T>::copiaRecursivamente(NodoAVL<T>* actual, NodoAVL<T>* copiar){
    if(copiar){ /*COPIAR EN PREORDEN.*/
        actual = new NodoAVL<T>(copiar->dato); 
        //actual->dato = copiar->dato; /*Copio el nodo padre.*/
        contador++;
        if (copiar->izq) /*Compruebo que el nodo copiar tiene hijo izquierdo*/
            copiaRecursivamente(actual->izq,copiar->izq);
        if (copiar->der) /*Compruebo que el nodo copiar tiene hijo derecho*/
            copiaRecursivamente(actual->der, copiar->der);
    }
}

/**
 * @brief Destructor RECURSIVO.
 * @post Método privado que elimina en postorden los elementos de un árbol de forma
 * recursiva.
 * @param borrar Nodo a ser borrado, en caso de que sea un nodo hoja.
 */
template <class T>
void Arbol_AVL<T>::destruyeRecursivamente(NodoAVL<T>* borrar){
    /*DESTRUIR EN POSTORDEN.*/
    if (borrar){
        if(borrar->izq) /*Compruebo si tiene hijo izquierdo.*/
            destruyeRecursivamente(borrar->izq);
        
        if(borrar->der) /*Compruebo si tiene hijo derecho.*/
            destruyeRecursivamente(borrar->der);
        
        delete borrar; /*Elimino el nodo, lo pongo a nullptr y resto un elemento al contador.*/
        borrar = 0;
        --contador;
    }
}


//Copiado de diapositiva. COMPROBADO.
template <class T>
void Arbol_AVL<T>::rotIzqda(NodoAVL<T>*& p){
    NodoAVL<T> *q = p, *r;
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
void Arbol_AVL<T>::rotDecha(NodoAVL<T>*& p){
    NodoAVL<T> *q = p, *l;
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

/**
 * @brief Busqueda Recursiva Privada.
 * @post Método privado encargado de buscar un dato tipo T en el árbol con una eficiencia
 * de O(log n). En caso de llegar a un nodo hoja y no ser el dato, se devolverá un booleano falso.
 * @param buscar Nodo desde donde se debe de buscar actualmente.
 * @param dato Elemento tipo T a encontrar.
 * @return Booleano que indica si se ha encontrado.
 */
template <class T>
NodoAVL<T>* Arbol_AVL<T>::buscaRecursivamente(NodoAVL<T>* buscar, T& dato){
    if(buscar){
        if (dato < buscar->dato)
            return buscaRecursivamente(buscar->izq,dato); /*Si el elemento es menor estricto, se busca por subarbol cuya raiz es el hijo izquierdo.*/
        else if (dato > buscar->dato)
            return buscaRecursivamente(buscar->der,dato); /*Si el elemento es mayor estricto, se busca por subarbol cuya raiz es el hijo derecho. */
        else
            return buscar; /*En caso de haberlo encontrado, fin de la recursividad.*/
    }
    return nullptr;

}


template <class T>
void Arbol_AVL<T>::inordenRecursivo(NodoAVL<T>* p){
    if(p){
        if(p->izq) /*Primero compruebo si aún hay hijo izquierda*/
            inordenRecursivo(p->izq);
        
        /*Importante: necesario que el tipo T tenga implementado el operador <<.*/
        std::cout<<p->dato<<" || "; /*Se procesa tanto ese hijo izquierda como aquel padre en caso de no haber ya hijo izquierda.*/
        
        if(p->der)
            inordenRecursivo(p->der); /*Compruebo si hay hijo derecho y vuelve a comprobar el proceso anterior.*/
    }
}


/**
 * @brief Calcular altura.
 * @post Calcula a nivel recursivo la altura de la estructura del árbol AVL.
 * @param p Nodo desde el que empieza a calcular la altura.
 * @return Entero que equivale al valor de la altura actual.
 */
template <class T>
unsigned int Arbol_AVL<T>::calcularAltura(NodoAVL<T>* p){
    if(!p)
        return 0;
    int altura_izquierda = calcularAltura(p->izq);
    int altura_derecha = calcularAltura(p->der);
    
    if( altura_izquierda > altura_derecha)
        return (altura_izquierda + 1);
    else
        return (altura_derecha +  1);
    
}
    
/**/
#endif /* ARBOL_AVL_H */

