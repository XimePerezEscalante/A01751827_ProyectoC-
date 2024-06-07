#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include "Arma.h"

using namespace std;

//Declaración de clase Jugador que es abstracta
class Jugador{
private:
    string nombre;
    string items[3];
    float vida;
public:
    Arma armas[2];
public:
    Jugador();
    Jugador(string,float);
    virtual void ataque(Jugador*);
    virtual void recibeAtaque(float) = 0;
    void agregaArma(Arma, int);
    void disparar(Jugador*,int);
    void curar(Jugador*, string);
    Arma getArma(int indice){return armas[indice];}
    void setVida(float health){vida = health;}
    void setNombre(string name){nombre = name;}
    float getVida(){return vida;}
    string getNombre(){return nombre;}
    void setItems(string it, int indice){items[indice] = it;}
    string getItems(int indice){return items[indice];}
    
};

Jugador::Jugador(){
    nombre = "Usuario123";
    vida = 100.0;
}

Jugador::Jugador(string name, float health){
    nombre = name;
    vida = health;
    items[0] = "-";
    items[1] = "-";
    items[2] = "Botiquín";
}

void Jugador::agregaArma(Arma weapon,int indice){
    armas[indice] = weapon;
    cout << weapon.getNombre() << "agregada al inventario" << endl;
    cout << armas[indice].getNombre() << "ahora en el inventario" << endl;
}


void Jugador::disparar(Jugador * infected, int indice){
    if (armas[indice].getAmmoTotal() > 0){
        if (armas[indice].getAmmoDisp() > 0) {
            cout << "BOOM!" << endl;
            armas[indice].disparo();
            if (armas[indice].getNombre() == "Pistola"){
                infected->recibeAtaque(30.5);
            }
            else if (armas[indice].getNombre() == "Magnum"){
                infected->recibeAtaque(80.5);
            }
            else if (armas[indice].getNombre() == "Rifle"){
                infected->recibeAtaque(90.5);
            }
            else if (armas[indice].getNombre() == "Escopeta"){
                infected->recibeAtaque(100.0);
            }
            //getArma(indice).setAmmoDisp(armas[indice].getAmmoDisp() - 1);
        }
        else {
            cout << "Debes recargar" << endl;
        }
    }
    else{
        cout << "Ya no tienes munición\n" << endl;
    }
    cout << "Ammo: " << armas[indice].getAmmoDisp() << endl;
}

/**
 *Recibe un apuntador de tipo Jugador.
 *Se imprime un mensaje diferente dependiendo de si el sobreviviente se cura a sí mismo o a alguien más, después se le agrega el
 *80% de la vida que le falta, se muestra la vida que tiene después de ser curado y al sobreviviente que curó se le cambia el item
 *"Botiquín" por "-".
 *No devuelve nada.
 */
void Jugador::curar(Jugador* survivor, string itm){
    if (getNombre() == survivor->getNombre()){
        if (itm == "Botiquín"){
            cout << getNombre() << " se está curando" << endl;
            setVida( getVida() + (100.0 - getVida()) * 0.8);
            cout << getNombre() << " " << getVida() << " vida" << endl;
            setItems("-", 2);
        }
        else if (itm == "Pastillas"){
            cout << getNombre() << " tomó pastillas" << endl;
            setVida( getVida() + (100.0 - getVida()) * 0.5);
            cout << getNombre() << " " << getVida() << " vida" << endl;
            setItems("-", 1);
        }
        else if (itm == "Adrenalina"){
            cout << getNombre() << " se inyectó adrenalina" << endl;
            setVida( getVida() + (100.0 - getVida()) * 0.25);
            cout << getNombre() << " " << getVida() << " vida" << endl;
            setItems("-", 1);
        }
        else{
            cout << "Sólo puedes usar un desfibrilador en tus compañeros." << endl;
        }
    }
    else{
        if (itm == "Botiquín"){
            cout << getNombre() << " curó a " << survivor->getNombre() << endl;
            survivor->setVida( survivor->getVida() + (100.0 - survivor->getVida()) * 0.8);
            cout << survivor->getNombre() << " " << survivor->getVida() << " vida" << endl;
            setItems("-", 2);
        }
        else if (itm == "Pastillas"){
            cout << getNombre() << " le dio pastillas a " << survivor->getNombre() << endl;
            survivor->setItems("Pastillas", 1);
        }
        else if (itm == "Adrenalina"){
            cout << getNombre() << " le dio adrenalina a " << survivor->getNombre() << endl;
            survivor->setItems("Adrenalina", 1);
        }
        else{
            cout << getNombre() << " revivió a " << survivor->getNombre() << endl;
            survivor->setVida(50.0);
            cout << survivor->getNombre() << " " << survivor->getVida() << " vida" << endl;
            setItems("-", 2);
        }
            
    }
}

/**
 *Recibe un apuntador de tipo Jugador, usa el método recibeAtaque() que recibe 
 *la cantidad de daño (float).
 *Imprime el nombre del jugador que atacó, así como al atacado.
 *No devuelve nada.
*/
void Jugador::ataque(Jugador* player){
    player->recibeAtaque(5.0);
    cout << getNombre() << " atacó AA " << player->getNombre() << endl;
}

/**
 *Recibe la variable danio (float).
 *Si la vida es mayor a 0, entonces le resta el daño, si no, imprime que ha muerto.
 *No devuelve nada
 */
void Jugador::recibeAtaque(float danio){
    if (getVida() > 0){
        setVida(getVida() - danio);
        cout << "Jugador " << getNombre() << " -" << danio <<  " vida." << endl;
        cout << getVida() << endl;
    }
    else{
        cout << getNombre() << " ha muerto." << endl;
    }
}

//Declaración de clase Sobreviviente que deriva de Jugador
class Sobreviviente:public Jugador{
    //Declaración de métodos
public:
    Sobreviviente(string name);
    void recibeAtaque(float);
};

Sobreviviente::Sobreviviente(string name):Jugador(name, 100.0){
    //items[0] = "-";
    //items[1] = "-";
    //items[2] = "Botiquín";
}


/**
 *Recibe la variable danio (float).
 *Si la vida es mayor a 0, entonces le resta el daño, si esta es menor o igual a 30, imprime el nombre del sobreviviente
 *que esté muriendo, si no, imprime que ha muerto y que puede ser revivido.
 *No devuelve nada.
 */
void Sobreviviente::recibeAtaque(float danio){
    cout << getVida() << endl;
    if (getVida() > 0){
        setVida(getVida() - danio);
        cout << getNombre() << " -" << danio <<  " vida = " << getVida() << endl;
        if (getVida() <= 30){
            cout << getNombre() << " está muriendo." << endl;
        }
    }
    else{
        cout << getNombre() << " ha muerto.\nSi tienes un desfibrilador puedes revivirlo." << endl;
    }
}


//Declaración de clase Infectado que deriva de Jugador
class Infectado:public Jugador{
    //Declaración de los métodos
public:
    Infectado():Jugador("Infectado Común",50.0){}
    Infectado(string name, float health):Jugador(name,health){}
    void ataque(Jugador*);
    void recibeAtaque(float);
};

/**
 *Uso de Sobreescritura y Polimorfismo
 *Recibe un apuntador de tipo Jugador, usa el método recibeAtaque() que recibe la cantidad de daño (float).
 *No devuelve nada.
*/
void Infectado::ataque(Jugador* survivor){
    survivor->recibeAtaque(5.0);
}

/**
 *Recibe daño (float).
 *Si la vida del infectado es mayor a 0, entonces le resta el daño, si no, imprime que ha muerto.
 *No devuelve nada
 */
void Infectado::recibeAtaque(float danio){
    if (getVida() > 0){
        setVida(getVida() - danio);
        cout << "Infectado " << getNombre() << " -" << danio <<  " vida." << endl;
    }
    else {
        cout << "Infectado " << getNombre() << " ha muerto." << endl;
    }
}

//Declaración de clase InfectadoEspecial que deriva de Jugador
class InfectadoEspecial:public Jugador{
    //Declaración de atributos
private:
    string habilidad;
    //Declaración de métodos
public:
    InfectadoEspecial();
    InfectadoEspecial(string,string,float);
    void ataque(Jugador*);
    void ataque(Jugador* []);
    void recibeAtaque(float);
    string getHabilidad();
    void setHabilidad(string);
};

InfectadoEspecial::InfectadoEspecial():Jugador("Jockey",100.0){
    habilidad = "montar y atacar al jugador hasta que muere.";
}

InfectadoEspecial::InfectadoEspecial(string hab,string name,float health):Jugador(name,health){
    habilidad = hab;
}

/**
 *Uso de sobreescritura y polimorfismo
 *Recibe un apuntador de tipo Jugador
 *Sependiendo del tipo de infectado es el daño que hará y el mensaje que imprimirá
 *No devuelve nada
 */
void InfectadoEspecial::ataque(Jugador* survivor){
    if (getNombre() == "Jockey"){
        cout << "Jockey ha montado a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(15.5);
    }
    else if (getNombre() == "Boomer"){
        cout << getNombre() << " explotó y salpicó a " << survivor->getNombre() << endl;
    }
    else if (getNombre() == "Spitter"){
        cout << getNombre() << " les ha escupido" << endl;
        survivor->recibeAtaque(75.5);
    }
    else if (getNombre() == "Charger"){
        cout << getNombre() << " está atacando a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(75.5);
    }
    else if (getNombre() == "Hunter"){
        cout << getNombre() << " está atacando a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(75.5);
    }
    else if (getNombre() == "Smoker"){
        cout << getNombre() << " ha atrapado a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(75.5);
    }
    else if (getNombre() == "Witch"){
        cout << getNombre() << " está atacando a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(75.5);
    }
    else if (getNombre() == "Tank"){
        cout << getNombre() << " ha aventado a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(75.5);
    }
    survivor->recibeAtaque(5.0);
}


void InfectadoEspecial::recibeAtaque(float danio){
    if (getVida() > 0){
        setVida(getVida() - danio);
        cout << getNombre() << " -" << danio <<  " vida." << endl;
    }
    else {
        cout << getNombre() << " ha muerto." << endl;
    }
}

#endif /* Jugador_h */
