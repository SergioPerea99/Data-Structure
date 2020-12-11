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
#include <list>

#include "DiccionarioConVerbos.h"
#include "Documento.h"

/**
 * @brief Constructor por defecto.
 */
DiccionarioConVerbos::DiccionarioConVerbos(): terminos(60000),nombreDicc("dicc-espanol-sin.txt"), nombreDiccVerbos("verbos_conjugados_sin_tildes_desordenados.txt"){
    
    /*Primera parte: Cargar las palabras del diccionario en el map.*/
    ifstream is(nombreDicc);
    string palabra;
    Palabra *pal = nullptr;
    while (is) {
        is >> palabra;
        //pal = new Palabra(palabra,this);
        Palabra pal (palabra,this);
        unsigned long clave = djb2((unsigned char*)pal.GetPalabra().c_str());
        //pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insertar(clave,pal); 
    }
    is.close();
    
    /*Segunda parte: cargar los verbos conjugados en el map.*/
    is.open(nombreDiccVerbos);
    while (is) {
        is >> palabra;
        //pal = new Palabra(palabra,this);
        Palabra pal (palabra,this);
        unsigned long clave = djb2((unsigned char*)pal.GetPalabra().c_str());
        //pair<std::string, Palabra*> palab(palabra,pal);
        terminos.insertar(clave,pal); 
    }
    is.close();
    
    cout <<"DICCIONARIO: "<< terminos.numPalabras() << " palabras cargadas en los TERMINOS del diccionario." << endl;
}


/**
 * @brief Constructor parametrizado.
 * @param _nombreFich String que indica el nombre del diccionario.
 */
DiccionarioConVerbos::DiccionarioConVerbos(std::string _nombreDicc, std::string _nombreDiccVerbos): terminos(60000),/*TODO: NO PONER ESE VALOR ASÍ*/ nombreDicc (_nombreDicc), nombreDiccVerbos(_nombreDiccVerbos) {
    
    /*Primera parte: Cargar palabras del diccionario en el map.*/
    ifstream is(nombreDicc);
    string palabra;
    Palabra *pal = nullptr;
    while (is) {
        is >> palabra;
        //pal = new Palabra(palabra,this);
        Palabra pal (palabra,this);
        //pair<std::string, Palabra*> palab(palabra,pal);
        unsigned long clave = djb2((unsigned char*)pal.GetPalabra().c_str());
        terminos.insertar(clave,pal);
    }
    is.close();
    
    /*Segunda parte: cargar los verbos conjugados en el map.*/
    is.open(nombreDiccVerbos);
    while (is) {
        is >> palabra;
        //pal = new Palabra(palabra,this);
        Palabra pal (palabra,this);
        //pair<std::string, Palabra*> palab(palabra,pal);
        unsigned long clave = djb2((unsigned char*)pal.GetPalabra().c_str());
        terminos.insertar(clave,pal);
    }
    is.close();
    
    cout << terminos.numPalabras() << " palabras cargadas en los TERMINOS del diccionario." << endl;
}

/**
 * @brief Constructor copia.
 * @param orig Diccionario a copiar.
 */
DiccionarioConVerbos::DiccionarioConVerbos(const DiccionarioConVerbos& orig) : nombreDicc(orig.nombreDicc) , 
        nombreDiccVerbos(orig.nombreDiccVerbos), 
        terminos (orig.terminos){
    
}

/**
 * @brief Destructor.
 * @post Se destruye, en caso de haber sido reservado memoria para ello, los verbos
 * los cuales formaban parte del diccionario.
 */
DiccionarioConVerbos::~DiccionarioConVerbos() {
//    map<std::string, Palabra*>::iterator it = terminos.begin();
//    while(it != terminos.end()){
//        delete it->second;
//        terminos.erase(it); /*DUDA: Si he eliminado con erase pero he creado un new de Palabras en esta clase para almacenarlo en esos nodos del mapa, ¿con el erase no haría falta liberar su memoria?*/
//        it = terminos.lower_bound(it->first); 
//    }
}


/**
 * @brief Operador de asignación.
 * @param orig Diccionario a ser asignado por el destinatario.
 * @return 
 */
DiccionarioConVerbos& DiccionarioConVerbos::operator =(const DiccionarioConVerbos& orig){
    if (this != &orig){
        nombreDicc = orig.nombreDicc;
        nombreDiccVerbos = orig.nombreDiccVerbos;
        terminos = orig.terminos;
        
    }
}

/**
 * @brief Buscar un término.
 * @post Busca la clave pasada como parámetro en el map de forma que si la encuentra, asigna el valor del dato en result y devuelve un true.
 * @param termino Clave a buscar.
 * @param result Palabra encontrada, en caso de encontrarse.
 * @return Booleano que indica si se ha encontrado o no.
 */
bool DiccionarioConVerbos::buscarTermino(string& termino, Palabra* &result){
    unsigned long clave = djb2((unsigned char*)termino.c_str());
    return terminos.buscar(clave,termino,result);
//    map<std::string, Palabra*>::iterator ite = terminos.find(termino);
//    if(ite != terminos.end()){
//        result = ite->second;
//        ite->second->incrementarOcurrencia();
//        return true;
//    }else
//        return false;
}


/**
 * @brief Buscar familia de una palabra.
 * @post A partir de una subcadena raiz, devolver una lista de todas las palabras
 * que contienen como subcadena raiz la misma que la pasada como parámetro.
 * @param raiz String a buscar como subcadena en el map.
 * @return Lista de palabras que forman la familia.
 */
//void DiccionarioConVerbos::buscarFamilias(std::string raiz,list<Palabra>* familia){
//    map<std::string, Palabra*>::iterator it = terminos.find(raiz);
//    std::string comprobar = it->first; /*Creo una variable para no hacer operaciones con el iterador.*/
//    while(comprobar.substr(0,raiz.length()) == raiz){ /*Supongo que al iterar hacia abajo o encuentra el final o sale por donde empezó.*/
//        familia->push_back(*it->second); /*Copio la palabra en la lista ya que sigue en el bucle que comprueba que es de la familia.*/
//        it++;
//        comprobar = it->first; /*Copio la nueva clave, para ver en el condicional si sigue siendo de la familia.*/
//    }
//}


Palabra* DiccionarioConVerbos::insertarInexistente(Palabra& dato){
    //Palabra *aniadir = new Palabra(dato.GetPalabra(),nullptr); 
    //pair<std::string, Palabra*> palab(aniadir->GetPalabra(),aniadir);
    //std::string clave = aniadir->GetPalabra();
    //Palabra pal (dato,this);
    unsigned long clave = djb2((unsigned char*)dato.GetPalabra().c_str());
    terminos.insertar(clave,dato);
    //pair<map<std::string,Palabra*>::iterator,bool> par = terminos.insert(palab);
    //cout<<"LLEGA PARA INSERTAR "<<aniadir->GetPalabra()<<endl;
    //if (par.second)
        //cout<<"INSERTADO"<<endl;
    //aniadir->incrementarOcurrencia(); /*Numero de veces que ha aparecido: 1.*/
    return &dato;
}

/*---- GETTERS Y SETTERS ----*/

void DiccionarioConVerbos::SetNombreFich(std::string nombreFich) {
    nombreDicc = nombreFich;
}

std::string DiccionarioConVerbos::GetNombreFich() const {
    return nombreDicc;
}

void DiccionarioConVerbos::setNombreDiccVerbos(std::string nombreDiccVerbos) {
    nombreDiccVerbos = nombreDiccVerbos;
}

std::string DiccionarioConVerbos::getNombreDiccVerbos() const {
    return nombreDiccVerbos;
}


int DiccionarioConVerbos::tamTerminos(){
    return terminos.numPalabras();
}


//void DiccionarioConVerbos::mostrarDiccionario(){
//    std::map<std::string,Palabra*>::iterator it = terminos.begin();
//    while (it != terminos.end()){
//        if(it->second->GetUltima_aparicion())
//            cout<<"["<<it->second->GetPalabra()<<", "<<it->second->GetUltima_aparicion()->getNombreFich()<<"]  ";
//        it++;
//    }
//}


unsigned long DiccionarioConVerbos::djb2(unsigned char* str){
    unsigned long hash = 5381;
    int c;
    
    while (c = *str++) hash = ((hash << 5) + hash) + c;
    return hash;
}