/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Documento.cpp
 * Author: spdlc
 * 
 * Created on 20 de octubre de 2020, 18:40
 */

//#include "Documento.h"
//
///**
// * @brief Constructor por defecto.
// */
//Documento::Documento(): nombreFich ("quijote-sin-simbolos.txt"), dicc (nullptr){
//
//}
//
///**
// * @brief Constructor parametrizado.
// * @param _texto Nombre del documento.
// * @param _dicc Puntero al diccionario que tiene asociado este Documento.
// */
//Documento::Documento(std::string _texto, DiccionarioConVerbos*& _dicc) : nombreFich (_texto), dicc (_dicc), palabras(){
//
//}
//
///**
// * @brief Constructor copia.
// * @param orig Documento a ser copiado.
// */
//Documento::Documento(const Documento& orig): nombreFich (orig.nombreFich), dicc (orig.dicc), palabras (orig.palabras){
//
//}
//
//
///**
// * @brief Operador de igualdad.
// * @param dato Dato a ser comparado con el destinatario.
// * @return Booleano falso o verdadero.
// */
//bool Documento::operator ==(const Documento& dato){
//    return nombreFich == dato.nombreFich ? true : false;
//}
//
///**
// * @brief Operador de asignación.
// * @param dato Dato a ser asignado al destinatario.
// * @return Documento destinatario, con la posibilidad de realizar una asignación en cascada por el &.
// */
//Documento& Documento::operator =(const Documento& dato){
//    if(this != &dato){
//        nombreFich = dato.nombreFich;
//        dicc = dato.dicc;
//    }
//    return *this;
//}
//
///**
// * @brief Chequear texto.
// * @post El propio documento en sí chequea que palabras de su documento son y cuáles no partícipes del diccionario que tiene asociado.
// * Dependiendo del número del parámetro, se realizará una búsqueda de palabras del diccionario básico (número 2, por la práctica 2)
// * o en caso de pasar como parámetro el valor 3 (número de la práctica 3) se comprueba también si dicha palabra es un verbo conjugado.
// * @param num_practica Número que indica que tipo de busqueda de palabras en el diccionario se quiere realizar.
// */
//void Documento::chequearTexto(){
//    ifstream is(nombreFich);
//    cout<<"NOMBRE DEL FICHERO QUE SE VA A CHEQUEAR: "<<nombreFich<<endl;
//    string palabra;
//    Palabra *result = nullptr;
//    Palabra aniadir;
//    int no_validadas = 0, total = 0, p;
//    while (is) {
//        is >> palabra;
//        Palabra pal(palabra);
//        //pal.SetUltima_aparicion(this);
//        ++total;
//        /*Ahora limpio la palabra para comprobar si existe en el diccionario.*/
//        pal.limpiar();
//        string aux = pal.conversionMinus();
//        unsigned long clave = getDicc()->djb2((unsigned char*)aux.c_str());
//        if (!getDicc()->buscarTermino(clave,aux, result)) {
//            ++no_validadas;
//            insertarInexistente(pal); 
//        }
//        
//    }
//    
//    is.close();
//    
//}
//
//
///**
// * @brief Destructor.
// */
//Documento::~Documento() {
//    
//}
//
//
//
///*---- GETTERS Y SETTERS ----*/
//
//void Documento::setNombreFich(std::string nombreFich) {
//    this->nombreFich = nombreFich;
//}
//
//std::string Documento::getNombreFich(){
//    return nombreFich;
//}
//
//DiccionarioConVerbos* Documento::getDicc() const{
//    return dicc;
//}
//
//void Documento::setDicc(DiccionarioConVerbos* dicc) {
//    this->dicc = dicc;
//}
//
//
//
//bool Documento::insertarInexistente(Palabra& pal){
//    list<Palabra>::iterator it = palabras.begin();
//    while (it != palabras.end()){
//        if ((*it).GetPalabra() == pal.GetPalabra())
//            return false; //Encontrado, entonces no se inserta otra vez.
//        it++;
//    }
//    //No ha sido encontrada la palabra, entonces se inserta al final.
//    palabras.push_back(pal);
//    return true;
//}
