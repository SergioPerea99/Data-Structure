/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VDinamico.h
 * Author: spdlc
 *
 * Created on 30 de septiembre de 2020, 16:53
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <iostream>
#include <climits> //Necesario para el UINT_MAX.


template <class T>
class VDinamico{
    private:
        int tamF, tamL;
        T* vector;
        
        void aumentarVector();
        void disminuye();
        
    public:
        VDinamico();
        VDinamico(unsigned int tam);
        VDinamico(const VDinamico<T>& orig);
        VDinamico(const VDinamico<T>& origen, unsigned int inicio, unsigned int num);
        VDinamico<T>& operator =(const VDinamico<T>& orig);
        T& operator[](unsigned int pos);
        void insertar(const T& dato, unsigned int pos = UINT_MAX);
        T borrar(unsigned int pos = UINT_MAX);
        virtual ~VDinamico();
        
        
        
        int getTamL() const{return tamL;};
        int getTamF() const{return tamF;};
        
        
        

};

/**
 * @brief Constructor por defecto.
 * @post Constructor por defecto VDinamico<T> , iniciando el tamaño físico a 1 y el lógico a 0.
 */
template <class T>
VDinamico<T>::VDinamico(){
    tamF = 1;
    tamL = 0;
    vector = nullptr;
};

/**
 * @brief Constructor por defecto parametrizado.
 * @post Constructor dando un tamaño lógico inicial, VDinamico<T>(unsigned int tam), 
 * iniciando el tamaño físico a la potencia de 2 inmediatamente superior a tam (tamaño lógico).
 * @param tam. Tamaño lógico pasado como parámetro.
 */
template <class T>
VDinamico<T>::VDinamico(unsigned int tam){
    tamL = tam; tamF = 1;
    while (tamF <= tamL)
        tamF *= 2;
    vector = new T[tamF];
};

/**
 * @brief Constructor copia.
 * @post Constructor copia VDinamico<T>(const VDinamico<T>& origen).
 * @param orig. Vector pasado como parámetro para su posterior copia.
 */
template <class T>
VDinamico<T>::VDinamico(const VDinamico<T>& orig){
    tamF = orig.tamF;
    tamL = orig.tamL;
    vector = new T[tamF];
    for (int i = 0; i < orig.tamL; i++)
        vector[i] = orig.vector[i];   
};

/**
 * @brief Constructor de copia parcial.
 * @param origen. Vector origen que se procede a copiar.
 * @param inicio. Inicio desde donde se quiere copiar en el vector.
 * @param num. Cantidad de elementos a copiar.
 */
template<class T> 
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned int inicio, unsigned int num){
    tamL = num; 
    tamF = origen.tamF;
    vector = new T[tamF];
    int i =0;
    while (i < num)
        vector[i++] = origen.vector[inicio+i]; 
};

/**
 * @brief Operador de asignación = .
 * @post Función especial que asegura una copia correcta de los objetos.
 * @param orig. Vector dinámico que se desea copiar.
 * @return El propio contenido del vector dinámico.
 */
template <class T>
VDinamico<T>& VDinamico<T>::operator =(const VDinamico<T>& orig){
    if (this != orig){
        if (vector)
            delete []vector;
        
        tamL = orig.tamL;
        tamF = orig.tamF;
        vector = new T[tamF];
        for (int i = 0; i < orig.tamL; i++)
            vector[i] = orig.vector[i];
    }
    return *this;
};


/**
 * @brief Operador [].
 * @post Operador que sustituye a las dos operaciones de lectura y escritura.
 * @param pos. Posición en el vector donde se quiere realizar una operación de lectura o escritura.
 * @return Elemento del vector.
 */
template <class T>
T& VDinamico<T>::operator [](unsigned int pos){
    if (pos < tamL){
        return vector[pos];
    }else
        throw std::out_of_range("[VDinamico<T>::operator []] La posicion indicada esta fuera del rango.");
};


/**
 * @brief Insertar dato.
 * @post Insertar un dato en una posición de forma que si no se pasa la posición del dato a insertar
 * se insertará al final del vector. En caso de dar una posición mayor elegida, entonces saltará una excepción.
 * @param dato. Tipo T que se insertará en el vector.
 * @param pos. Posición en la que debe de insertarse el dato en el vector.
 * @throw out_of_range. Valor de la posición dada está fuera de rango.
 */
template <class T>
void VDinamico<T>::insertar(const T& dato, unsigned int pos){
        //En caso de dar una posición por parametro que sea superior al tamaño lógico.
    if(pos > tamL && pos != UINT_MAX) 
        throw std::out_of_range("[VDinamico<T>::insertar] Intenta insertar fuera del rango del vector. Elija una posición positiva menor.");
    
    if(vector){
        if (tamL < tamF){
            if(pos == UINT_MAX)
                vector[tamL] = dato;
            else{
                for (int i = tamL; i > pos; i--)
                    vector[i] = vector[i-1];
                vector[pos] = dato;
            }
        }else{
            aumentarVector();
            for (int i = tamL; i > pos; i--)
                vector[i] = vector[i-1];
            vector[pos] = dato;       
        }
    }else{
            //En este caso, aunque me digan una posición, sabemos que es un vector construido por defecto.
            //Por lo tanto, tenemos que generar su espacio en memoria y añadir el elemento en la primera casilla.
        vector = new T[tamF];
        vector[0] = dato;
    }
    ++tamL;
};


template <class T>
T VDinamico<T>::borrar(unsigned int pos){
    if(pos >= tamL && pos != UINT_MAX)
        throw std::out_of_range("[VDinamico<T>::borrar] Intenta eliminar un elemento en una posición fuera del rango de elementos.");
    if(vector){
            //Compruebo si al eliminar el elemento provoca que se tenga que disminuir el tamF reservado para el vector.
        if((tamL-1)*3 < tamF)
            disminuye();
        
            //Ahora compruebo en que posición se quiere eliminar el elemento.
        if(pos == UINT_MAX)
            return vector[--tamL];
        else{
            for(int i=pos; i<tamL; i++)
                vector[i] = vector[i+1];
            --tamL;
        }
    }else
        throw std::invalid_argument("[VDinamico<T>::borrar] No existen elementos en el vector para borrar.");
};



/**
 * @brief Destructor.
 * @post Destructor de la instancia. Conlleva a una previa liberación de memoria en caso de que
 * el atributo vector apunte hacia algo y no hacia nullptr.
 */
template <class T>
VDinamico<T>::~VDinamico(){
    if(vector){
        delete []vector;
        vector = nullptr;
    }
}



//--------------- METODOS PRIVADOS ----------//
/**
 * @brief Aumentar tamaño físico.
 * @post Aumenta a la siguiente potencia de 2 superior al valor del tamaño lógico.
 */
template <class T>
void VDinamico<T>::aumentarVector(){
        //Creo vector auxiliar que apunte al anterior vector.
    T* auxiliar = vector;
        //Incremento el tamF en una potencia de 2 mayor y creo ese espacio en memoria para el vector.
    vector = new T[tamF *= 2];
    
    for(int i = 0;i < tamL;i++)
        vector[i] = auxiliar[i];
        //Ahora libero la memoria del vector anterior (es decir, el auxiliar).
    delete []auxiliar;
    auxiliar = nullptr;
};

/**
 * @bief Disminuir tamaño físico.
 * @post Disminuye en caso de que haya menos de 1/3 de capacidad ocupada en el vector. En ese casp,
 * disminuye su tamaño a la mitad.
 */
template <class T>
void VDinamico<T>::disminuye(){
    tamF = tamF/2;
    T* auxiliar = new T [tamF];
    for (int i = 0; i < tamL; i++)
        auxiliar[i] = vector[i];
    
    delete []vector;
    vector = auxiliar;
};
#endif /* VDINAMICO_H */

