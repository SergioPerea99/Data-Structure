/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ziri.cpp
 * Author: spdlc
 * 
 * Created on 20 de diciembre de 2020, 11:01
 */

#include <math.h>
#include <complex>
#include <list>


#include "Ziri.h"


Ziri::Ziri():
gestor(new GestorTextos()), usuariosNIF(), conectados(){
    std::ifstream is("usuarios_frases_win_LIMPIO.csv"); //OJO: LA PRIMERA LINEA NO VALE
    stringstream ss;
    std::string linea; //Cada linea es un usuario para el csv. TODO: Separados por ";"
    std::string nif, nombre, nomape, direccion, latitud, longitud, frase; //Variables de recogida de datos del dataset
    
    float xMin = MAXFLOAT, xMax = -MAXFLOAT, yMin = MAXFLOAT, yMax = -MAXFLOAT; //Coordenadas máximas y mínimas para la construcción de la malla
    int contUsuarios = 0;
    
    getline(is,linea); //Primera linea del fichero que no sirve de nada
    while(is){
        getline(is,linea);
        ss << linea;
        getline(ss,nif,';');
        getline(ss,nombre,';');
        getline(ss,nomape,';');
        getline(ss,direccion,';');
        getline(ss,latitud,';');
        getline(ss,longitud,';');
        getline(ss,frase,';');
        getline(ss,linea,';');
        //CREAR UN USUARIO CON LOS DATOS OBTENIDOS
        Usuario user(nif,nomape,nombre,frase,stof(latitud),stof(longitud),this);
        
        //COMPROBAR QUE LAS COORDENADAS QUE DA SON (O NO) LAS MENORES O MAYORES ENCONTRADAS.
        if(user.getLatitud() < xMin) xMin = user.getLatitud();
        if(user.getLatitud() > xMax) xMax = user.getLatitud();
        
        if(user.getLongitud() < yMin) yMin = user.getLongitud();
        if(user.getLongitud() > yMax) yMax = user.getLongitud();
        
        
        //AÑADIRLO EN LAS EEDD DEL MAP QUE RECOGE A TODOS LOS USUARIOS DEL ARCHIVO CSV
        usuariosNIF.insert(pair<std::string,Usuario>(user.getClave(),user));
        
        contUsuarios++; //Para estimar sobre cuanto dividir la malla regular
        ss.clear();
    }
    is.close();
    //RECORRER EL MAPA ENTERO PARA INSERTAR LOS USUARIOS EN SUS PUNTOS UTM CORRESPONDIENTES.
    float cantidadUserCelda = 2.5;
    int nDivX = ceil(pow((contUsuarios/cantidadUserCelda),0.5)); //Si hago la raiz cuadrada del numero total de celdas saco el número de filas para el eje X y el número de columnas para el eje Y de forma equitativa.
    int nDivY = nDivX; //Como no saldrá exacto -> Aumentará la cantidad de usuarios por celda, por eso he puesto 2.
    usuarioUTM = MallaRegular<Usuario*>(floor(xMin),floor(yMin),ceil(xMax),ceil(yMax),nDivX,nDivY); //Necesito redondear porque sino me da problemas la inserción en la MALLA REGULAR.
    int insertadosUTM = 0;
    for(std::map<std::string,Usuario>::iterator it = usuariosNIF.begin(); it != usuariosNIF.end(); it++){
        usuarioUTM.insertar((*it).second.getLatitud(), (*it).second.getLongitud(), &(*it).second);
    }
    cout<<"NUMERO TOTAL DE USUARIOS EN LA APLICACIÓN = "<<usuariosNIF.size()<<endl;
    cout<<"PROMEDIO DE USUARIOS POR CELDA = "<<usuarioUTM.promedioElementosPorCelda()<<endl;
    
    /*LOGUEAR A TODOS MENOS LOS 50 ÚLTIMOS USUARIOS DEL MAPA*/
    for (std::map<std::string,Usuario>::iterator it = usuariosNIF.begin() ; it != usuariosNIF.end(); it++)
        if (conectados.size() < usuariosNIF.size() - 50)
            conectados.push_back((*it).second);
    
    cout<<"USUARIOS CONECTADOS = "<<conectados.size()<<" de "<<usuariosNIF.size()<<endl;
}

Ziri::Ziri(const Ziri& orig):
usuariosNIF(orig.usuariosNIF), conectados(orig.conectados),usuarioUTM(){
    gestor = new GestorTextos(*orig.gestor);

}

Ziri::~Ziri() {
    if (gestor)
        delete gestor;
    gestor = nullptr;
}


/**
 * @brief Chequear texto.
 * @post La aplicación en sí chequea que palabras de su documento son y cuáles no partícipes del diccionario que tiene asociado a través del
 * objeto GestorTextos.
 */
void Ziri::chequearTexto(std::string frase, Usuario& u){
    std::stringstream ss(frase);
    //std::cout<<"FRASE A CHEQUEAR: "<<frase<<std::endl;
    std::string palabra;
    Palabra* result = nullptr;
    while (ss) {
        getline(ss,palabra,' ');
        Palabra pal(palabra);
        pal.limpiar();
        std::string aux = pal.conversionMinus();
        result = gestor->getDiccionario()->buscarTermino(aux, u);
        if (result == nullptr)
            gestor->insertarInexistente(aux,u); 

    }
}


Usuario* Ziri::nuevoUsuarioConectado(std::string& nif,std::string& pass){
    for (std::list<Usuario>::iterator it = conectados.begin(); it != conectados.end(); it++){
        if ((*it).getNif() == nif){
            std::cout<<"EL USUARIO YA ESTABA CONECTADO"<<endl;
            return nullptr; //Ya estaba conectado
        }
    }
    
    std::map<std::string, Usuario>::iterator ite = usuariosNIF.find(nif);
    if(ite != usuariosNIF.end()){
        if ((*ite).second.getClave() == pass){
            conectados.push_back((*ite).second);
            std::cout<<"CONECTADO AL USUARIO..."<<endl;
            return &(*ite).second; 
        }
        std::cout<<"NO SE HA ENCONTRADO UN USUARIO EN EL MAPA CON ESA CLAVE"<<endl;
    }
    std::cout<<"NO SE HA ENCONTRADO UN USUARIO EN EL MAPA CON ESE NIF"<<endl;
    return nullptr; //NO EXISTE ESE USUARIO EN EL MAPA
}

bool Ziri::desconectarUsuario(std::string& nif){
    for (std::list<Usuario>::iterator it = conectados.begin(); it != conectados.end(); it++){
        if ((*it).getNif() == nif){
            conectados.erase(it);
            return true; //Lo desconecta eliminandolo de la lista de conectados
        }
    }
    return false; //No ha encontrado ese usuario conectado      
}


void Ziri::recibeMensajeUsuario(std::string& frase, Usuario& u){
    for (std::list<Usuario>::iterator it = conectados.begin(); it != conectados.end(); it++){
        if ((*it).getNif() == u.getNif()){
            chequearTexto(frase,u);
        }
    }
}

std::list<Usuario>* Ziri::analizarTermino(std::string& palabra){
    return gestor->getDiccionario()->buscarPalabra(palabra)->usadoPorUsers();
}


/**
 * @brief Buscar Termino en un rango de usuarios
 * @post IMPORTANTE: SE RESERVA MEMORIA A LA ESTRUCTURA PASADA COMO RETURN -> ELIMINAR DICHA MEMORIA CUANDO EL USUARIO NO LO NECESITE MÁS
 * Método encargado de, a partir de una palabra usada por unos usuarios, comprobar que usuarios se encuentran en el rango indicado.
 * @param palabra
 * @param rxmin
 * @param rymin
 * @param rxmax
 * @param rymax
 * @return 
 */
std::list<Usuario>* Ziri::buscarTerminoRango(std::string& palabra, float rxmin, float rymin, float rxmax, float rymax){
    std::list<Usuario>* palabUsersRango = new std::list<Usuario>();
    std::list<Usuario>* todos = analizarTermino(palabra); //Me devuelve todos los usuarios que han usado la palabra.
    std::vector<Usuario*>* rangoUser = usuarioUTM.buscarRango(rxmin,rymin,rxmax,rymax);
    
    bool aniadido;
    for(int i = 0; i < rangoUser->size(); i++){
        aniadido = false;
        for (std::list<Usuario>::iterator it = todos->begin(); it != todos->end() && !aniadido; it++){
            if ((*it) == (*(*rangoUser)[i])){
                palabUsersRango->push_back((*(*rangoUser)[i])); 
                aniadido = true;
            }
        }
    }
    return palabUsersRango;
}


int Ziri::tamUserConectados(){
    return conectados.size();
}

Usuario& Ziri::userConectado(unsigned int pos){
    if (pos >= conectados.size())
        throw std::out_of_range("[Ziri::userConectado] La posición dada está fuera de rango");
    
    std::list<Usuario>::iterator it = conectados.begin();
    for (int i = 0; i < pos; i++)
        it++;
    
    return (*it);
}

GestorTextos* Ziri::getGestor(){
    return gestor;
}
