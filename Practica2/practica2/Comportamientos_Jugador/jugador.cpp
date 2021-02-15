#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <time.h>


// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.
Action ComportamientoJugador::think(Sensores sensores) {
	Action accion = actIDLE;
	// Estoy en el nivel 1

	if (sensores.nivel != 4){
		if (sensores.mensajeF != -1){
			fil = sensores.mensajeF;
			col = sensores.mensajeC;
			
			actual.fila = fil;
			actual.columna = col;
			actual.orientacion = brujula;

			destino.fila = sensores.destinoF;
			destino.columna = sensores.destinoC;

		}

		list<Action> aux1=plan;

		bool hay_plan = pathFinding (sensores.nivel, actual, destino, plan);

		if(count1>=1)
			if(aux1!=plan)
				count1=0;

		if(hay_plan && count1<plan.size()){
			list<Action>::iterator it=plan.begin();
			advance(it,count1);
			count1++;
			accion=*it;
			switch (accion){
				case actTURN_R: brujula= (brujula+1)%4; break;
				case actTURN_L: brujula= (brujula+3)%4;  break;
			}
		}
		if(!hay_plan){
			if(sensores.terreno[2]=='P' or sensores.terreno[2]=='M' or 
				sensores.terreno[2]=='D' or sensores.superficie[2]=='a'){
				accion=actTURN_R;
			}else{
				accion=actFORWARD;
			}
		}

	}

	else {
		// Estoy en el nivel 2
		bool hay_plan=false;
		if(!llega){
			if(sensores.terreno[0]=='K'){
				cout << "ENTRA"<<endl;
				cout << sensores.mensajeF << endl;
				cout << sensores.mensajeC << endl;
				cout << brujula << endl;
				fil=sensores.mensajeF;
				col=sensores.mensajeC;
				actual.fila = fil;
				actual.columna = col;
				actual.orientacion = brujula;
				destino.fila = sensores.destinoF;
				destino.columna = sensores.destinoC;
				switch(brujula){
					case 1:
						mapaResultado[fil][col] = sensores.terreno[0];
				        mapaResultado[fil-1][col+1] = sensores.terreno[1];
				        mapaResultado[fil][col+1] = sensores.terreno[2];
				        mapaResultado[fil+1][col+1] = sensores.terreno[3];
				        mapaResultado[fil-2][col+2] = sensores.terreno[4];
				        mapaResultado[fil-1][col+2] = sensores.terreno[5];
				        mapaResultado[fil][col+2] = sensores.terreno[6];
				        mapaResultado[fil+1][col+2] = sensores.terreno[7];
				        mapaResultado[fil+2][col+2] = sensores.terreno[8];
				        mapaResultado[fil-3][col+3] = sensores.terreno[9];
				        mapaResultado[fil-2][col+3] = sensores.terreno[10];
				        mapaResultado[fil-1][col+3] = sensores.terreno[11];
				        mapaResultado[fil][col+3] = sensores.terreno[12];
				        mapaResultado[fil+1][col+3] = sensores.terreno[13];
				        mapaResultado[fil+2][col+3] = sensores.terreno[14];
				        mapaResultado[fil+3][col+3] = sensores.terreno[15];
		          break;

		          case 3:
			          	mapaResultado[fil][col] = sensores.terreno[0];
				        mapaResultado[fil+1][col-1] = sensores.terreno[1];
				        mapaResultado[fil][col-1] = sensores.terreno[2];
				        mapaResultado[fil-1][col-1] = sensores.terreno[3];
				        mapaResultado[fil+2][col-2] = sensores.terreno[4];
				        mapaResultado[fil+1][col-2] = sensores.terreno[5];
				        mapaResultado[fil][col-2] = sensores.terreno[6];
				        mapaResultado[fil-1][col-2] = sensores.terreno[7];
				        mapaResultado[fil-2][col-2] = sensores.terreno[8];
				        mapaResultado[fil+3][col-3] = sensores.terreno[9];
				        mapaResultado[fil+2][col-3] = sensores.terreno[10];
				        mapaResultado[fil+1][col-3] = sensores.terreno[11];
				        mapaResultado[fil][col-3] = sensores.terreno[12];
				        mapaResultado[fil-1][col-3] = sensores.terreno[13];
				        mapaResultado[fil-2][col-3] = sensores.terreno[14];
				        mapaResultado[fil-3][col-3] = sensores.terreno[15];
			        break;

			    case 0:
			        mapaResultado[fil][col] = sensores.terreno[0];
			        mapaResultado[fil-1][col-1] = sensores.terreno[1];
			        mapaResultado[fil-1][col] = sensores.terreno[2];
			        mapaResultado[fil-1][col+1] = sensores.terreno[3];
			        mapaResultado[fil-2][col-2] = sensores.terreno[4];
			        mapaResultado[fil-2][col-1] = sensores.terreno[5];
			        mapaResultado[fil-2][col] = sensores.terreno[6];
			        mapaResultado[fil-2][col+1] = sensores.terreno[7];
			        mapaResultado[fil-2][col+2] = sensores.terreno[8];
			        mapaResultado[fil-3][col-3] = sensores.terreno[9];
			        mapaResultado[fil-3][col-2] = sensores.terreno[10];
			        mapaResultado[fil-3][col-1] = sensores.terreno[11];
			        mapaResultado[fil-3][col] = sensores.terreno[12];
			        mapaResultado[fil-3][col+1] = sensores.terreno[13];
			        mapaResultado[fil-3][col+2] = sensores.terreno[14];
			        mapaResultado[fil-3][col+3] = sensores.terreno[15];
		          break;

		          case 2:
			        mapaResultado[fil][col] = sensores.terreno[0];
			        mapaResultado[fil+1][col+1] = sensores.terreno[1];
			        mapaResultado[fil+1][col] = sensores.terreno[2];
			        mapaResultado[fil+1][col-1] = sensores.terreno[3];
			        mapaResultado[fil+2][col+2] = sensores.terreno[4];
			        mapaResultado[fil+2][col+1] = sensores.terreno[5];
			        mapaResultado[fil+2][col] = sensores.terreno[6];
			        mapaResultado[fil+2][col-1] = sensores.terreno[7];
			        mapaResultado[fil+2][col-2] = sensores.terreno[8];
			        mapaResultado[fil+3][col+3] = sensores.terreno[9];
			        mapaResultado[fil+3][col+2] = sensores.terreno[10];
			        mapaResultado[fil+3][col+1] = sensores.terreno[11];
			        mapaResultado[fil+3][col] = sensores.terreno[12];
			        mapaResultado[fil+3][col-1] = sensores.terreno[13];
			        mapaResultado[fil+3][col-2] = sensores.terreno[14];
			        mapaResultado[fil+3][col-3] = sensores.terreno[15];
		          break;

				}
				llega=true;
				accion=actIDLE;
			
			}else if(sensores.terreno[2]=='P' or sensores.terreno[2]=='M' or 
				sensores.terreno[2]=='D'){
				accion=actTURN_R;
				brujula= (brujula+1)%4;
			}else if(sensores.superficie[2]=='a'){
				accion=actIDLE;
			}else if(sensores.terreno[0]!='K'){
				accion=actFORWARD;
			}
		}else{


			switch(brujula){
					case 1:
						mapaResultado[fil][col] = sensores.terreno[0];
				        mapaResultado[fil-1][col+1] = sensores.terreno[1];
				        mapaResultado[fil][col+1] = sensores.terreno[2];
				        mapaResultado[fil+1][col+1] = sensores.terreno[3];
				        mapaResultado[fil-2][col+2] = sensores.terreno[4];
				        mapaResultado[fil-1][col+2] = sensores.terreno[5];
				        mapaResultado[fil][col+2] = sensores.terreno[6];
				        mapaResultado[fil+1][col+2] = sensores.terreno[7];
				        mapaResultado[fil+2][col+2] = sensores.terreno[8];
				        mapaResultado[fil-3][col+3] = sensores.terreno[9];
				        mapaResultado[fil-2][col+3] = sensores.terreno[10];
				        mapaResultado[fil-1][col+3] = sensores.terreno[11];
				        mapaResultado[fil][col+3] = sensores.terreno[12];
				        mapaResultado[fil+1][col+3] = sensores.terreno[13];
				        mapaResultado[fil+2][col+3] = sensores.terreno[14];
				        mapaResultado[fil+3][col+3] = sensores.terreno[15];
		          break;

		          case 3:
			          	mapaResultado[fil][col] = sensores.terreno[0];
				        mapaResultado[fil+1][col-1] = sensores.terreno[1];
				        mapaResultado[fil][col-1] = sensores.terreno[2];
				        mapaResultado[fil-1][col-1] = sensores.terreno[3];
				        mapaResultado[fil+2][col-2] = sensores.terreno[4];
				        mapaResultado[fil+1][col-2] = sensores.terreno[5];
				        mapaResultado[fil][col-2] = sensores.terreno[6];
				        mapaResultado[fil-1][col-2] = sensores.terreno[7];
				        mapaResultado[fil-2][col-2] = sensores.terreno[8];
				        mapaResultado[fil+3][col-3] = sensores.terreno[9];
				        mapaResultado[fil+2][col-3] = sensores.terreno[10];
				        mapaResultado[fil+1][col-3] = sensores.terreno[11];
				        mapaResultado[fil][col-3] = sensores.terreno[12];
				        mapaResultado[fil-1][col-3] = sensores.terreno[13];
				        mapaResultado[fil-2][col-3] = sensores.terreno[14];
				        mapaResultado[fil-3][col-3] = sensores.terreno[15];
			        break;

			    case 0:
			        mapaResultado[fil][col] = sensores.terreno[0];
			        mapaResultado[fil-1][col-1] = sensores.terreno[1];
			        mapaResultado[fil-1][col] = sensores.terreno[2];
			        mapaResultado[fil-1][col+1] = sensores.terreno[3];
			        mapaResultado[fil-2][col-2] = sensores.terreno[4];
			        mapaResultado[fil-2][col-1] = sensores.terreno[5];
			        mapaResultado[fil-2][col] = sensores.terreno[6];
			        mapaResultado[fil-2][col+1] = sensores.terreno[7];
			        mapaResultado[fil-2][col+2] = sensores.terreno[8];
			        mapaResultado[fil-3][col-3] = sensores.terreno[9];
			        mapaResultado[fil-3][col-2] = sensores.terreno[10];
			        mapaResultado[fil-3][col-1] = sensores.terreno[11];
			        mapaResultado[fil-3][col] = sensores.terreno[12];
			        mapaResultado[fil-3][col+1] = sensores.terreno[13];
			        mapaResultado[fil-3][col+2] = sensores.terreno[14];
			        mapaResultado[fil-3][col+3] = sensores.terreno[15];
		          break;

		          case 2:
			        mapaResultado[fil][col] = sensores.terreno[0];
			        mapaResultado[fil+1][col+1] = sensores.terreno[1];
			        mapaResultado[fil+1][col] = sensores.terreno[2];
			        mapaResultado[fil+1][col-1] = sensores.terreno[3];
			        mapaResultado[fil+2][col+2] = sensores.terreno[4];
			        mapaResultado[fil+2][col+1] = sensores.terreno[5];
			        mapaResultado[fil+2][col] = sensores.terreno[6];
			        mapaResultado[fil+2][col-1] = sensores.terreno[7];
			        mapaResultado[fil+2][col-2] = sensores.terreno[8];
			        mapaResultado[fil+3][col+3] = sensores.terreno[9];
			        mapaResultado[fil+3][col+2] = sensores.terreno[10];
			        mapaResultado[fil+3][col+1] = sensores.terreno[11];
			        mapaResultado[fil+3][col] = sensores.terreno[12];
			        mapaResultado[fil+3][col-1] = sensores.terreno[13];
			        mapaResultado[fil+3][col-2] = sensores.terreno[14];
			        mapaResultado[fil+3][col-3] = sensores.terreno[15];
		          break;

				}

			if(actual.columna==destino.columna && actual.fila==destino.fila){
				destino.fila = sensores.destinoF;
				destino.columna = sensores.destinoC;
			}

			list<Action> aux1=plan;

			bool hay_plan = pathFinding (sensores.nivel, actual, destino, plan);

			if(count1>=1)
				if(aux1!=plan)
					count1=0;

			if(hay_plan && count1<plan.size()){
				list<Action>::iterator it=plan.begin();
				advance(it,count1);
				count1++;
				accion=*it;
				switch (accion){
					case actTURN_R: brujula= (brujula+1)%4; break;
					case actTURN_L: brujula= (brujula+3)%4;  break;
				}
			}
			if(accion==actFORWARD){
				if(sensores.terreno[2]=='P' or sensores.terreno[2]=='M' or 
				sensores.terreno[2]=='D')
					hay_plan=false;
				if(sensores.superficie[2]=='a'){
					hay_plan=false;
				}
				if(hay_plan && sensores.superficie[2]!='a'){
					if(brujula==0)
						fil-=1;
					if(brujula==1)
						col+=1;
					if(brujula==2)
						fil+=1;
					if(brujula==3)
						col-=1;
					actual.fila = fil;
					actual.columna = col;
					actual.orientacion = brujula;
				}
			}
			if(!hay_plan){
				accion=actTURN_R;
				brujula= (brujula+1)%4;
			}
		}
	}

  return accion;
}




// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			      return pathFinding_Profundidad(origen,destino,plan);
						break;
		case 2: cout << "Busqueda en Anchura\n";
			      return pathFinding_Anchura(origen,destino,plan);
						break;
		case 3: cout << "Busqueda Costo Uniforme\n";
				  return pathFinding_Costo(origen, destino, plan);
						break;
		case 4: cout << "Busqueda para el reto\n";
					return pathFinding_Costo(origen, destino, plan);
						break;
	}
	cout << "Comportamiento sin implementar\n";
	return false;
}


//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el código en carácter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M' or casilla =='D')
		return true;
	else
	  return false;
}


// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}


// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	stack<nodo> pila;				// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);

  while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			pila.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			pila.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				pila.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

bool ComportamientoJugador::anchura_Recursivo(list<nodo> &rec, const estado &destino, nodo &current, set<estado,ComparaEstados> &generados){

	list<nodo> rec2;
	rec2.resize(rec.size());
	rec2=rec;
	rec.clear();
	rec.resize(0);
	for(list<nodo>::iterator it=rec2.begin(); it!=rec2.end(); it++){
		if((*it).st.fila == destino.fila and (*it).st.columna == destino.columna){
			current=*it;
			return true;
		}

		generados.insert((*it).st);
		nodo hijoTurnR = *it;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
			if (generados.find(hijoTurnR.st) == generados.end() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){
				hijoTurnR.secuencia=(*it).secuencia;
				hijoTurnR.secuencia.push_back(actTURN_R);
				rec.push_back(hijoTurnR);
			}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = *it;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){
			hijoTurnL.secuencia=(*it).secuencia;
			hijoTurnL.secuencia.push_back(actTURN_L);
			rec.push_back(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = *it;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia=(*it).secuencia;
				hijoForward.secuencia.push_back(actFORWARD);
				rec.push_back(hijoForward);
			}
		}
	}
	if(rec.empty())
		return false;
	anchura_Recursivo(rec, destino, current, generados);

}

bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	stack<nodo> pila;				// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);
	nodo current2=current;
	list<nodo> rec;
	rec.push_back(current);
	anchura_Recursivo(rec, destino, current, generados);


  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

////////////////////////////////////////////////////////////////////////
//T arenoso 2
//B bosque 5
//Resto 1
//A agua 10

void ComportamientoJugador::encuentra_Minimo(list<costo> &costos, list<costo>::iterator &min){
	list<costo>::iterator it;
	int minimo=3000;
	
	for(it=costos.begin(); it!=costos.end(); it++){
		if((*it).valor<minimo){
			minimo=(*it).valor;
			min=it;
		}
	}
}



bool ComportamientoJugador::pathFinding_Costo(const estado &origen, const estado &destino, list<Action> &plan){
	
		//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	list<costo> c;				// Lista de Abiertos
	set<estado,ComparaEstados> generados;

  	costo current;
	current.n.st = origen;
	current.n.secuencia.empty();
	current.valor=0;

	c.push_back(current);
	list<costo>::iterator cur=c.begin();
	costo hijoTurnR;
	costo hijoTurnL;
	costo hijoForward;
	int contador=0;
	
	while((*cur).n.st.fila!=destino.fila or (*cur).n.st.columna!=destino.columna){
		
		generados.insert((*cur).n.st);

		hijoTurnR.n=(*cur).n;
		hijoTurnR.n.st.orientacion = (hijoTurnR.n.st.orientacion+1)%4;
		if(generados.find(hijoTurnR.n.st) == generados.end()){
			hijoTurnR.n.secuencia.push_back(actTURN_R);
			hijoTurnR.valor=(*cur).valor;
			hijoTurnR.valor+=1;
			c.push_back(hijoTurnR);
		}
		

		hijoTurnL.n=(*cur).n;
		hijoTurnL.n.st.orientacion = (hijoTurnL.n.st.orientacion+3)%4;
		if(generados.find(hijoTurnL.n.st) == generados.end()){
			hijoTurnL.n.secuencia.push_back(actTURN_L);
			hijoTurnL.valor=(*cur).valor+1;
			hijoTurnL.valor+=1;
			c.push_back(hijoTurnL);
		}

		
		hijoForward.n=(*cur).n;
		if(!HayObstaculoDelante(hijoForward.n.st)){
			if(generados.find(hijoForward.n.st) == generados.end()){
				hijoForward.n.secuencia.push_back(actFORWARD);
				hijoForward.valor=(*cur).valor;
				
				if(mapaResultado[hijoForward.n.st.fila][hijoForward.n.st.columna]=='T'){
					hijoForward.valor+=2;
				}else if(mapaResultado[hijoForward.n.st.fila][hijoForward.n.st.columna]=='B'){
					hijoForward.valor+=5;
				}else if(mapaResultado[hijoForward.n.st.fila][hijoForward.n.st.columna]=='A'){
					hijoForward.valor+=10;
				}else{
					hijoForward.valor+=1;
				}

				c.push_back(hijoForward);
			}
		}
		c.erase(cur);
		encuentra_Minimo(c, cur);
		

	}
	
	cout << "Terminada la busqueda\n";

	if ((*cur).n.st.fila == destino.fila and (*cur).n.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = (*cur).n.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		cout << "Coste del plan: " << (*cur).valor << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;


}

/////////////////////////////////////////////////

// Sacar por la términal la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}



void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}


// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}



int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
