#ifndef NODOS_H
#define NODOS_H

#include <iostream>


typedef struct nodo{
    int x;
    int y;
    int val;
    bool destroyed;
    struct nodo *up;
    bool up_tierra;
    struct nodo *down;
    bool down_tierra;
    struct nodo *right;
    bool right_tierra;
    struct nodo *left;
    bool left_tierra;
    struct nodo *next;
}nodo;

nodo* crear_nodo(int x, int y, int val);
void crear_mapa(nodo **r, int n, int m);
nodo** buscar_nodo_puntero_posicion(nodo **r, int x, int y);
nodo** buscar_nodo_puntero_tipo(nodo **r, int val);
bool esCoordenadaInterior(int n, int max);
void designarDireccionesIniciales(nodo **r, int n, int m);
void destruirTierra(nodo **posVista);
void mover(nodo **posPersonaje, nodo **posVista, char direction);
void crearTierra(nodo *posPersonaje, nodo *posVista);
void imprimir_mapa(nodo **r, int n, int m);
void recorrer(nodo *r);

using namespace std;

nodo* crear_nodo(int x, int y, int val) {
  nodo *q = (nodo*)malloc(sizeof(nodo));
  q->x = x;
  q->y = y;
  q->val = val;
  q->destroyed = false;
  q->next = NULL;
  q->up = NULL;
  q->down = NULL;
  q->left = NULL;
  q->right = NULL;
  q->up_tierra = true;
  q->down_tierra = true;
  q->left_tierra = true;
  q->right_tierra = true;

  return q;
}

void crear_mapa(nodo **r, int n, int m) {
  nodo *p = (*r);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (((i == 0) && (j == 1))) {
        p->next = crear_nodo(i, j, 2);
        p = p->next;
      } else if (!((i == 0) && (i == j))) {
        p->next = crear_nodo(i, j, 0);
        p = p->next;
      }
    }
  }

  designarDireccionesIniciales(r, n, m);
}

nodo** buscar_nodo_puntero_posicion(nodo **r, int x, int y) {
  if (((*r)->x == x) && ((*r)->y == y)) {
    return (r);
  } else {
    if ((*r)->next != NULL) {
      return buscar_nodo_puntero_posicion(&(*r)->next, x, y);
    } else {
      cout << "Nodo no encontrado" << endl;
      return NULL;
    }
  }
}

nodo** buscar_nodo_puntero_tipo(nodo **r, int val) {
  if (((*r)->val == val)) {
    return (r);
  } else {
    if ((*r)->next != NULL) {
      return buscar_nodo_puntero_tipo(&(*r)->next, val);
    } else {
      cout << "Nodo no encontrado" << endl;
      return NULL;
    }
  }
}

bool esCoordenadaInterior(int n, int max) {
  return (n < max && n >=0);
}

void designarDireccionesIniciales(nodo **r, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      nodo *p = (*buscar_nodo_puntero_posicion(r, i, j));
      if (esCoordenadaInterior(i + 1, n)) {
        p->down = (*buscar_nodo_puntero_posicion(r, i + 1, j));
      } else {
        p->down = (*buscar_nodo_puntero_posicion(r, 0, j));
      }
      if (esCoordenadaInterior(i - 1, n)) {
        p->up = (*buscar_nodo_puntero_posicion(r, i - 1, j));
      } else {
        p->up = (*buscar_nodo_puntero_posicion(r, (n - 1), j));
      }
      if (esCoordenadaInterior(j + 1, m)) {
        p->right = (*buscar_nodo_puntero_posicion(r, i, j + 1));
      } else {
        p->right = (*buscar_nodo_puntero_posicion(r, i, 0));
      }
      if (esCoordenadaInterior(j - 1, m)) {
        p->left = (*buscar_nodo_puntero_posicion(r, i, j - 1));
      } else {
        p->left = (*buscar_nodo_puntero_posicion(r, i, (m - 1)));
      }
    }
  }
}

void destruirTierra(nodo **posVista) {
    (*posVista)->up->down_tierra = false;
    (*posVista)->up_tierra = false;

    (*posVista)->down->up_tierra = false;
    (*posVista)->down_tierra = false;

    (*posVista)->left->right_tierra = false;
    (*posVista)->left_tierra = false;

    (*posVista)->right->left_tierra = false;
    (*posVista)->right_tierra = false;

    (*posVista)->destroyed = true;
}

void mover(nodo **posPersonaje, nodo **posVista, char direction) {
  nodo **q;
  nodo **r;

  switch (direction) {
    case 'w':
    {
      q = &(*posPersonaje)->up;
      r = &(*posVista)->up;
      break;
    }
    case 'a':
    {
      q = &(*posPersonaje)->left;
      r = &(*posVista)->left;
      break;
    }
    case 's':
    {
      q = &(*posPersonaje)->down;
      r = &(*posVista)->down;
      break;
    }
    case 'd':
    {
      q = &(*posPersonaje)->right;
      r = &(*posVista)->right;
      break;
    }
  }

  if (((*q)->x == (*posVista)->x) && ((*q)->y == (*posVista)->y)) {

    if ((*posPersonaje)->destroyed) {
    (*posPersonaje)->val = 3;
    } else {
      (*posPersonaje)->val = 0;
    }
    (*posVista)->val = 1;
    (*r)->val = 2;
  } else {
    if ((*posVista)->destroyed) {
      (*posVista)->val = 3;
    } else {
    (*posVista)->val = 0;
    }
    (*q)->val = 2;
  }
}

void crearTierra(nodo *posPersonaje, nodo *posVista) {
  int difX = (posPersonaje)->x - (posVista)->x;
  int difY = (posPersonaje)->y - (posVista)->y;

  if (difX != 0) {
    if (difX == -1) {
      posPersonaje->down_tierra = true;
      posVista->up_tierra = true;
    } else if (difX == 1) {
      posPersonaje->up_tierra = true;
      posVista->down_tierra = true;
    }
  } else if (difY != 0) {
    if (difY == -1) {
      posPersonaje->right_tierra = true;
      posVista->left_tierra = true;
    } else if (difY == 1) {
      posPersonaje->left_tierra = true;
      posVista->right_tierra = true;
    }
  }

  posVista->destroyed = false;
}

void imprimir_mapa(nodo **r, int n, int m) {
  cout << endl << endl;
  nodo *p = (*r);
  nodo *q = p;
  for (int i = 0; i < n; i++) {
    nodo *aux = p;
    for (int j = 0; j < m; j++) {
      if (p->val == 0) {
        cout << "O";
      } else if (p->val == 1) {
        cout << "#";
      } else if (p->val == 2) {
        cout << "x";
      } else if (p->val == 3) {
        cout << " ";
      }
      if (p->right_tierra) {
        cout << "-";
      } else {
        cout << " ";
      }
      p = p->next;
    }
    cout << endl;
    for (int j = 0; j < m; j++) {
      if (q->down_tierra) {
        cout << "|";
      } else {
        cout << " ";
      }
      cout << " ";
      q = q->next;
    }
    cout << endl;
  }
}

void recorrer(nodo *r) {

  while (r != NULL) {
    cout << "-" << endl;
    cout << "(" << r->x << "," << r->y << ")" << endl;
      if (r->up != NULL) {
        cout << "Arriba del punto es: " << "(" << r->up->x << "," <<r->up->y << ")" << endl;
      }
      if (r->down != NULL) {
        cout << "Abajo del punto es: " << "(" << r->down->x << "," <<r->down->y << ")" << endl;
      }
      if (r->left != NULL) {
        cout << "Izquierda del punto es: " << "(" << r->left->x << "," <<r->left->y << ")" << endl;
      }
      if (r->right != NULL) {
        cout << "Derecha del punto es: " << "(" << r->right->x << "," <<r->right->y << ")" << endl;
      }

    r = r->next;
  }
}

#endif
