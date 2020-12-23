/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   THashPalabra.h
 * Author: spdlc
 *
 * Created on 11 de diciembre de 2020, 17:02
 */

#ifndef THASHPALABRA_H
#define THASHPALABRA_H

#include "Palabra.h"
#include <vector>

enum estado{vacia,disponible,ocupada};

class Entrada {
public:
    long clave;
    Palabra dato;
    estado _estado;
    Entrada (unsigned long aClave, Palabra& aDato) : clave (aClave), dato (aDato), _estado (vacia) {}

    Entrada& operator=(const Entrada& orig) {
        if (this != &orig) {
            clave = orig.clave;
            dato = orig.dato;
            _estado = orig._estado;
        }
        return *this;
    }
    ~Entrada(){};
};


class THashPalabra {
private:
    unsigned long tamF, tamL, primoMenor, maxColisiones, colisiones;
    float factorCarga;
    std::vector<Entrada> tabla;
    unsigned long sigPrimo(unsigned long num, unsigned long& primoAnterior);
    
    long hashDoble1(unsigned long clave, int intento);
    long hashDoble2(unsigned long clave, int intento);
    long hashCuadratica(unsigned long clave, int intento);
public:
    THashPalabra(int tamTabla, float _factorCarga);
    THashPalabra(const THashPalabra& orig);
    THashPalabra& operator=(const THashPalabra& orig);
    virtual ~THashPalabra();
    
    unsigned int numPalabras() const;
    
    bool insertar(unsigned long clave, Palabra& pal);
    bool buscar(unsigned long clave, string& termino, Palabra*&pal);
    bool borrar(unsigned long clave, string& termino);
    
    
    /*---- MÉTODOS DE ENTRENAMIENTO DE LA TABLA ----*/
    unsigned int MaxColisiones() const;
    float promedioColisiones() const;
    float FactorCarga() const;
    unsigned int tamTabla() const;
    
    bool getPalabra(unsigned long pos, Palabra& result);

};

#endif /* THASHPALABRA_H */

