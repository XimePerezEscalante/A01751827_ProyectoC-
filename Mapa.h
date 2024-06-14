//
//  Mapa.h
//  ProyectoTC1030
//
//  Created by Ximena Perez Escalante on 06/06/24.
//

#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include "Jugador.h"

using namespace std;

class Mapa{
    //Declaración de atributos
private:
    int numPersonaje = 4;
    int totalPer = 30;
    int numSobreviviente = 0;
    int indiceUsuario;
    string select;
public:
    Arma armasMapa[4];
    Jugador * personajes[50];
    //Declaración de métodos
public:
    Mapa();
    void creaEquipo(int);
    void agregaUsuario(Jugador*, int);
    void escogeArmas();
    void escogeItems();
    void accion(string);
    void curarMutuo();
    void partida();
};

Mapa::Mapa(){
    Arma pist(0,30,false);
    Arma mag(1,30,false);
    Arma esc(2,80,false);
    Arma rif(3,120,false);
    
    armasMapa[0] = pist;
    armasMapa[1] = mag;
    armasMapa[2] = esc;
    armasMapa[3] = rif;
    
    for (int i = 4;i < 16;i++){
        personajes[i] = new Infectado();
    }
    
    personajes[16] = new InfectadoEspecial();
    personajes[17] = new InfectadoEspecial("Boomer",100.0);
    personajes[18] = new InfectadoEspecial("Spitter",100.0);
    personajes[19] = new InfectadoEspecial("Smoker",100.0);
    personajes[20] = new InfectadoEspecial("Tank",100.0);
    personajes[21] = new InfectadoEspecial("Witch",100.0);
    personajes[22] = new InfectadoEspecial("Hunter",100.0);
    personajes[23] = new InfectadoEspecial("Charger",100.0);
}

/**
 *Uso de composición con la clase Sobreviviente
 *Función que crea el equipo de 4 sobrevivientes y los agrega al arreglo de
 *apuntadores llamado personajes
 *param int debe ser 1 o 2 para saber de qué juego serán los personajes
 *return
 */
void Mapa::creaEquipo(int opcion){
    if (opcion == 1){
        personajes[0] = new Sobreviviente("Zoey", true);
        personajes[1] = new Sobreviviente("Bill", true);
        personajes[2] = new Sobreviviente("Louis", true);
        personajes[3] = new Sobreviviente("Frank", true);
    }
        
    else{
        Jugador *rochelle = new Sobreviviente("Rochelle", true);
        Jugador *nick = new Sobreviviente("Nick", true);
        Jugador *coach = new Sobreviviente("Coach", true);
        Jugador *ellis = new Sobreviviente("Ellis", true);
        personajes[0] = rochelle;
        personajes[1] = nick;
        personajes[2] = coach;
        personajes[3] = ellis;
    }
}

/**
 *Función que agrega al usuario (apuntador de tipo jugador que apunta
 *a sobreviviente) al arreglo de apuntadores llamado personajes
 *param: apuntador de tipo jugador que apunta a sobreviviente (usr),
 *int (indice) para saber en qué posición del arreglo se agregará al 
 *jugador
 *return
 */
void Mapa::agregaUsuario(Jugador * usr, int indice){
    usr->setNombre(usr->getNombre() + " (" + 
                   personajes[indice - 1]->getNombre() + ")");
    personajes[indice - 1] = usr;
    indiceUsuario = indice - 1;
}

/**
 *Función para que al inicio de la partida el usuario pueda escoger sus
 *armas y a los bots se les asignen
 *param
 *return
 */
void Mapa::escogeArmas(){
    int arma_elec;
    cout << "Escojan sus armas (una secundaria y una primaria):" << endl;
    for (int i = 0; i < 4;i++){
        cout << i+1 << ". " << armasMapa[i].getNombre() << "  Tipo: " << 
            armasMapa[i].getTipo() << endl;
    }
    cout << "Arma primaria: \n(Escoge el número del arma): ";
    cin >> arma_elec;
    while (arma_elec < 3 || arma_elec > 4){
        cout << "Arma primaria: \n(Escoge el número del arma): ";
        cin >> arma_elec;
    }
    personajes[indiceUsuario]->agregaArma(armasMapa[arma_elec - 1], 0);
    cout << "Arma secundaria: \n(Escoge el número del arma): ";
    cin >> arma_elec;
    while (arma_elec < 1 || arma_elec > 2){
        cout << "Arma secundaria: \n(Escoge el número del arma): ";
        cin >> arma_elec;
    }
    personajes[indiceUsuario]->agregaArma(armasMapa[arma_elec - 1], 1);
    
    for (int i = 0;i < 4;i++){
        if (personajes[i]->getBot() == true){
            personajes[i]->agregaArma(armasMapa[1], 1);
            if (i < 2){
                personajes[i]->agregaArma(armasMapa[2], 0);
            }
            else{
                personajes[i]->agregaArma(armasMapa[3], 0);
            }
        }
    }
    
    
}

/**
 *Función para que al inicio de la partida el usuario pueda escoger sus
 *items y a los bots se les asignen
 *param
 *return
 */
void Mapa::escogeItems(){
    int itm_selec;
    cout << "Escojan los items que quieran:\n1. Pastillas\n2. Adrenalina\n> ";
    cin >> itm_selec;
    while (itm_selec < 1 || itm_selec > 2){
        cout << "Por favor selecciona 1 o 2: " << endl;
        cin >> itm_selec;
    }
    if (itm_selec == 1){
        personajes[indiceUsuario]->setItems("Pastillas", 2);
    }
    else{personajes[indiceUsuario]->setItems("Adrenalina", 2);}
    cout << "\n1. Botiquín\n2. Desfibrilador\n> ";
    cin >> itm_selec;
    while (itm_selec < 1 || itm_selec > 2){
        cout << "Por favor selecciona 1 o 2: " << endl;
        cin >> itm_selec;
    }
    if (itm_selec == 1){
        personajes[indiceUsuario]->setItems("Botiquín", 1);
    }
    else{personajes[indiceUsuario]->setItems("Desfibrilador", 1);}
    cout << "\n1. Bomba\n2. Molotov\n> ";
    cin >> itm_selec;
    while (itm_selec < 1 || itm_selec > 2){
        cout << "Por favor selecciona 1 o 2: " << endl;
        cin >> itm_selec;
    }
    if (itm_selec == 1){
        personajes[indiceUsuario]->setItems("Bomba", 0);
    }
    else{personajes[indiceUsuario]->setItems("Molotov", 0);}
    
    for (int i = 0;i < 4;i++){
        if (personajes[i]->getBot() == true){
            personajes[i]->setItems("Botiquín", 1);
            if (i < 2){
                personajes[i]->setItems("Pastillas", 2);
            }
            else{
                personajes[i]->setItems("Adrenalina", 2);
            }
        }
    }
}

/**
 *Función para mandar a llamar a la función que el usuario haya seleccionado según la 
 *tecla
 *param: string tecla debe ser "d", "D", "c", "C", "r", "R", "1", "2", "3", "4", o "5"
 *return
 */
void Mapa::accion(string tecla){
    if (tecla == "d" || tecla == "D"){
        cout << "bruh" << endl;
        if (personajes[indiceUsuario]->getInvSelec() == 2){
            if (personajes[indiceUsuario]->getItems(0) == "Bomba"){
                cout << personajes[indiceUsuario]->getNombre() << " lanzó una bomba" << endl;
            }
            else if (personajes[indiceUsuario]->getItems(0) == "Molotov"){
                cout << personajes[indiceUsuario]->getNombre() << " lanzó un molotov" << endl;
                }
            
            for (int i = 0;i < 4;i++){
                personajes[indiceUsuario]->ataque(personajes[numPersonaje + i]);
            }
            personajes[indiceUsuario]->setInvSelec(1);
        }
        else{
            personajes[indiceUsuario]->ataque(personajes[numPersonaje]);
        }
    }
    if (tecla == "r" || tecla == "R"){
        if (personajes[indiceUsuario]->getInvSelec() > 1){
            cout << "Selecciona un arma para recargar" << endl;
        }
        else{
            personajes[indiceUsuario]->armas[personajes[indiceUsuario]->getInvSelec()].recargar();
        }
    }
    if (tecla == "c" || tecla == "C"){
        cout << "Curar a:" << endl;
        for (int i = 0; i < 4;i++){
            cout << i+1 << ". " <<
            personajes[i]->getNombre() << "  ";
        }
        cout << "\n> ";
        cin >> numSobreviviente;
        while (numSobreviviente < 1 && numSobreviviente > 4){
            cout << "Escoge a un sobreviviente\n> ";
            cin >> numSobreviviente;
        }
        personajes[indiceUsuario]->curar(personajes[numSobreviviente - 1],
        personajes[indiceUsuario]->getItems(
        personajes[indiceUsuario]->getInvSelec()));
    }
    if (tecla == "1"){
        personajes[indiceUsuario]->setInvSelec(1);
        cout << personajes[indiceUsuario]->armas[0].getNombre() << " seleccionad@" << endl;
    }
    if (tecla == "2"){
        personajes[indiceUsuario]->setInvSelec(2);
        cout << personajes[indiceUsuario]->armas[1].getNombre() << " seleccionad@" << endl;
    }
    if (tecla == "3"){
        personajes[indiceUsuario]->setInvSelec(3);
        cout << personajes[indiceUsuario]->getItems(0)<< " seleccionad@" << endl;
    }
    if (tecla == "4"){
        personajes[indiceUsuario]->setInvSelec(4);
        cout << personajes[indiceUsuario]->getItems(1)<< " seleccionad@" << endl;
    }
    if (tecla == "5"){
        personajes[indiceUsuario]->setInvSelec(5);
        cout << personajes[indiceUsuario]->getItems(2)<< " seleccionad@" << endl;
    }
}

/**
 *Función para que los bots puedan curarse entre ellos y se le recuerde al jugador
 *que también los puede curar
 *param
 *return
 */
void Mapa::curarMutuo(){
    int seleccionInt;
    if (personajes[numSobreviviente]->getVida() < 50){
        //Si no tiene items de salud no se puede curar
        if (personajes[numSobreviviente]->getItems(1) == "-" && personajes[numSobreviviente]->getItems(2) == "-"){
            //Se checa si los otros jugadores bots tienen items de salud
            for (int i = 0;i < 4;i++){
                if (personajes[i]->getBot() == true){
                    //Se le da prioridad al botiquín, si lo tiene, cura al infectado con poca salud
                    if (personajes[i]->getItems(1) == "Botiquín"){personajes[i]->curar(personajes[numSobreviviente], "Botiquín");
                    }
                    //Se checa si tiene pastillas o adrenalina
                    else{
                        if (personajes[i]->getItems(2) != "-"){
                            //Cura al sobreviviente pero como en el método sólo le dan los items...
                            personajes[i]->curar(personajes[numSobreviviente], personajes[i]->getItems(2));
                            //El sobreviviente debe curarse solo
                            personajes[numSobreviviente]->curar(personajes[numSobreviviente], personajes[numSobreviviente]->getItems(2));
                        }
                        //Si el usuario tiene items de salud se le sugiere curarlo
                        else{
                            //Se le da prioridad al botiquín
                            if (personajes[indiceUsuario]->getItems(1) == "Botiquín"){
                                cout << "¿Curar a " << personajes[numSobreviviente]->getNombre() << "?\n1. Si 2. No\n(Escribe 1 o 2)" << endl;
                                cin >> seleccionInt;
                                if (seleccionInt == 1){
                                    //El usuario cura al sobreviviente
                                    personajes[indiceUsuario]->curar(personajes[numSobreviviente], "Botiquín");
                                }
                            }
                            //Se checa si el usuario tiene pastillas o adrenalina
                            else{
                                if (personajes[indiceUsuario]->getItems(2) != "-"){
                                    cout << "Le puedes dar tu(s) " << personajes[indiceUsuario]->getItems(2) << " a " << personajes[numSobreviviente]->getNombre() << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
        else{
            if (personajes[numSobreviviente]->getItems(1) == "Botiquín"){
                personajes[numSobreviviente]->curar(personajes[numSobreviviente], "Botiquín");
            }
            else{
                if (personajes[numSobreviviente]->getItems(2) == "Pastillas"){
                    personajes[numSobreviviente]->curar(personajes[numSobreviviente], "Pastillas");
                }
                else{
                    personajes[numSobreviviente]->curar(personajes[numSobreviviente], "Adrenalina");
                }
                    
            }
        }
    }
}


void Mapa::partida(){
    string seleccion;
    int acum = 0;
    bool seguir = true;
    
    cout << "EQUIPO:" << endl;
    for (int i = 0;i < 4;i++){
        cout << personajes[i]->getNombre() << endl;
    }
    escogeArmas();
    escogeItems();
    cout << "Prepárate para luchar" << endl;
    while (numPersonaje < totalPer && seguir == true){
        while (numSobreviviente < 4 && seguir == true){      
            if (personajes[numPersonaje]->getVida() > 0 ){
                personajes[numPersonaje]->ataque(personajes[numSobreviviente]);    
                if (personajes[numSobreviviente]->getBot() == true){
                    if (personajes[numSobreviviente]->getVida() > 0){
                        personajes[numSobreviviente]->ataque(personajes[numPersonaje]);
                        curarMutuo();
                    }
                }
                else{
                    if (personajes[numSobreviviente]->getVida() > 0){
                        cout << "> ";
                        cin >> seleccion;
                        cout << "> " << seleccion << endl;
                        accion(seleccion);
                    }
                }
                if (personajes[indiceUsuario]->getVida() <= 0){
                    seguir = false;
                }
                numSobreviviente ++;
            }
            else{
                numPersonaje ++;
            }
        }
        numSobreviviente = 0;
        numPersonaje ++;
    }
    cout << "Fin de la partida\n" << endl;
    cout << "EQUIPO:" << endl;
    for (int i = 0;i < 4;i++){
        cout << personajes[i]->getNombre();
        if (personajes[i]->getVida() <= 0){
            cout << " - muert@" << endl;
        }
        else{
            cout << endl;
        }
    }
}
                
#endif /* MAPA_H */
