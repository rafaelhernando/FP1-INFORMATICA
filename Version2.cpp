#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#define inFile "Tablero.txt";
using namespace std;


const int MODO_DEBUG = true;

const int TURNOS_POSADA = 1;
const int TURNOS_CARCEL = 2;
const int TURNOS_POZO = 3;

const int CENTINELA = 0;

const int CASILLA_INICIAL = 1;
const int CASILLA_META = 63;

const int RETROCESO_LABERINTO = 12;
// n�mero de jugadores actual
const int NUM_JUGADORES = 2;
// m�ximo n�mero de jugadores
const int MAX_JUGADORES = 4;
// n�mero de filas a dibujar
const int NUM_FILAS_A_DIBUJAR = 3;

typedef enum { NORMAL, OCA, PUENTE1, PUENTE2, POZO, POSADA, LABERINTO, DADO1, DADO2, CARCEL, CALAVERA } tCasilla;

typedef tCasilla tTablero[CASILLA_META];

typedef int tJugadores[NUM_JUGADORES];

//-------------------------------------------------------------------------
// Subprogramas para pintar el tablero o mostrar informaci�n

void pintaTablero(const tTablero tablero, const tJugadores casillasJ);
void pintaNumCasilla(int fila, int casillasPorFila);
void pintaBorde(int casillasPorFila);
void pintaTipoCasilla(const tTablero tablero, int fila, int casillasPorFila);
void pintaJugadores(const tJugadores casillasJ, int fila, int casillasPorFila);
string casillaAstring(tCasilla casilla);
//---------------------------------------------------------------------------

void iniciaTablero(tTablero tablero);
bool cargaTablero(tTablero tablero);
int main() {
    tTablero tablero;
    tJugadores casillasJ;
    iniciaTablero(tablero);
    cargaTablero(tablero);
    pintaTablero(tablero, casillasJ);




    return 0;
}



string casillaAstring(tCasilla casilla) {
    string cadena;
    switch (casilla) {
    case NORMAL:
        cadena = " ";
        break;
    case OCA:
        cadena = "OCA";
        break;
    case DADO1:
    case DADO2:
        cadena = "DADO";
        break;
    case PUENTE1:
    case PUENTE2:
        cadena = "PNTE";
        break;
    case POSADA:
        cadena = "PSDA";
        break;
    case CALAVERA:
        cadena = "MUER";
        break;
    case LABERINTO:
        cadena = "LBRN";
        break;
    case POZO:
        cadena = "POZO";
        break;
    case CARCEL:
        cadena = "CRCL";
        break;
    }
    return cadena;
}

void pintaTablero(const tTablero tablero, const tJugadores casillasJ) {


    int casillasPorFila = CASILLA_META / NUM_FILAS_A_DIBUJAR;
    cout << endl;
    for (int fila = 0; fila < NUM_FILAS_A_DIBUJAR; fila++) {
        pintaBorde(casillasPorFila);
        pintaNumCasilla(fila, casillasPorFila);
        pintaTipoCasilla(tablero, fila, casillasPorFila);
        pintaJugadores(casillasJ, fila, casillasPorFila);
    }
    pintaBorde(casillasPorFila);
    cout << endl;
}


void pintaBorde(int casillasPorFila) {

    for (int i = 1; i <= casillasPorFila; i++)
        cout << "|====";

    cout << "|" << endl;

}


void pintaNumCasilla(int fila, int casillasPorFila) {

    for (int i = 1; i <= casillasPorFila; i++)
        cout << "| " << setw(2) << setfill('0') << i + fila * casillasPorFila << " ";

    cout << "|" << endl;

}


void pintaTipoCasilla(const tTablero tablero, int fila, int casillasPorFila) {

    for (int i = 1; i <= casillasPorFila; i++)
        cout << "|" << setw(4) << setfill(' ') << casillaAstring(tablero[i - 1 + fila * casillasPorFila]);

    cout << "|" << endl;

}

void pintaJugadores(const tJugadores casillasJ, int fila, int casillasPorFila) {
    int casilla;

    int blancos = MAX_JUGADORES - NUM_JUGADORES;
    string b = "";
    for (int i = 1; i < blancos; i++) b = b + " ";
    cout << "|";
    for (int i = 1; i <= casillasPorFila; i++) {
        casilla = i - 1 + fila * casillasPorFila;
        for (int jug = 0; jug < NUM_JUGADORES; jug++) {
            if (casillasJ[jug] == casilla)
                cout << jug + 1;
            else
                cout << " ";
        }
        cout << b;
        cout << "|";
    }
    cout << endl;

}
//inicia el valor de las casillas a normal;
void iniciaTablero(tTablero tablero) {

    for (int i = 0; i <= CASILLA_META - 1; i++) {
        tablero[i] = NORMAL;

        if (i == CASILLA_META - 1) { tablero[i] = OCA; }
    }


}
// lee el fichero de las casillas especiales.
//almacena las casillas en el array Ttablero.
bool cargaTablero(tTablero tablero) {
    bool carga;
    int i;
    char aux;
    string nombreF;
    string casillaESP;
    int contador = 0;
    ifstream fichero;
   // cout << "Introduce el nombre del fichero que contiene el tablero: ";
   // cin >> nombreF;
    fichero.open("tablero.txt");
    if (fichero.is_open()) {
        carga = true;
        fichero >> i;
        while (i != 0) {
            fichero.get(aux);
            getline(fichero, casillaESP);
            if (casillaESP == "OCA") {
                tablero[i - 1] = OCA;
            }
            else if (casillaESP == "PUENTE1") {
                tablero[i - 1] = PUENTE1;
            }
            else if (casillaESP == "PUENTE2") {
                tablero[i - 1] = PUENTE2;
            }
            else if (casillaESP == "DADO1") {
                tablero[i - 1] = DADO1;
            }
            else if (casillaESP == "DADO2") {
                tablero[i - 1] = DADO2;
            }
            else if (casillaESP == "NORMAL") {
                tablero[i - 1] = NORMAL;
            }
            else if (casillaESP == "POZO") {
                tablero[i - 1] = POZO;
            }
            else if (casillaESP == "LABERINTO") {
                tablero[i - 1] = LABERINTO;
            }
            else if (casillaESP == "CARCEL") {
                tablero[i - 1] = CARCEL;
            }
            else if (casillaESP == "CALAVERA") {
                tablero[i - 1] = CALAVERA;
            }
            fichero >> i;
        }
    }
    else {
        cout << "error";
        carga = false;
    }
    fichero.close();
    return carga;
}

bool esCasillaPremio(const tTablero tablero, int casilla) {
    bool premio;
    for (int i = 0; i < CASILLA_META; i++) {
        if (tablero[i] == OCA || tablero[i] == PUENTE1 || tablero[i] == PUENTE2 || tablero[i] == DADO1 || tablero[i] == DADO2) {
            premio = true;
        }
        else { premio = false; }
    }

    return premio;
}
void efectoTirada(const tTablero tablero, int& casillaJ, int& penalizacionJ) {
    //SWITCH calcula el caso de avanze retroceso o penalización de la casillaJ
    tCasilla casilla;
    switch(casilla){
    case OCA:
        cout << "Estas en la casilla Oca: " << casillaJ << endl;
        casillaJ = saltaCasilla(tablero, casillaJ);
        cout << "Saltas a la casilla Oca: " << casillaJ << endl;
        if (casillaJ!=CASILLA_META) { cout << "Y VUELVES A TIRAR" << endl; }
        break;
    case DADO1:
        cout << "Estas en la casilla Dado: " << casillaJ << endl;
        casillaJ = saltaCasilla(tablero, casillaJ);
        cout << "Saltas a la casilla Dado: " << casillaJ << endl;
        if (casillaJ != CASILLA_META) { cout << "Y VUELVES A TIRAR" << endl; }
        break;
    case DADO2:
        cout << "Estas en la casilla Dado: " << casillaJ << endl;
        casillaJ = saltaCasilla(tablero, casillaJ);
        cout << "Saltas a la casilla Dado: " << casillaJ << endl;
        if (casillaJ != CASILLA_META) { cout << "Y VUELVES A TIRAR" << endl; }
        break;
    case PUENTE1:
        cout << "Estas en la casilla Puente: " << casillaJ << endl;
        casillaJ = saltaCasilla(tablero, casillaJ);
        cout << "Saltas a la casilla Puente: " << casillaJ << endl;
        if (casillaJ != CASILLA_META) { cout << "Y VUELVES A TIRAR" << endl; }
        break;
    case PUENTE2:
        cout << "Estas en la casilla Puente: " << casillaJ << endl;
        casillaJ = saltaCasilla(tablero, casillaJ);
        cout << "Saltas a la casilla Puente: " << casillaJ << endl;
        if (casillaJ != CASILLA_META) { cout << "Y VUELVES A TIRAR" << endl; }
        break;
    case POSADA:
        cout << "HAS CAIDO EN LA POSADA." << endl;
        cout << "PIERDES " << TURNOS_POSADA << " TURNOS" << endl;
        penalizacionJ = TURNOS_POSADA;
        break;
    case CARCEL:
        cout << "HAS CAIDO EN LA POSADA." << endl;
        cout << "PIERDES " << TURNOS_CARCEL << " TURNOS" << endl;
        penalizacionJ = TURNOS_CARCEL;
        break;
    case POZO:
        cout << "HAS CAIDO EN LA POSADA." << endl;
        cout << "PIERDES " << TURNOS_POZO << " TURNOS" << endl;
        penalizacionJ = TURNOS_POZO;
        break;
    case CALAVERA:
        cout << "Estas en la casilla Calavera: " << casillaJ << endl;
        casillaJ = saltaCasilla(tablero, casillaJ);
        cout << "Retrocedes al inicio: " << casillaJ << endl;
        break;
    case LABERINTO:
        cout << "Estas en la casilla Laberinto: " << casillaJ << endl;
        casillaJ = saltaCasilla(tablero, casillaJ);
        cout << "Retrocedes doce casillas: " << casillaJ << endl;
        break;

    
    
    }

}
//desplaza a la casilla correspondiente
int saltaCasilla(const tTablero tablero, int casillaActual) {
    int i = casillaActual + 1;
    if (tablero[casillaActual] == OCA) {
        
        while (i < CASILLA_META - 1 && tablero[i] != OCA && tablero[i]==DADO1 && tablero[i] == DADO2 && tablero[i] == PUENTE1 && tablero[i] == PUENTE2 && tablero[i] == CALAVERA && tablero[i] == POSADA && tablero[i] == POZO && tablero[i] == LABERINTO
            && tablero[i] == CARCEL) {
            i++;
        }
    
    }
    else if (tablero[casillaActual] == DADO1) {
        casillaActual = tablero[DADO2];
    }
    else if (tablero[casillaActual] == DADO2) {
        casillaActual = tablero[DADO1];
    }
    else if (tablero[casillaActual] == PUENTE1) {
        casillaActual = tablero[PUENTE2];
    }
    else if (tablero[casillaActual] == PUENTE2) {
        casillaActual = tablero[PUENTE1];
    }
    else if (tablero[casillaActual] == CALAVERA) {
        casillaActual = 1;
    }
    else if (tablero[casillaActual] == LABERINTO) {
        casillaActual = casillaActual-RETROCESO_LABERINTO;
    }
    
}

void tirada(const tTablero tablero, int& casillaActual, int& penalizacion) {

    int dado = 0;
    cout << endl;
    if (MODO_DEBUG==true) {
        cout << "Introduce valor del dado:";
        cin >> dado;
        while (dado > 6 || dado < 1) {
            cout << "ERROR: el numero debe pertenecer al intervalo [1,6]." << endl;
            cout << "Elige otro numero:";
            cin >> dado;
        }
    }
    else {

        dado = rand() % 6 + 1;
        cout << "Valor del dado: " << dado << endl;
    }
    casillaActual = casillaActual + dado;
    if (casillaActual != CASILLA_META) { efectoTirada(tablero, casillaActual, penalizacion); }

}
void iniciaJugadores(tJugadores casillasJ, tJugadores penalizacionesJ) {
    for (int i = 0;i < NUM_JUGADORES;i++) { casillasJ[i] = 0; }

    for (int i = 0;i < NUM_JUGADORES;i++) { penalizacionesJ[i] = 0; }


}
int quienEmpieza() {
    int jugador = 1 + rand() % NUM_JUGADORES;
    cout << "Empieza el jugador " << jugador << endl;

    return jugador;
}
int partida(const tTablero tablero) {
    tJugadores casillasJug, penalizacionesJug;
    iniciaJugadores( 0, 0);
    pintaTablero(tablero,casillasJug);
    quienEmpieza();
    while (!CASILLA_META) {


   }

}

