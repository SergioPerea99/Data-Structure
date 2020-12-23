/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MallaRegular.h
 * Author: spdlc
 *
 * Created on 19 de diciembre de 2020, 16:20
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H
#include <vector>
#include <list>

template <typename T>
class Casilla{
    std::list<T> puntos;
public:
      Casilla(): puntos(){};
      Casilla(const Casilla& orig): puntos(orig.puntos){};
      ~Casilla(){};
      int tamaDatos(){ return puntos.size();};
      typename std::list<T>::iterator inicio(){ return puntos.begin(); };
      typename std::list<T>::iterator fin(){ return puntos.end(); }; 
      void insertar(const T& dato){ puntos.push_back(dato);};
      
      T* buscar(const T& dato){
          typename std::list<T>::iterator it; 
          
          for (it = puntos.begin(); it != puntos.end(); it++)
              if(*it == dato)
                  return *it;
          return nullptr;
      };
      
      bool borrar(const T& dato){
          typename std::list<T>::iterator it;
          for (it = puntos.begin(); it != puntos.end(); it++){
              if (*it == dato){
                  puntos.erase(it); 
                  return true;
              }
          }
          return false;
      }
      
};

template <typename T>
class MallaRegular {
private:
    float xMin, xMax, yMin, yMax; //Tamaño real global de la M.R.
    float tamaCasillaX, tamaCasillaY; //Tamaño real de cada Casilla
    std::vector<std::vector<Casilla<T> > > mr; //Vector 2D de casillas
public:
    MallaRegular();
    MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY);
    MallaRegular(const MallaRegular& orig);
    virtual ~MallaRegular(){};
    Casilla<T>* obtenerCasilla(float x, float y);
    
    void insertar(float x, float y, const T& dato); 
    T* buscar(float x, float y, const T& dato);
    bool borrar(float x, float y, const T& dato);
    
    std::vector<T>* buscarRango(float rxmin, float rymin, float rxmax, float rymax);
    unsigned maxElementosPorCelda();
    float promedioElementosPorCelda();
    
    
    /*---- GETTERS Y SETTERS ----*/
    float getYMax() const;
    float getYMin() const;
    float getXMax() const;
    float getXMin() const;
    float getTamaCasillaY() const;
    float getTamaCasillaX() const;
    
    
};

template <typename T>
MallaRegular<T>::MallaRegular(){}

template <typename T>
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY):
    xMin(aXMin),xMax(aXMax), yMin(aYMin), yMax(aYMax){
    tamaCasillaX = (aXMax-aXMin)/nDivX;
    tamaCasillaY = (aYMax-aYMin)/nDivY;
    mr.insert(mr.begin(),nDivX,std::vector<Casilla<T>>(nDivY));
}

template <typename T>
MallaRegular<T>::MallaRegular(const MallaRegular& orig):
    xMin(orig.xMin),xMax(orig.xMax), yMin(orig.xMin), yMax(orig.yMax),
    tamaCasillaX(orig.tamaCasillaX), tamaCasillaY(orig.tamaCasillaY),
    mr(orig.mr)
{
}

template <typename T>
void MallaRegular<T>::insertar(float x, float y, const T& dato){
    if (x < xMin || x > xMax || y < yMin || y > yMax)
        throw std::out_of_range("[MallaRegular<T>::insertar] Se ha introducido mal los valores de los parámetros x ó y. Revisar que no se salgan del rango de la M.R.");
    Casilla<T>* c = obtenerCasilla(x,y);
    c->insertar(dato);
}

template <typename T>
bool MallaRegular<T>::borrar(float x, float y, const T& dato){
    if (x < xMin || x > xMax || y < yMin || y > yMax)
        throw std::out_of_range("[MallaRegular<T>::borrar] Se ha introducido mal los valores de los parámetros x ó y. Revisar que no se salgan del rango de la M.R.");
    Casilla<T>* c = obtenerCasilla(x,y);
    return c->borrar(dato);
}

template <typename T>
T* MallaRegular<T>::buscar(float x, float y, const T& dato){
    if (x < xMin || x > xMax || y < yMin || y > yMax)
        throw std::out_of_range("[MallaRegular<T>::buscar] Se ha introducido mal los valores de los parámetros x ó y. Revisar que no se salgan del rango de la M.R.");
    Casilla<T>* c = obtenerCasilla(x,y);
    return c->buscar(dato);
}

template <typename T>
std::vector<T>* MallaRegular<T>::buscarRango(float rxmin, float rymin, float rxmax, float rymax){
    std::vector<T>* devolver;
    if (rxmin < xMin || rxmax > xMax || rymin < yMin || rymax > yMax)
        throw std::out_of_range("[MallaRegular<T>::borrar] Se ha introducido mal los valores de los rangos respecto al eje x y el eje y. Revisar que no se salgan del rango de la M.R.");
    
    Casilla<T>* c;
    for(float i = xMin; i < xMax; i += tamaCasillaX){
        for (float j = yMin; j  < yMax; j += tamaCasillaY){
            //TODO: COMPROBAR LOS VALORES DE Xmin, Ymin, Xmax y Ymax individualmente (Si estan los 4 en el rango -> entero, si hay alguno -> se trata como limite)
            bool insertar = true;
            if ( (i >= rxmin && (i+tamaCasillaX) <= rxmax) && (j >= rymin && (j+tamaCasillaY) <= rymax) ){ //CASO EN EL QUE ESTÁ LA CASILLA COMPLETA EN EL RANGO
                c = obtenerCasilla(i,j);
                for (typename std::list<T>::iterator it = c->inicio(); it != c->fin(); it++){
                    
                    for (int k = 0; k < devolver->size() && insertar; k++)
                        if ((*devolver)[k] == (*it)) insertar = false;
                    
                    if (insertar) devolver->push_back((*it)); //Inserta solo si no existe ya, para evitar repetidos
                }
            }
            else if ( i >= rxmin && i <= rxmax ) { //Se encuentra la pos i entre el rango de la X
                if (j >= rymin && j <= rymax){ //Compruebo si tambien se encuentra la pos j entre el rango de la Y
                    
                    c = obtenerCasilla (i,j); //CASO DONDE ENTRAN SOLO LOS USUARIOS QUE PERTENEZCAN AL RANGO Y NO TODA LA CASILLA
                    for (typename std::list<T>::iterator it = c->inicio(); it != c->fin(); it++){
                        if ((*it)->getLatitud() >= rxmin && (*it)->getLatitud() <= rxmin){ //Está en el intervalo X
                            if ((*it)->getLongitud() >= rymin && (*it)->getLongitud() <= rymax){ //Está en el intervalo Y
                                
                                for (int k = 0; k < devolver->size() && insertar; k++)
                                    if ((*devolver)[k] == (*it)) insertar = false;
                                
                                if (insertar) devolver->push_back((*it)); //Inserta solo si no existe ya, para evitar repetidos
                            }
                        }
                    }
                }
            }
        }
    }
    return devolver;
}


template <typename T>
unsigned MallaRegular<T>::maxElementosPorCelda(){
    //TODO: HACERLO CON UN ATRIBUTO, Y MIENTRAS SE INSERTA EN CASILLA COMPROBAR QUE NO SE TENGA QUE ACTUALIZAR EL MAXIMO
    unsigned maxDatoscelda = 0; 
    Casilla<T>* c;
    for(float i = xMin; i < xMax; i += tamaCasillaX){
        for (float j = yMin; j  < yMax; j += tamaCasillaY){
            c = obtenerCasilla(i, j);
            if (c->tamaDatos() > maxDatoscelda)
                maxDatoscelda = c->tamaDatos();
        }
    }
    return maxDatoscelda;
}

template <typename T>
float MallaRegular<T>::promedioElementosPorCelda(){
    float promedio = 0.0;
    int numCasillas = 0;
    Casilla<T>* c;
    for(float i = xMin; i < xMax; i += tamaCasillaX){
        for (float j = yMin; j  < yMax; j += tamaCasillaY){
            c = obtenerCasilla(i, j);
            promedio += c->tamaDatos();
            numCasillas++;
        }
    }
    
    return promedio/numCasillas;
}

/*---- GETTERS Y SETTERS ----*/

template <typename T>
float MallaRegular<T>::getYMax() const {
    return yMax;
}

template <typename T>
float MallaRegular<T>::getYMin() const {
    return yMin;
}

template <typename T>
float MallaRegular<T>::getXMax() const {
    return xMax;
}

template <typename T>
float MallaRegular<T>::getXMin() const {
    return xMin;
}

template <typename T>
float MallaRegular<T>::getTamaCasillaY() const {
    return tamaCasillaY;
}

template <typename T>
float MallaRegular<T>::getTamaCasillaX() const {
    return tamaCasillaX;
}


/*---- MÉTODOS PRIVADOS ----*/

template <typename T>
Casilla<T>* MallaRegular<T>::obtenerCasilla(float x, float y){
    int i = (x - xMin) / tamaCasillaX;
    int j = (y - yMin) / tamaCasillaY;
    return &mr[i][j];
}


#endif /* MALLAREGULAR_H */

