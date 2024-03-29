#include "nodos.h"

using namespace std;
int main(int argc, char **argv){
	
	int n = 5, m = 10;
	if (argc >= 3) {
		if (atoi(argv[1]) > 0) {
			n = atoi(argv[1]);
		}
		if (atoi(argv[2]) > 0) {
			m = atoi(argv[2]);
		}
	}

	bool play = true, err = true;
	char c;
	nodo *r = crear_nodo(0, 0, 1);
	crear_mapa(&r, n, m);
	while (play) {
		nodo **posPersonaje = buscar_nodo_puntero_tipo(&r, 1),
		**posVista = buscar_nodo_puntero_tipo(&r, 2);

		if ((*posPersonaje)->destroyed) {
			mover(posPersonaje, posVista, c);
		} else {
			system("clear");
			imprimir_mapa(&r, n, m);
			if (err) {
				cout << endl << "Ingrese \"w\" / \"a\" / \"s\" / \"d\" para moverse" << endl;
				cout << "Ingrese \"q\" para eliminar las uniones de la tierra en \"x\"" << endl;
				cout << "Ingrege \"e\" para crear una union en la direccion de \"x\"" << endl;
				err = false;
			}
			cout << endl << "Ingrese instrucción: ";
			cin >> c;
			c = char(tolower(c));
			switch (c) {
				case 'w':	case 'a':	case 's':	case 'd':
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
				{
					err = true;
				}
			}

		}

	}

	cout << endl;
	return EXIT_SUCCESS;
}
