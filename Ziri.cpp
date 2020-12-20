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

#include "Ziri.h"


Ziri::Ziri():
gestor(new GestorTextos()), usuariosNIF(), conectados(),usuarioUTM(){
    std::ifstream is("usuarios_frases_win.csv"); //OJO: LA PRIMERA LINEA NO VALE
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
    }
    is.close();
    
    //RECORRER EL MAPA ENTERO PARA INSERTAR LOS USUARIOS EN SUS PUNTOS UTM CORRESPONDIENTES.
    //DUDA: PREGUNTAR SI ESTÁ ASÍ BIEN PENSADO
    int cantidadUserCelda = 2;
    int nDivX = pow((contUsuarios/cantidadUserCelda),0.5); //Si hago la raiz cuadrada del numero total de celdas saco el número de filas para el eje X y el número de columnas para el eje Y de forma equitativa.
    int nDivY = nDivX; //Como no saldrá exacto -> Aumentará la cantidad de usuarios por celda, por eso he puesto 2.
    usuarioUTM = MallaRegular<Usuario*>(xMin,xMax,yMin,yMax,nDivX,nDivY);
    
    //DUDA: PREGUNTAR SI ESTÁ ASÍ BIEN PENSADO
    for(std::map<std::string,Usuario>::iterator it = usuariosNIF.begin(); it != usuariosNIF.end(); it++){
        Usuario* new_user = new Usuario((*it).second); //Lo hago new copiando al del MAPA o pongo en el puntero la direccion de memoria del cliente en el mapa?
        usuarioUTM.insertar((*it).second.getLatitud(), (*it).second.getLongitud(), new_user);
        //usuarioUTM.insertar((*it).second.getLatitud(), (*it).second.getLongitud(), &(*it).second);
    }
    
}

Ziri::Ziri(const Ziri& orig):
usuariosNIF(orig.usuariosNIF), conectados(orig.conectados),usuarioUTM(){
    gestor = new GestorTextos(*orig.gestor);

}

Ziri::~Ziri() {
    Casilla<Usuario*>* eliminar;
    for (float x = usuarioUTM.getXMin(); x < usuarioUTM.getXMax(); x += usuarioUTM.getTamaCasillaX()){
        for (float y = usuarioUTM.getYMin(); y < usuarioUTM.getYMax(); y += usuarioUTM.getTamaCasillaY()){
            eliminar = usuarioUTM.obtenerCasilla(x,y);
            for (std::list<Usuario*>::iterator it = eliminar->inicio(); it != eliminar->fin(); it++){
                delete (*it);
                *it = nullptr;
            }
        }
    }
    
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
    std::ifstream is(frase);
    std::stringstream ss;
    std::cout<<"FRASE A CHEQUEAR: "<<frase<<std::endl;
    std::string palabra;
    Usuario *user = nullptr;
    Palabra* result = nullptr;
    std::string linea;
    getline(is,linea); //TODO: SEPARAR POR ESPACIOS !! //DUDA: SERIA ASI???
    while (is) {
        ss << linea;
        getline(ss,palabra,' ');
        Palabra pal(palabra);
        pal.limpiar();
        std::string aux = pal.conversionMinus();
        result = gestor->getDiccionario()->buscarTermino(aux, u);
        
        if (result == nullptr)
            gestor->insertarInexistente(aux,u); 

    }
    is.close(); //DUDA: NO CREO QUE ESTÉ ASI BIEN IMPLEMENTADO
}


bool Ziri::nuevoUsuarioConectado(std::string& nif){
    for (std::list<Usuario>::iterator it = conectados.begin(); it != conectados.end(); it++)
        if ((*it).getNif() == nif)
            return false; //Ya estaba conectado
    
    std::map<std::string, Usuario>::iterator ite = usuariosNIF.find(nif);
    if(ite != usuariosNIF.end()){
        conectados.push_back((*ite).second);
        return true; 
    }
    return false; //NO EXISTE ESE USUARIO EN EL MAPA
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
        if ((*it).getNif() == u.getNif())
            chequearTexto(frase,u); //DUDA: HACER ALGO MAS O SIMPLEMENTE EL METODO PUBLICO PARA LLAMAR AL PRIVADO DE CHEQUEAR?
    }
}

std::list<Usuario>& Ziri::analizarTermino(std::string& palabra){
    return gestor->getDiccionario()->buscarPalabra(palabra)->usadoPorUsers();
}

//std::list<Usuario>& Ziri::buscarTerminoRango(std::string& palabra, float rxmin, float rymin, float rxmax, float rymax){
//    std::list<Usuario> palabUsersRango;
//    std::list<Usuario> todos = analizarTermino(palabra); //Me devuelve todos los usuarios que han usado la palabra.
//    std::vector<Usuario*> rangoUser = usuarioUTM.buscarRango(rxmin,rymin,rxmax,rymax); //DUDA: POR QUE NO ME FUNCIONA DE ESTA FORMA ?
//    
//    bool aniadido;
//    for(int i = 0; i < rangoUser.size(); i++){
//        aniadido = false;
//        for (std::list<Usuario>::iterator it = todos.begin(); it != todos.end() && !aniadido; it++){
//            if ((*it).getNif() == rangoUser[i]->getNif()){
//                palabUsersRango.push_back(*(rangoUser[i])); 
//                aniadido = true;
//            }
//        }
//    }
//    return palabUsersRango;
//}