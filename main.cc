#include "nodos.h"

using namespace std;
int main(){

    int n = 5;
    int m = 10;
    bool play = true;
    bool err = true;
    char c;
    nodo *r = crear_nodo(0, 0, 1);

    crear_mapa(&r, n, m);
    while (play) {
      nodo **posPersonaje = buscar_nodo_puntero_tipo(&r, 1);
      nodo **posVista = buscar_nodo_puntero_tipo(&r, 2);

      if ((*posPersonaje)->destroyed) {
        mover(posPersonaje, posVista, c);
      } else {
        imprimir_mapa(&r, n, m);
        if (err) {
          cout << endl << "Ingrese \"w\" / \"a\" / \"s\" / \"d\" para moverse" << endl;
          cout << "Ingrese \"q\" para eliminar las uniones de la tierra en \"x\"" << endl;
          cout << "Ingrege \"e\" para crear una union en la direccion de \"x\"" << endl;
          err = false;
        }
        cout << endl << "Ingrese comando: ";
        cin >> c;
        c = char(tolower(c));
        switch (c) {
          case 'w':
            {
              mover(posPersonaje, posVista, c);
              break;
            }
          case 'a':
            {
              mover(posPersonaje, posVista, c);
              break;
            }
          case 's':
            {
              mover(posPersonaje, posVista, c);
              break;
            }
          case 'd':
            {
              mover(posPersonaje, posVista, c);
              break;
            }
          case 'q':
            {
              destruirTierra(posVista);
              break;
            }
          case 'e':
            {
              crearTierra((*posPersonaje), (*posVista));
              break;
            }
          case '0':
            {
              cout << endl << "Gracias por jugar!!" << endl;
              play = false;
              break;
            }
          default:
            err = true;
        }

      }

    }

    cout << endl;
    return EXIT_SUCCESS;
}
