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
    //Declaración de métodos
public:
    Arma();
    Arma(int, int);
    void recargar();
    void disparo();
    void rellenarMunicion();
    string getNombre(){return nombre;}
    string getTipo(){return tipo;}
    int getAmmoTotal(){return municionTotal;}
    void setAmmoTotal(int ammo){municionTotal = ammo;}
    int getAmmoDisp(){return municionDisp;}
    void setAmmoDisp(int ammo){municionDisp = ammo;}
};

Arma::Arma(){
    nombre = "Pistola";
    tipo = "Secundaria";
    municionTotal = 10;
    municionDisp = 10;
}

Arma::Arma(int name, int ammo){
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
}

/**
 *Le resta 10 de munición a la munición total y a la disponible le suma 10
 *param
 *return
 */
void Arma::recargar(){
    cout << " ¡recargando!" << endl;
    if (getNombre() == "Pistola" || "Magnum"){
        setAmmoDisp(10);
    }
    else{
        setAmmoTotal(getAmmoTotal() - (10 - getAmmoDisp()));
        setAmmoDisp(10);
    }
    cout << "Munición: " << getAmmoDisp() << "[" << getAmmoTotal() <<
    "]" << endl;
}

/**
 *Imprime un mensaje y le resta 1 de munición a la munición
 *disponible
 *param
 *return
 */
void Arma::disparo(){
    setAmmoDisp(getAmmoDisp() - 1);
    cout << " ha disparado\n" << endl;
}

/**
 *Dependiendo del nombre es el total de munición
 *total que le agregará
 *param
 *return
 */
void Arma::rellenarMunicion(){
    if (getNombre() == "Escopeta"){
        setAmmoTotal(80);
    }
    else if (getNombre() == "Rifle"){
        setAmmoTotal(120);
    }
    else{
        setAmmoTotal(10);
    }
}

#endif /* ARMA_H */
