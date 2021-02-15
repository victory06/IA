#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}




double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar

void NumFichasEnLinea(const Environment &estado, int jugador, int &numdos, int &numtres){

    for(int fila=0; fila<7; fila++){
    	for(int columna=0; columna<7; columna++){
		    //En la misma Fila
		    if (columna<5){
		      if ((estado.See_Casilla(fila,columna)%3)   == (estado.See_Casilla(fila,columna+1)%3) and
		          (estado.See_Casilla(fila,columna+1)%3) == (estado.See_Casilla(fila,columna+2)%3)
		          and (estado.See_Casilla(fila,columna+1)%3) == (jugador)){
		          //cout << "En la misma fila\n";
		        numtres++;
		    	numdos-=2;
		      }
		    }
		    //En la misma columna
		    if (fila<5){
		      if ((estado.See_Casilla(fila,columna)%3)   == (estado.See_Casilla(fila+1,columna)%3) and
		          (estado.See_Casilla(fila+1,columna)%3) == (estado.See_Casilla(fila+2,columna)%3)
		          and (estado.See_Casilla(fila+1,columna)%3) ==jugador){
		          //cout << "En la misma columna\n";
				numtres++;
				numdos-=2;
		      }
		    }
		    //En la diagonal hacia arriba
		    if (fila<5 and columna<5){
		      if ((estado.See_Casilla(fila,columna)%3)     == (estado.See_Casilla(fila+1,columna+1)%3) and
		          (estado.See_Casilla(fila+1,columna+1)%3) == (estado.See_Casilla(fila+2,columna+2)%3)
		          and (estado.See_Casilla(fila+1,columna+1)%3) ==jugador){
		          //cout << "En la diagonal principal\n";
				numtres++;
				numdos-=2;
		      }
		    }

		    //En la diagonal hacia abajo
		    if (fila>1 and columna<5){
		      if ((estado.See_Casilla(fila,columna)%3)   == (estado.See_Casilla(fila-1,columna+1)%3) and
		          (estado.See_Casilla(fila-1,columna+1)%3) == (estado.See_Casilla(fila-2,columna+2)%3)
		          and (estado.See_Casilla(fila-1,columna+1)%3) ==jugador){
		          //cout << "En la diagonal secundaria\n";
				numtres++;
				numdos-=2;
		      }
		    }
		}
	}

	for(int fila=0; fila<7; fila++){
    	for(int columna=0; columna<7; columna++){
		    //En la misma Fila
		    if (columna<6){
		      if ((estado.See_Casilla(fila,columna)%3)   == (estado.See_Casilla(fila,columna+1)%3)
		          and (estado.See_Casilla(fila,columna+1)%3) == (jugador)){
		          //cout << "En la misma fila\n";
		        numdos++;
		      }
		    }
		    //En la misma columna
		    if (fila<6){
		      if ((estado.See_Casilla(fila,columna)%3)   == (estado.See_Casilla(fila+1,columna)%3)
		          and (estado.See_Casilla(fila+1,columna)%3) ==jugador){
		          //cout << "En la misma columna\n";
				numdos++;
		      }
		    }
		    //En la diagonal hacia arriba
		    if (fila<6 and columna<6){
		      if ((estado.See_Casilla(fila,columna)%3)     == (estado.See_Casilla(fila+1,columna+1)%3)
		          and (estado.See_Casilla(fila+1,columna+1)%3) ==jugador){
		          //cout << "En la diagonal principal\n";
				numdos++;
		      }
		    }

		    //En la diagonal hacia abajo
		    if (fila>0 and columna<6){
		      if ((estado.See_Casilla(fila,columna)%3)   == (estado.See_Casilla(fila-1,columna+1)%3)
		          and (estado.See_Casilla(fila-1,columna+1)%3) ==jugador){
		          //cout << "En la diagonal secundaria\n";
				numdos++;
		      }
		    }
		}
	}


}



// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){
  int lineaCuatro=estado.RevisarTablero();
  if(lineaCuatro==jugador)
    return masinf;
  else if(lineaCuatro==(jugador%2)+1)
    return menosinf;
  int numtres=0, numdos=0, numdos_p=0, numtres_p=0; //Los _p son el otro jugador
  NumFichasEnLinea(estado, jugador, numdos, numtres);
  NumFichasEnLinea(estado, (jugador%2)+1, numdos_p, numtres_p);
  int valor3=-8, valor2=-2, valor3_p=8, valor2_p=2;
  return numdos*valor2+numtres*valor3+numtres_p*valor3_p+numdos_p*valor2_p;

}


double Poda_AlfaBeta(bool maximizingPlayer, const Environment &env, int jugador_, int depth , int profmax, Environment::ActionType &accion, double alpha, double beta){
  
  if(depth==profmax){
    return Valoracion(env,jugador_);
  }

  Environment *hijos;
  hijos=new Environment[8];
  int num_moves=env.GenerateAllMoves(hijos);
  //cout << "hijos: " << hijos[7].Last_Action(jugador_) << endl;
  
  double *valores0;
  valores0=new double[num_moves];
  double best2;
  if(maximizingPlayer){
    double best=menosinf;
    double val;
    for(int i=0; i<num_moves; i++){
      if(hijos[i].RevisarTablero()==0)
        val=Poda_AlfaBeta(false, hijos[i],(jugador_%2)+1, depth+1, profmax, accion, alpha, beta);
      else if(hijos[i].RevisarTablero()==jugador_)
        val=masinf;
      else
        val=menosinf;
        if(depth==0){
          valores0[i]=val;
        }
        best=max(best, val);
        alpha=max(alpha, best);
        best2=best;
        
        if(beta<=alpha){
          break;
        }
    }
    if(depth==0){
      bool encontrado=false;
      for(int j=0; j<num_moves && !encontrado; j++){
        if(valores0[j]==best2){
          encontrado=true;
          accion=static_cast<Environment::ActionType>(hijos[j].Last_Action(jugador_));
        }
      }
    }
    delete [] hijos;
  	delete [] valores0;
    return best;
  }else{
    double best=masinf;
    double val;
    for(int i=0; i<num_moves; i++){
      if(hijos[i].RevisarTablero()==0)
        val=Poda_AlfaBeta(true, hijos[i],(jugador_%2)+1, depth+1, profmax, accion, alpha, beta);
      else if(hijos[i].RevisarTablero()==jugador_)
        val=menosinf;
      else
        val=masinf;
      best=min(best,val);
      beta=min(beta,best);

       if(beta<=alpha){
        break;
      }
    }
    delete [] hijos;
  	delete [] valores0;
    return best;
  }


}


// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}






// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acción que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    //double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha=menosinf, beta=masinf; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual

    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;

    /*
    //--------------------- COMENTAR Desde aqui
    cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);

         }

    //--------------------- COMENTAR Hasta aqui
    */

    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------



    Environment *hijos;
 	hijos=new Environment[8];
  	int num_moves=actual_.GenerateAllMoves(hijos);
  	bool ganadora=false;
  	for(int i=0; i<num_moves && !ganadora; i++){
  		if(hijos[i].RevisarTablero()==jugador_){
  			ganadora=true;
  			accion=static_cast<Environment::ActionType>(hijos[i].Last_Action(jugador_));
  		}
  	}



    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    if(!ganadora){
	    double valor = Poda_AlfaBeta(true, actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
	    cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;
	}
	delete [] hijos;


    return accion;
}


