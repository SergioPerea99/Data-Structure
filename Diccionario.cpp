/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Diccionario.cpp
 * Author: spdlc
 * 
 * Created on 20 de octubre de 2020, 18:06
 */

#include <time.h>

#include "Diccionario.h"

/**
 * @brief Constructor por defecto.
 */
Diccionario::Diccionario() {
    verbos = new VerbosConjugados();
    nombreFich = "dicc-espanol-sin.txt";
    /*Primera parte: Cargar el diccionario en el Gestor de Textos.*/
    ifstream is("dicc-espanol-sin.txt");
    string palabra;
    Palabra pal;
    while (is) {
        is >> palabra;
        pal.SetPalabra(palabra);
        terminos.insertar(pal);
    }
    /*Ordenación para poder luego buscar en él con una búsqueda binaria.*/
    terminos.ordenar();
    cout << terminos.tam() << " palabras cargadas en los TERMINOS del diccionario." << endl;
    is.close();
}

/**
 * @brief Constructor parametrizado.
 * @param _nombreFich String que indica el nombre del diccionario.
 */
Diccionario::Diccionario(std::string _nombreFich){
    verbos = new VerbosConjugados("verbos_conjugados_sin_tildes_desordenados.txt");
    nombreFich = _nombreFich;
    /*Primera parte: Cargar el diccionario en el Gestor de Textos.*/
    ifstream is(_nombreFich);
    string palabra;
    Palabra pal;
    while (is) {
        is >> palabra;
        pal.SetPalabra(palabra);
        terminos.insertar(pal);
    }
    /*Ordenación para poder luego buscar en él con una búsqueda binaria.*/
    terminos.ordenar();
    cout << terminos.tam() << " palabras cargadas en los TERMINOS del diccionario." << endl;
    is.close();
}

/**
 * @brief Constructor copia.
 * @param orig Diccionario a copiar.
 */
Diccionario::Diccionario(const Diccionario& orig) {
    nombreFich = orig.nombreFich;
    terminos = orig.terminos;
    verbos = orig.verbos;
    
}

/**
 * @brief Destructor.
 * @post Se destruye, en caso de haber sido reservado memoria para ello, los verbos
 * los cuales formaban parte del diccionario.
 */
Diccionario::~Diccionario() {
    if(verbos)
        delete verbos;
    verbos = nullptr;
}


/**
 * @brief Operador de asignación.
 * @param orig Diccionario a ser asignado por el destinatario.
 * @return 
 */
Diccionario& Diccionario::operator =(const Diccionario& orig){
    if (this != &orig){
        nombreFich = orig.nombreFich;
        terminos = orig.terminos;
        if(verbos)
            delete verbos;
        verbos = new VerbosConjugados(*orig.verbos);
    }
}

bool Diccionario::buscar(Palabra& buscar, double& t_buscDicotomica_MAX, double& t_buscAVL_MAX,double&  t_buscDicotomica_MIN,double& t_buscAVL_MIN){
    time_t t0, t1;
    double varMax = 0.0;
    
    t0 = clock(); /*Comienzo de tiempo de búsqueda dicotómica, encuentre o no el elemento a buscar quedándose con el mayor de los tiempos.*/
    if(buscarDicotomica(buscar)){
        t1 = clock();
        varMax = (double)(t1-t0)/CLOCKS_PER_SEC;
        if (t_buscDicotomica_MAX < varMax) t_buscDicotomica_MAX = varMax;
        if (t_buscDicotomica_MIN > varMax) t_buscDicotomica_MIN = varMax;
        return true;
    }else{
        t1 = clock();
        varMax = (double)(t1-t0)/CLOCKS_PER_SEC;
        if (t_buscDicotomica_MAX < varMax) t_buscDicotomica_MAX = varMax;
        if (t_buscDicotomica_MIN > varMax) t_buscDicotomica_MIN = varMax;
        t0 = clock(); /*Comienzo de tiempo de búsqueda en árbol, encuentre o no el elemento a buscar quedándose con el mayor de los tiempos.*/
        if (verbos->buscar(buscar)){
            t1 = clock();
            varMax = (double)(t1-t0)/CLOCKS_PER_SEC;
            if (t_buscAVL_MAX < varMax) t_buscAVL_MAX = varMax;
            if (t_buscAVL_MIN > varMax) t_buscAVL_MIN = varMax;
            return true;
        }
        t1 = clock();
        varMax = (double)(t1-t0)/CLOCKS_PER_SEC;
        if (t_buscAVL_MAX < varMax) t_buscAVL_MAX = varMax;
        if (t_buscAVL_MIN > varMax) t_buscAVL_MIN = varMax;
    }
    return false;
}


/*---- GETTERS Y SETTERS ----*/

Palabra* Diccionario::GetTermino(unsigned int pos){
    return &terminos[pos];
}

void Diccionario::SetNombreFich(std::string nombreFich) {
    this->nombreFich = nombreFich;
}

std::string Diccionario::GetNombreFich() const {
    return nombreFich;
}

VerbosConjugados* Diccionario::getVerbos() const {
    return verbos;
}


/*---- MÉTODOS PRIVADOS ----*/
/**
 * @brief Busqueda dicotómica.
 * @post Busqueda logarítmica que a su vez llamará al búsqueda binaria de la estructura de datos del vector dinámico.
 * @param buscar Dato de tipo Palabra que se quiere buscar.
 * @return Booleano que expresa si se ha encontrado o no.
 */
bool Diccionario::buscarDicotomica(const Palabra& buscar){
    //Suponemos que el vector de palabras debe de estar ordenado para su llamada.
    int pos = terminos.busquedaBin(buscar);
    if(pos != -1)
        return true;
    return false;
}