#ifndef NODO_H
#define NODO_H

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

    // struct nodo *up;
    // struct nodo *down;
    // struct nodo *right;
    // struct nodo *left;

    struct nodo *next;
}nodo;

typedef struct pos{
  int x;
  int y;
}pos;

using namespace std;

pos* crear_pos(int x, int y) {
  pos *q = (pos*)malloc(sizeof(pos));
  q->x = x;
  q->y = y;

  return q;
}

nodo* crear_nodo(int x, int y, int val, int n, int m) {
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
        p->next = crear_nodo(i, j, 2, n, m);
        p = p->next;
      } else if (!((i == 0) && (i == j))) {
        p->next = crear_nodo(i, j, 0, n, m);
        p = p->next;
      }
    }
  }
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

bool esCoordenadaValida(int n, int max) {
  return (n < max && n >=0);
}

void designarDireccionesIniciales(nodo **r, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      nodo *p = (*buscar_nodo_puntero_posicion(r, i, j));
      if (esCoordenadaValida(i + 1, n)) {
        p->down = (*buscar_nodo_puntero_posicion(r, i + 1, j));
      } else {
        p->down = (*buscar_nodo_puntero_posicion(r, 0, j));
      }
      if (esCoordenadaValida(i - 1, n)) {
        p->up = (*buscar_nodo_puntero_posicion(r, i - 1, j));
      } else {
        p->up = (*buscar_nodo_puntero_posicion(r, (n - 1), j));
      }
      if (esCoordenadaValida(j + 1, m)) {
        p->right = (*buscar_nodo_puntero_posicion(r, i, j + 1));
      } else {
        p->right = (*buscar_nodo_puntero_posicion(r, i, 0));
      }
      if (esCoordenadaValida(j - 1, m)) {
        p->left = (*buscar_nodo_puntero_posicion(r, i, j - 1));
      } else {
        p->left = (*buscar_nodo_puntero_posicion(r, i, (m - 1)));
      }
    }
  }
}

void DestruirTierra(nodo **posVista) {
  // if ((*posVista)->up != NULL) {
    (*posVista)->up->down_tierra = false;
    (*posVista)->up_tierra = false;
  // }
  //cortar conexion con down
  // if ((*posVista)->down != NULL) {
    (*posVista)->down->up_tierra = false;
    (*posVista)->down_tierra = false;
  // }

  //cortar conexion con left
  // if ((*posVista)->left != NULL) {
  (*posVista)->left->right_tierra = false;
  (*posVista)->left_tierra = false;
  // }
  //cortar conexion con right
  // if ((*posVista)->right != NULL) {
  (*posVista)->right->left_tierra = false;
  (*posVista)->right_tierra = false;

  (*posVista)->destroyed = true;

  // }
}

void crearTierra(nodo *posPersonaje, nodo *posVista) {
  if (posPersonaje == NULL) {
    cout << "personaje es null" << endl;
  }
  if (posVista== NULL) {
    cout << "vista es null" << endl;
  }

  pos *personaje = crear_pos((posPersonaje)->x, (posPersonaje)->y);
  pos *vista = crear_pos((posVista)->x, (posVista)->y);
  int difX = personaje->x - vista->x;
  int difY = personaje->y - vista->y;

  if (difX != 0) {
    if (difX == -1) {
      // posPersonaje->down = posVista;
      posPersonaje->down_tierra = true;
      // posVista->up = posPersonaje;
      posVista->up_tierra = true;

    } else if (difX == 1) {
      // posPersonaje->up = posVista;
      posPersonaje->up_tierra = true;
      // posVista->down = posPersonaje;
      posVista->down_tierra = true;
    }
  } else if (difY != 0) {
    if (difY == -1) {
      // posPersonaje->right = posVista;
      posPersonaje->right_tierra = true;
      // posVista->left = posPersonaje;
      posVista->left_tierra = true;
    } else if (difY == 1) {
      // posPersonaje->left = posVista;
      posPersonaje->left_tierra = true;
      // posVista->right = posPersonaje;
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
