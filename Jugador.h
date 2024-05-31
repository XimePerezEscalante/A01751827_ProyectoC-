#ifndef Jugador_h
#define Jugador_h

#include <iostream>
#include "Arma.h"

using namespace std;

//Declaración de clase Jugador
class Jugador{
    //Declaración de atributos
private:
    string nombre;
    float vida;
    //Declaración de métodos
public:
    Jugador();
    Jugador(string,float);
    Arma armas[2];
    virtual void ataque(Jugador*);
    virtual void recibeAtaque(float);
    virtual void disparar(Jugador*,int);
    void setVida(float health){vida = health;}
    void setNombre(string name){nombre = name;}
    float getVida(){return vida;}
    string getNombre(){return nombre;}
};

Jugador::Jugador(){
    nombre = "Usuario123";
    vida = 100.0;
}

Jugador::Jugador(string name, float health){
    nombre = name;
    vida = health;
}

void Jugador::disparar(Jugador* infected,int indice){
    cout << "No disponible" << endl;
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
    //Declaración de atributos
private:
    string items[3];
public:
    Arma armas[2];
    //Declaración de métodos
public:
    Sobreviviente();
    Sobreviviente(string name,float health, string it1, string it2, string it3);
    Sobreviviente(string name);
    void recibeAtaque(float);
    void disparar(Jugador*,int);
    void curar(Jugador*);
    void setItems(string it, int indice){items[indice] = it;}
    string getItems(int indice){return items[indice];}
};

Sobreviviente::Sobreviviente():Jugador("Bot", 100.0){
    items[0] = "-";
    items[1] = "Pastillas";
    items[2] = "Botiquín";
}

Sobreviviente::Sobreviviente(string name,float health, string it1, string it2, string it3):Jugador(name,health){
    items[0] = it1;
    items[1] = it2;
    items[2] = it3;
}

Sobreviviente::Sobreviviente(string name):Jugador(name, 100.0){
    items[0] = "-";
    items[1] = "-";
    items[2] = "Botiquín";
}

/**
 *Recibe un apuntador de tipo Jugador
 *Usa el método recibeAtaque() del infectado
 *Dependiendo del tipo de arma es la cantidad de daño
 *y también se le resta munición
 *
 */
void Sobreviviente::disparar(Jugador* infected,int indice){
    if (armas[indice].getAmmoTotal() > 0){
        if (armas[indice].getAmmoDisp() > 0) {
            if (armas[indice].getTipo() == "Primaria"){
                infected->recibeAtaque(95.5);
            }
            else{
                infected->recibeAtaque(75.5);
            }
            armas[indice].setAmmoDisp(armas[indice].getAmmoDisp() - 1);
        }
        else {
            cout << "Debes recargar" << endl;
        }
    }
    else{
        cout << "Ya no tienes munición\n" << endl;
    }
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
        cout << getNombre() << " -" << danio <<  " vida." << endl;
        cout << getVida() << endl;
        if (getVida() <= 30){
            cout << getNombre() << " está muriendo." << endl;
        }
    }
    else{
        cout << getNombre() << " ha muerto.\nSi tienes un desfibrilador puedes revivirlo." << endl;
    }
}

/**
 *Recibe un apuntador de tipo Jugador.
 *Se imprime un mensaje diferente dependiendo de si el sobreviviente se cura a sí mismo o a alguien más, después se le agrega el
 *80% de la vida que le falta, se muestra la vida que tiene después de ser curado y al sobreviviente que curó se le cambia el item
 *"Botiquín" por "-".
 *No devuelve nada.
 */
void Sobreviviente::curar(Jugador* survivor){
    if (getNombre() == survivor->getNombre()){
        cout << getNombre() << " se está curando" << endl;
        setVida( getVida() + (100 - getVida()) * 0.8);
        cout << getNombre() << " " << getVida() << " vida" << endl;
    }
    else{
        cout << getNombre() << " curó a " << survivor->getNombre() << endl;
        survivor->setVida( survivor->getVida() + (100 - survivor->getVida()) * 0.8);
        cout << survivor->getNombre() << " " << survivor->getVida() << " vida" << endl;

    }
    setItems("-", 2);
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
