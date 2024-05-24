#include <iostream>
#include "Jugador.h"
using namespace std;

/**
*Función para convertir de int a string el personaje que escoja el usuario.
*/
string nombreSob(int select){
    //string name;
    if (select == 1){
        return "Bill";
    }
    else if (select == 2){
        return "Zoey";
    }
    else if (select == 3){
        return "Frank";
    }
    else if (select == 4){
        return "Louis";
    }
    else if (select == 5){
        return "Ellis";
    }
    else if (select == 6){
        return "Rochelle";
    }
    else if (select == 7){
        return "Coach";
    }
    else if (select == 8){
        return "Nick";
    }
    else{
        return "Rochelle";
    }
}

int main(){
  int opcion;
  string name, user;

  cout << "LEFT 4 DEAD (versión barata)\nContexto: En tu equipo habrá cuatro sobrevivientes, haz lo mejor posible para completar el nivel.\n¿Cuál es tu nombre?\n" << endl;
  cin >> user;
  cout << "¿Quieres jugar con los personajes del primer o segundo juego? (Escribe 1 o 2)\n " << endl;

  cin >> opcion;
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
    
  //Pruebas para ver que funcione el programa
  cout << usuario.getNombre() << endl;

  Infectado inf1;

  usuario.ataque(inf1);
  inf1.ataque(usuario);
}
