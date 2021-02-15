#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>
#include <iostream>
#include <cmath>
#include <set>
#include <unordered_set>
#include <stack>

struct estado {
  int fila;
  int columna;
  int orientacion;
};

struct nodo{
  estado st;
  list<Action> secuencia;

};

struct costo{
  nodo n;
  int valor;
};


struct ComparaEstados{
  bool operator()(const estado &a, const estado &n) const{
    if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
        (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
      return true;
    else
      return false;
  }
};



class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      count1=0;
      llega=false;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      count1=0;
      llega=false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    bool llega;
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    estado actual, destino;
    list<Action> plan;
    int count1;
    Action ultimaAccion;

    // Métodos privados de la clase
    bool HayObstaculoDelante(estado &st);
    bool pathFinding(int level, const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool anchura_Recursivo(list<nodo> &rec, const estado &destino,nodo &current, set<estado,ComparaEstados> &generados);
    bool pathFinding_Costo(const estado &origen, const estado &destino, list<Action> &plan);
    //void costo_Recursivo(costo &cost, const estado &destino, costo &solucion, set<estado,ComparaEstados> &generados, int &min,int **mat);
    //bool planificaSensores(Sensores sensores);
    void encuentra_Minimo(list<costo> &costos, list<costo>::iterator &min);
    void PintaPlan(list<Action> plan);
    

};

#endif
