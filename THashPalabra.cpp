/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   THashPalabra.cpp
 * Author: spdlc
 * 
 * Created on 11 de diciembre de 2020, 17:02
 */

#include <stdexcept>
#include <complex>
#include <vector>

#include "THashPalabra.h"

THashPalabra::THashPalabra(int tamTabla, float _factorCarga): tamF(0), tamL(0),primoMenor(0), tabla(), colisiones(0), maxColisiones(0),factorCarga(0.6) {
    if(_factorCarga < 0.6 || _factorCarga > 1) 
        throw std::invalid_argument ("[THashPalabra::THashPalabra] Tienes que introducir bien el factor de carga de la tabla de palabras. Debe ser mayor de 0.6");
    factorCarga = _factorCarga;
    int num = floor(tamTabla/factorCarga); //Necesito redondeo a la baja, para a las malas hacer el factor de carga algo mayor y no algo menor al pasado.
    tamF = sigPrimo(num, primoMenor); //APARENTEMENTE FUNCIONANDO.
    Palabra pal;
    tabla = std::vector<Entrada>(tamF,Entrada(0,pal));
    cout<<"TAM_F = "<<tamF<<" :: primo_anterior = "<<primoMenor<<endl;
}

THashPalabra::THashPalabra(const THashPalabra& orig):
    tamF (orig.tamF), tamL (orig.tamL), primoMenor (orig.primoMenor),
    tabla (orig.tabla), colisiones (orig.colisiones), maxColisiones (orig.maxColisiones), factorCarga (orig.factorCarga){
}


THashPalabra& THashPalabra::operator =(const THashPalabra& orig){
    if (this != &orig){
        tamF = orig.tamF;
        tamL = orig.tamL;
        primoMenor = orig.primoMenor;
        tabla = orig.tabla;
        
    }
}

THashPalabra::~THashPalabra() {
}

unsigned int THashPalabra::numPalabras() const{
    return tamL;
}

bool THashPalabra::insertar(unsigned long clave, Palabra& pal){
    bool insertado = false;
    Palabra* pPal = nullptr;
    string termino = pal.GetPalabra();
    if (!buscar(clave,termino,pPal)){ //Entonces no lo ha encontrado y hay que insertarlo
        //DUDA: SI BUSCO PREVIAMENTE NO ESTOY HACIENDO UN MISMO PROCESO (MÁS O MENOS) 2 VECES ??
        int intento = 0;
        while (intento < tamF && !insertado){
            long h = hashDoble1(clave,intento); //TODO: IR CAMBIANDO PARA HACER LAS TABLAS
            if (tabla[h]._estado != ocupada){
                tabla[h].dato = pal;
                //cout<<"PALABRA INSERTADA : "<<tabla[h].dato.GetPalabra()<<endl;
                tabla[h].dato.incrementarOcurrencia();
                tabla[h]._estado = ocupada;
                ++tamL;
                
                //COMPROBAR SI ES EL MAXIMO DE COLISIONES RESPECTO AL GUARDADO
                if (intento > maxColisiones) 
                    maxColisiones = intento;
                insertado = true;
            }
            ++colisiones;
            ++intento;
        }
    }else{
        return true; //PARA EVITAR QUE LO AÑADA COMO PALABRA INEXISTENTE.
    }
    return insertado;
}

bool THashPalabra::borrar(unsigned long clave, string& termino){
    bool borrar = false;
    int intento = 0;
    while ( intento < tamF && !borrar) {
        unsigned h = hashDoble1(clave,intento);
        if (tabla[h]._estado == ocupada){
            if (tabla[h].dato.GetPalabra() == termino){
                tabla[h]._estado = disponible;
                --tamL;
                borrar = true;
            }
        
        }
        intento++;
    }
    return borrar;
}

bool THashPalabra::buscar(unsigned long clave, string& termino, Palabra*& pal){
    int intento = 0;
    while(intento < tamF){
        long h = hashDoble1(clave,intento); //TODO: IR CAMBIANDO PARA HACER LAS TABLAS
        if (tabla[h]._estado == ocupada){ //Entonces, posiblemente que esté en esa posición.
            if (tabla[h].dato.GetPalabra() == termino){ //Entonces, sí que es la palabra a buscar.
                pal = &tabla[h].dato; 
                tabla[h].dato.incrementarOcurrencia();
                return true;
            }
        }else if (tabla[h]._estado == vacia){ //Entonces, termina de buscar
            pal = nullptr;
            return false;
        }
        ++intento;
    } 
    return false;
}


/*---- MÉTODOS DE ENTRENAMIENTO ----*/
unsigned int THashPalabra::MaxColisiones() const{
    return maxColisiones;
}

float THashPalabra::promedioColisiones() const{
    return (float)colisiones/tamL;
}

float THashPalabra::FactorCarga() const{
    return factorCarga;
}

unsigned int THashPalabra::tamTabla() const{
    return tamF;
}


/*---- MÉTODOS PRIVADOS ----*/


unsigned int THashPalabra::sigPrimo(unsigned int num, unsigned int& primoAnterior){
    unsigned int primoMayor = num, a = 0;
    primoAnterior = num;
    bool primoMayorEncontrado = false, primoMenorEncontrado = false;
    while (!primoMayorEncontrado && primoMayor < 100000){ //TODO: AÑADIR UN LIMITE.
        for (int i = 1; i < (primoMayor + 1); i++)
            if (primoMayor % i == 0)
                a++;
        
        if (a == 2)
            primoMayorEncontrado = true;
        else
            ++primoMayor;
        a = 0;
    }
    
    while (!primoMenorEncontrado && primoAnterior > 0){ //TODO: AÑADIR UN LIMITE.
        for (int i = 1; i < (primoAnterior + 1); i++)
            if (primoAnterior % i == 0)
                a++; 
        
        if (a == 2){
            primoMenorEncontrado = true;
        }else
            --primoAnterior;
        a = 0;
    }
    return primoMayor;
}



/**
 * @brief Dispersión doble 1.
 * @post Función hash privada que, a partir de la fórmula general de la dispersión 
 * doble, la función h2 se caracteriza por al primoMenor al correspondiente del tamaño
 * lógico se le resta el valor del módulo de la clave respecto a ese primo. De esta forma
 * se evita que h2 = 0 en algún momento.
 * @param clave
 * @param intento
 * @return 
 */
long THashPalabra::hashDoble1(unsigned long clave, int intento){
    unsigned h1 = clave % tamF; //Suponiendo que el tamF es precalculado de forma que sea un primo.
    unsigned h2 = primoMenor - (clave % primoMenor); 
    return  ((h1 + (intento * h2))%tamF); //Fórmula de las diapositivas.
}

/**
 * @brief Dispersión doble 2.
 * @post A partir de la fórmula general de dispersión doble, se crea una h2 diferente
 * tal que se añada 1 siempre para evitar la condición necesaria de que h2 != 0.
 * @param clave
 * @param intento
 * @return 
 */
long THashPalabra::hashDoble2(unsigned long clave, int intento){
    unsigned h1 = clave % tamF; //Suponiendo que el tamF es precalculado de forma que sea un primo.
    unsigned h2 = 1 + (clave % primoMenor); //h2 nunca puede ser 0 entonces sumo 1 siempre.
    return  ((h1 + (intento * h2))%tamF); //Fórmula de las diapositivas.
}

/**
 * @brief Exploración cuadrática.
 * @post Función hash cuadrática privada que evita agrupamientos primarios, pero no los secundarios.
 * @param clave
 * @param intento
 * @return 
 */
long THashPalabra::hashCuadratica(unsigned long clave, int intento){
    return (clave + intento*intento)%tamF;
}
