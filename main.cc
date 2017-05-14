#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "nodos.h"
#include <iostream>

#define MAXDEPTH 100

using namespace std;
int main(int argc, char **argv){

    int n = 5;
    int m = 10;
    nodo *r = crear_nodo(0, 0, 1, n, m);
    pos *lastPos = crear_pos(0, 0);
    pos *lastVista = crear_pos(0, 1);

    crear_mapa(&r, n, m);
    designarDireccionesIniciales(&r, n, m);
    char c;
    bool play = true;
    while (play) {
      nodo **posPersonaje = buscar_nodo_puntero_tipo(&r, 1);
      lastPos->x = (*posPersonaje)->x;
      lastPos->y = (*posPersonaje)->y;

      nodo **posVista = buscar_nodo_puntero_tipo(&r, 2);
      lastVista->x = (*posVista)->x;
      lastVista->y = (*posVista)->y;

      imprimir_mapa(&r, n, m);
      cout << endl << "Ingrese comando: ";
      cin >> c;
      switch (c) {
        case 'w':
          if (esCoordenadaValida((*posVista)->x - 1, n)) {
            nodo **q = buscar_nodo_puntero_posicion(&r, (*posPersonaje)->x - 1, (*posPersonaje)->y);
            nodo **up = (buscar_nodo_puntero_posicion(&r, (*posVista)->x - 1, (*posVista)->y));
            if (((*up) != NULL) && ((*q) != NULL)) {
              if (((*q)->x == lastVista->x) && ((*q)->y == lastVista->y)) {
                if ((*posPersonaje)->destroyed) {
                (*posPersonaje)->val = 3;
                } else {
                  (*posPersonaje)->val = 0;
                }
                (*posVista)->val = 1;
                (*up)->val = 2;
              } else {
                if ((*posVista)->destroyed) {
                  (*posVista)->val = 3;
                } else {
                  (*posVista)->val = 0;
                }
                (*q)->val = 2;
              }
            }
          }
          break;
        case 'a':
          if (esCoordenadaValida((*posVista)->y - 1, m)) {
            nodo **q = buscar_nodo_puntero_posicion(&r, (*posPersonaje)->x, (*posPersonaje)->y - 1);
            nodo **left = (buscar_nodo_puntero_posicion(&r, (*posVista)->x, (*posVista)->y - 1));
            if ((*left) != NULL) {
              if (((*q)->x == lastVista->x) && ((*q)->y == lastVista->y)) {
                if ((*posPersonaje)->destroyed) {
                (*posPersonaje)->val = 3;
                } else {
                  (*posPersonaje)->val = 0;
                }
                (*posVista)->val = 1;
                (*left)->val = 2;
              } else {
                if ((*posVista)->destroyed) {
                  (*posVista)->val = 3;
                } else {
                (*posVista)->val = 0;
                }
                (*q)->val = 2;
              }
            }

          }
          break;
        case 's':
          if (esCoordenadaValida((*posVista)->x + 1, n)) {
            nodo **q = buscar_nodo_puntero_posicion(&r, (*posPersonaje)->x + 1, (*posPersonaje)->y);
            nodo **down = (buscar_nodo_puntero_posicion(&r, (*posVista)->x + 1, (*posVista)->y));
            if ((*down) != NULL) {
              if (((*q)->x == lastVista->x) && ((*q)->y == lastVista->y)) {
                if ((*posPersonaje)->destroyed) {
                (*posPersonaje)->val = 3;
                } else {
                  (*posPersonaje)->val = 0;
                }
                (*posVista)->val = 1;
                (*down)->val = 2;
              } else {
                if ((*posVista)->destroyed) {
                  (*posVista)->val = 3;
                } else {
                (*posVista)->val = 0;
                }
                (*q)->val = 2;
              }
            }
          }
          break;
        case 'd':
          if (esCoordenadaValida((*posVista)->y + 1, m)) {
            nodo **q = buscar_nodo_puntero_posicion(&r, (*posPersonaje)->x, (*posPersonaje)->y + 1);
            nodo **right = (buscar_nodo_puntero_posicion(&r, (*posVista)->x, (*posVista)->y + 1));
            if ((*right) != NULL) {
              if (((*q)->x == lastVista->x) && ((*q)->y == lastVista->y)) {
                if ((*posPersonaje)->destroyed) {
                (*posPersonaje)->val = 3;
                } else {
                  (*posPersonaje)->val = 0;
                }
                (*posVista)->val = 1;
                (*right)->val = 2;
              } else {
                if ((*posVista)->destroyed) {
                  (*posVista)->val = 3;
                } else {
                (*posVista)->val = 0;
                }
                (*q)->val = 2;
              }
            }
          }
          break;
        case 'q':

          //cortar conexion con up
          if ((*posVista)->up != NULL) {
            (*posVista)->up->down = NULL;
            (*posVista)->up = NULL;
          }
          //cortar conexion con down
          if ((*posVista)->down != NULL) {
            (*posVista)->down->up = NULL;
            (*posVista)->down = NULL;
          }

          //cortar conexion con left
          if ((*posVista)->left != NULL) {
          (*posVista)->left->right = NULL;
          (*posVista)->left = NULL;
          }
          //cortar conexion con right
          if ((*posVista)->right != NULL) {
          (*posVista)->right->left = NULL;
          (*posVista)->right = NULL;
          }

          (*posVista)->destroyed = true;

          break;
        case 'e':
          crearTierra((*posPersonaje), (*posVista));
          (*posVista)->destroyed = false;
          break;
      }
    }

    cout << "\n\n\n";
    cout << "\n";
    return EXIT_SUCCESS;
}
