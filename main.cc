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
          {
            nodo **q = &(*posPersonaje)->up;

            nodo **up = &(*posVista)->up;
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
          {
            nodo **q = &(*posPersonaje)->left;

            nodo **left = &(*posVista)->left;
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
          {
            nodo **q = &(*posPersonaje)->down;
            nodo **down = &(*posVista)->down;
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
          {
            nodo **q = &(*posPersonaje)->right;
            nodo **right = &(*posVista)->right;
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
          {
            DestruirTierra(posVista);
            break;
          }
        case 'e':
          {
            crearTierra((*posPersonaje), (*posVista));
            break;
          }

      }
    }

    cout << "\n\n\n";
    cout << "\n";
    return EXIT_SUCCESS;
}
