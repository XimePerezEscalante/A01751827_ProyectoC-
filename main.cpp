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
    Jugador * equipo[4];
    
    cout << "LEFT 4 DEAD (versión barata)\nContexto: En tu equipo habrá cuatro sobrevivientes, haz lo mejor posible para completar el nivel.\n" << endl;
    user = "Usuario";
    
    cout << "¿Quieres jugar con los personajes del primer o segundo juego? (Escribe 1 o 2)\n " << endl;
    cin >> opcion;
    
    if (opcion == 1){
        Jugador *zoey = new Sobreviviente("Zoey (Bot)");
        Jugador *bill = new Sobreviviente("Bill (Bot)");
        Jugador *louis = new Sobreviviente("Louis (Bot)");
        Jugador *frank = new Sobreviviente("Frank (Bot)");
        equipo[0] = bill;
        equipo[1] = zoey;
        equipo[2] = frank;
        equipo[3] = louis;
        cout << "Escoge un personaje:\n1. Bill\n2. Zoey\n3. Frank\n4. Louis\n" << endl;
        cin >> opcion;
        name = nombreSob(opcion);
    }
        
    else{
        Jugador *rochelle = new Sobreviviente("Rochelle (Bot)");
        Jugador *nick = new Sobreviviente("Nick (Bot)");
        Jugador *coach = new Sobreviviente("Coach (Bot)");
        Jugador *ellis = new Sobreviviente("Ellis (Bot)");
        equipo[0] = ellis;
        equipo[1] = rochelle;
        equipo[2] = coach;
        equipo[3] = nick;
        cout << "Escoge un personaje:\n1. Ellis\n2. Rochelle\n3. Coach\n4. Nick" << endl;
        cin >> opcion;
        name = nombreSob(opcion+4);
    }
    
    Jugador *usuario = new Sobreviviente(user + " (" + name + ")");
    equipo[opcion-1] = usuario;
    
    
    cout << "EQUIPO:" << endl;
    
    for (int i = 0;i < 4;i++){
        cout << equipo[i]->getNombre() << endl;
    }

    //Pruebas para ver que funcione el programa
    Jugador *inf1 = new Infectado();
    Jugador *tank = new InfectadoEspecial("Lanzar objetos y jugadores","Tank",3000.0);
    inf1->ataque(usuario);
    tank->ataque(equipo[0]);
    inf1->ataque(equipo[3]);
    usuario->disparar(inf1,2);
    usuario->disparar(tank,0);
}
