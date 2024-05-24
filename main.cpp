#include <iostream>
#include "Juego.h"
using namespace std;

int main(){
	int opcion;
	string name, user;
    
	cout << "LEFT 4 DEAD (versión barata)\nContexto: En tu equipo habrá cuatro sobrevivientes, haz lo mejor posible para completar el nivel.\n¿Cuál es tu nombre?\n> " << endl;
	cin >> user;
	cout << "¿Quieres jugar con los personajes del primer o segundo juego? (Escribe 1 o 2)\n " << endl;
	if (opcion == 1){
				cout << "Escoge un personaje:\n1. Bill\n2. Zoey\n3. Frank\n4. Louis\n" << endl;
        cin >> opcion;
        name = nombreSob(opcion);
	}
	else{
				cout << "Escoge un personaje:\n1. Ellis\n2. Rochelle\n3. Coach\n4. Nick" << endl;
        cin >> opcion;
        name = nombreSob(opcion+4);
	}
	
	Sobreviviente usuario(user + " (" + name + ")",100.0);
	
	cout << usuario.getNombre() << endl;
	
	Infectado inf1;
	
	usuario.ataque(inf1);
	inf1.ataque(usuario);

  cout << "Juego en construcción" << endl;
}
