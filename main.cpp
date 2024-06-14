/*
 * Proyecto Left 4 Dead main
 * Ximena Pérez Escalante
 * A01751827
 * 14/06/2024
 *
 * En este proyecto se simula una partida de Left 4 Dead, en el que 
 * hay 4 sobrevivientes que deben combatir a una horda de infectados 
 * (zombies) e infectados especiales (mutaciones). En ella el usuario
 * puede escoger si jugar con los sobrevivientes del primer o segundo 
 * juego, además de interactuar disparándole a los infectados o curando
 * a sus compañeros hasta que este muera.
 */

#include <iostream>
#include "Jugador.h"
#include "Mapa.h"
#include "Arma.h"
using namespace std;

int main(int argc, const char * argv[]) {

    int opcion;
    string user;
    Mapa m1;

    cout << "LEFT 4 DEAD (versión barata)\n" <<
        "Contexto: En tu equipo habrá cuatro" << 
        " sobrevivientes, haz lo mejor posible" << 
        " para completar el nivel.\n¿Cuál es tu"
        << " nombre?\n> ";
    cin >> user;

    cout << "¿Quieres jugar con los personajes " <<
        "del primer o segundo juego? (Escribe 1 o 2)"
        << "\n> ";
    cin >> opcion;

    while (opcion != 1 && opcion !=2){
        cout << "Escoge 1 o 2:\n> ";
        cin >> opcion;
    }

    m1.creaEquipo(opcion);

    if (opcion == 1){
        cout << 
            "Escoge un personaje:\n1. Zoey\n" <<
            "2. Bill\n3. Louis\n4. Frank\n> ";
        cin >> opcion;
    }

    else{
        cout << 
            "Escoge un personaje:\n1. Rochelle\n"
            << "2. Nick\n3. Coach\n4. Ellis\n> ";
        cin >> opcion;
    }

    Jugador *usuario = new Sobreviviente(user, false);

    m1.agregaUsuario(usuario, opcion);
    m1.partida();
}