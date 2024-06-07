//
//  Arma.h
//  ProyectoTC1030
//
//  Created by Ximena Perez Escalante on 27/05/24.
//

#ifndef ARMA_H
#define ARMA_H

#include <iostream>
using namespace std;

//Declaración de clase Arma
class Arma{
    //Declaración de atributos
private:
    string nombre;
    string tipo;
    int municionTotal;
    int municionDisp;
    bool laser;
    //Declaración de métodos
public:
    Arma();
    Arma(int, int, bool);
    void recargar();
    void disparo();
    string getNombre(){return nombre;}
    void setNombre(string name){nombre = name;}
    string getTipo(){return tipo;}
    //void setTipo(string type){tipo = type;}
    int getAmmoTotal(){return municionTotal;}
    void setAmmoTotal(int ammo){municionTotal = ammo;}
    int getAmmoDisp(){return municionDisp;}
    void setAmmoDisp(int ammo){municionDisp = ammo; cout << "Has setteado\nNueva: " << getAmmoDisp() << endl;}
    bool getLAser(){return laser;}
    void setLaser(bool lsr){laser = lsr;}
};

Arma::Arma(){
    nombre = "Pistola";
    tipo = "Secundaria";
    municionTotal = 10;
    municionDisp = 10;
    laser = false;
}

Arma::Arma(int name, int ammo, bool lsr){
    string weapons[] = {"Pistola","Magnum","Escopeta","Rifle"};
    nombre = weapons[name];
    if (name > 1){
        tipo = "Primaria";
    }
    else {
        tipo = "Secundaria";
    }
    municionTotal = ammo;
    municionDisp = 10;
    laser = lsr;
}

/**
 *No recibe nada
 *Le resta 10 de munición a la munición total y a la disponible le suma 10
 *No devuelve nada
 */
void Arma::recargar(){
    cout << "Recargando..." << endl;
    if (getNombre() == "Pistola" || "Magnum"){
        setAmmoDisp(10);
    }
    else{
        setAmmoTotal(getAmmoTotal() - (10 - getAmmoDisp()));
        setAmmoDisp(10);
    }
    cout << "Munición: " << getAmmoDisp() << "[" << getAmmoTotal() << "]" << endl;
}

void Arma::disparo(){
    setAmmoDisp(getAmmoDisp() - 1);
    cout << "Has disparado\n" << getAmmoDisp() << endl;
}


#endif /* Arma_h */
