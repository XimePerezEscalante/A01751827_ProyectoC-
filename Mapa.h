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
public:
    Arma armasMapa[4];
    Jugador * equipoMapa[4];
    Jugador * infectadosMapa[];
public:
    Mapa();
    void agregaEquipo(Jugador*,Jugador*,Jugador*,Jugador*);
};

Mapa::Mapa(){
    Arma pist(0,30,false);
    Arma mag(1,30,false);
    Arma rif(2,120,false);
    Arma esc(2,80,false);
    
    armasMapa[0] = pist;
    armasMapa[1] = mag;
    armasMapa[2] = rif;
    armasMapa[3] = esc;
    
    for (int i = 0;i<11;i++){
        infectadosMapa[i] = new Infectado();
    }
}

void Mapa::agregaEquipo(Jugador* surv1,Jugador* surv2,Jugador* surv3,Jugador* surv4){
    equipoMapa[0] = surv1;
    equipoMapa[1] = surv2;
    equipoMapa[2] = surv3;
    equipoMapa[3] = surv4;
}

#endif /* MAPA_H */
