#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include "Arma.h"

using namespace std;

//Declaración de clase Jugador que es abstracta
class Jugador{
    //Declaración de atributos
private:
    string nombre;
    string items[3];
    float vida;
    int infKilled;
    int inventarioSelec;
    bool bot;
public:
    Arma armas[2];
    //Declaración de métodos
public:
    Jugador();
    Jugador(string,float,bool);
    Jugador(string,float,string,string,string,bool);

    virtual void ataque(Jugador*);
    virtual void recibeAtaque(float) = 0;
    virtual void agregaArma(Arma, int);
    virtual void curar(Jugador*, string);
    
    void setVida(float health){vida = health;}
    void setNombre(string name){nombre = name;}
    float getVida(){return vida;}
    string getNombre(){return nombre;}
    void setItems(string it, int indice){items[indice] = it;}
    string getItems(int indice){return items[indice];}
    void setInfKilled(int num){infKilled = num;}
    int getInfKilled(){return infKilled;}
    void setInvSelec(int num){inventarioSelec = num - 1;}
    int getInvSelec(){return inventarioSelec;}
    bool getBot(){return bot;}
};

Jugador::Jugador(){
    nombre = "Usuario123";
    vida = 100.0;
    items[0] = "-";
    items[1] = "-";
    items[2] = "-";
    infKilled = 0;
    inventarioSelec = 1;
    bot = true;
}

Jugador::Jugador(string name, float health, bool tipo){
    nombre = name;
    vida = health;
    items[0] = "-";
    items[1] = "Botiquín";
    items[2] = "-";
    infKilled = 0;
    inventarioSelec = 1;
    bot = tipo;
}

Jugador::Jugador(string name, float health, string it1, 
string it2, string it3, bool tipo){
    nombre = name;
    vida = health;
    items[0] = it1;
    items[1] = it2;
    items[2] = it3;
    infKilled = 0;
    inventarioSelec = 1;
    bot = tipo;
}

/**
 *Imprime que la función no está disponible
 *param: apuntador de tipo Jugador e int
 *return
*/
void Jugador::agregaArma(Arma weapon,int indice){
    cout << "No disponible" << endl;
}

/**
 *Imprime que la función no está disponible
 *param: apuntador de tipo Jugador y string
 *return
*/
void Jugador::curar(Jugador* survivor, string itm){
    cout << "No disponible" << endl;
}

/**
 *Usa el método recibeAtaque() que recibe la cantidad de daño 
 *(float). Imprime el nombre del jugador que atacó, así como
 *al atacado.
 *param: apuntador de tipo Jugador
 *return
*/
void Jugador::ataque(Jugador* player){
    player->recibeAtaque(5.0);
    cout << getNombre() << " atacó a " << player->getNombre() << 
        endl;
}

/**
 *Si la vida es mayor a 0, entonces le resta el daño, si no, 
 *imprime que ha muerto.
 *param: float (danio).
 *return
 */
void Jugador::recibeAtaque(float danio){
    if (getVida() > 0){
        setVida(getVida() - danio);
        cout << "Jugador " << getNombre() << " -" << danio <<  
            " vida." << endl;
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
    Sobreviviente();
    Sobreviviente(string,bool);
    void ataque(Jugador*);
    void agregaArma(Arma, int);
    void recibeAtaque(float);
    void curar(Jugador*, string);
};

Sobreviviente::Sobreviviente():Jugador("Bot", 100.0, true){}

Sobreviviente::Sobreviviente(string name, bool tipo):Jugador(name, 
100.0, tipo){}

/**
 *Uso de agregación
 *param: objeto de tipo Arma e int del índice en el que irá el 
 *arma en el arreglo
 *return
 */

void Sobreviviente::agregaArma(Arma weapon,int indice){
    armas[indice] = weapon;
    cout << armas[indice].getNombre() << "ahora en el inventario" << 
        endl;
}

/**
 *Dependiendo del tipo de arma o item es la cantidad de daño
 *y si se usa un arma, se le resta munición
 *Usa el método recibeAtaque() del infectado 
 *param: apuntador de tipo Jugador
 *return
 */
void Sobreviviente::ataque(Jugador * infected){
    if (getInvSelec() == 2){
        cout << "entra" << endl;
        if (getItems(0) == "Bomba"){
            infected->recibeAtaque(70.5);
        }
        else if (getItems(0) == "Molotov"){
            for (int i = 0;i < 3;i++){
                infected->recibeAtaque(25.5);
            }
        }
        setItems("-", 2);
        if (infected->getVida() <= 0){
            setInfKilled(getInfKilled() + 1);
            cout << getNombre() << " mató a " << 
                infected->getNombre() << endl;
        }
    }
    else{
        if (armas[getInvSelec()].getAmmoTotal() > 0){
            if (armas[getInvSelec()].getAmmoDisp() > 0) {
                cout << "BOOM!\n" << getNombre();
                armas[getInvSelec()].disparo();
                if (armas[getInvSelec()].getNombre() == "Pistola"){
                    infected->recibeAtaque(30.5);
                }
                else if (armas[getInvSelec()].getNombre() == "Magnum"){
                    infected->recibeAtaque(80.5);
                }
                else if (armas[getInvSelec()].getNombre() == "Rifle"){
                    infected->recibeAtaque(90.5);
                }
                else if (armas[getInvSelec()].getNombre() == "Escopeta"){
                    infected->recibeAtaque(100.0);
                }
                if (infected->getVida() <= 0){
                    setInfKilled(getInfKilled() + 1);
                    cout << getNombre() << " mató a " << 
                        infected->getNombre() << endl;
                }
            }
            else {
                if (getBot() == false){
                    cout << "Debes recargar" << endl;
                    cout << getNombre() << ":";
                }
                else{
                    cout << getNombre() << ":";
                    armas[getInvSelec()].recargar();
                }
            }
        }
        else{
            if (getBot() == false){
                cout << "Ya no tienes munición\n" << endl;
            }
            else{
                setInvSelec(2);
            }
        }
        cout << "Ammo: " << armas[getInvSelec()].getAmmoDisp() << endl;
    }
}


/**
 *Si la vida es mayor a 0, entonces le resta el daño, si esta es menor o 
 *igual a 30, imprime el nombre del sobreviviente que esté muriendo, 
 *si no, imprime que ha muerto y que puede ser revivido.
 *param: float (danio)
 *No devuelve nada.
 */
void Sobreviviente::recibeAtaque(float danio){
    cout << getVida() << endl;
    if (getVida() > 0){
        setVida(getVida() - danio);
        cout << getNombre() << " -" << danio <<  " vida = " << 
            getVida() << endl;
        if (getVida() <= 30 && getVida() > 10){
            cout << getNombre() << " debe curarse." << endl;
        }
        else if (getVida() <= 10){
            cout << getNombre() << " está muriendo." << endl;
            setInvSelec(2);
        }
    }
    else{
        setVida(0);
        cout << getNombre() << " ha muerto.\nSi tienes un desfibrilador
            puedes revivirlo." << endl;
    }
}

/**
 *Se imprime un mensaje diferente dependiendo de si el sobreviviente se 
 *cura a sí mismo o a alguien más, después se le agrega el x% de la 
 *vida que le falta, se muestra la vida que tiene después de ser curado 
 *y al sobreviviente que curó se le cambia el item "x" por "-".
 *param: apuntador de tipo Jugador.
 *return
 */
void Sobreviviente::curar(Jugador* survivor, string itm){
    if (getNombre() == survivor->getNombre()){
        if (itm == "Botiquín"){
            cout << getNombre() << " se está curando" << endl;
            setVida( getVida() + (100.0 - getVida()) * 0.8);
            cout << getNombre() << " " << getVida() << " vida" << endl;
            setItems("-", 1);
        }
        else if (itm == "Pastillas"){
            cout << getNombre() << " tomó pastillas" << endl;
            setVida( getVida() + (100.0 - getVida()) * 0.5);
            cout << getNombre() << " " << getVida() << " vida" << endl;
            setItems("-", 2);
        }
        else if (itm == "Adrenalina"){
            cout << getNombre() << " se inyectó adrenalina" << endl;
            setVida( getVida() + (100.0 - getVida()) * 0.25);
            cout << getNombre() << " " << getVida() << " vida" << endl;
            setItems("-", 2);
        }
        else if (itm == "Desfibrilador"){
            cout << "Sólo puedes usar un desfibrilador en tus compañeros." << 
                endl;
        }
        else{
            cout << "No tienes ningún item de Salud" << endl;
        }
    }
    else{
        if (itm == "Botiquín"){
            cout << getNombre() << " curó a " << survivor->getNombre() << 
                endl;
            survivor->setVida( survivor->getVida() + 
                (100.0 - survivor->getVida()) * 0.8);
            cout << survivor->getNombre() << " " << 
                survivor->getVida() << " vida" << endl;
            setItems("-", 1);
        }
        else if (itm == "Pastillas"){
            cout << getNombre() << " le dio pastillas a " << 
                survivor->getNombre() << endl;
            survivor->setItems("Pastillas", 2);
        }
        else if (itm == "Adrenalina"){
            cout << getNombre() << " le dio adrenalina a " << 
                survivor->getNombre() << endl;
            survivor->setItems("Adrenalina", 2);
        }
        else if (itm == "Desfibrilador"){
            if (survivor->getVida() <= 0){
                cout << getNombre() << " revivió a " << 
                    survivor->getNombre() << endl;
                survivor->setVida(50.0);
                cout << survivor->getNombre() << " " << 
                    survivor->getVida() << " vida" << endl;
                setItems("-", 1);
            }
            else{
                cout << "Tranqui, " << survivor->getNombre() << 
                    " sigue viv@" << endl;
            }
        }
        else{
            cout << "No tienes ningún item de Salud" << endl;
        }
            
    }
}


//Declaración de clase Infectado que deriva de Jugador
class Infectado:public Jugador{
    //Declaración de los métodos
public:
    Infectado():Jugador("Infectado Común",50.0,true){}
    Infectado(string name, float health):Jugador(name,health,true){}
    void ataque(Jugador*);
    void recibeAtaque(float);
};

/**
 *Uso de Sobreescritura
 *param: apuntador de tipo Jugador, usa el método
 *recibeAtaque() que recibe la cantidad de daño (float).
 *return
*/
void Infectado::ataque(Jugador* survivor){
    survivor->recibeAtaque(5.0);
}

/**
 *Si la vida del infectado es mayor a 0, entonces le resta
 *el daño, si no, se usa el setter para que su vida sea
 *igual a 0
 *param: float (danio)
 *return
 */
void Infectado::recibeAtaque(float danio){
    if (getVida() > 0){
        setVida(getVida() - danio);
        cout << "Infectado " << getNombre() << " -" << danio <<  " vida." << endl;
    }
    else {
        setVida(0);
    }
}

//Declaración de clase InfectadoEspecial que deriva de Jugador
class InfectadoEspecial:public Jugador{
    //Declaración de métodos
public:
    InfectadoEspecial();
    InfectadoEspecial(string,float);
    void ataque(Jugador*);
    void recibeAtaque(float);
};

InfectadoEspecial::InfectadoEspecial():Jugador("Jockey",100.0,true){}

InfectadoEspecial::InfectadoEspecial(string name,float health):Jugador(name,health,true){}

/**
 *Uso de sobreescritura
 *Dependiendo del tipo de infectado es el daño que hará y 
 *el mensaje que imprimirá
 *param: apuntador de tipo Jugador
 *return
 */
void InfectadoEspecial::ataque(Jugador* survivor){
    if (getNombre() == "Jockey"){
        cout << "Jockey ha montado a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(15.5);
    }
    else if (getNombre() == "Boomer"){
        cout << getNombre() << " explotó y salpicó a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(0.5);
    }
    else if (getNombre() == "Spitter"){
        cout << getNombre() << " le ha escupido a" << endl;
        survivor->recibeAtaque(25.5);
    }
    else if (getNombre() == "Charger"){
        cout << getNombre() << " está atacando a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(35.5);
    }
    else if (getNombre() == "Hunter"){
        cout << getNombre() << " está atacando a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(45.5);
    }
    else if (getNombre() == "Smoker"){
        cout << getNombre() << " ha atrapado a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(55.5);
    }
    else if (getNombre() == "Witch"){
        cout << getNombre() << " está atacando a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(65.5);
    }
    else if (getNombre() == "Tank"){
        cout << getNombre() << " ha aventado a " << survivor->getNombre() << endl;
        survivor->recibeAtaque(75.5);
    } 
}

/**
 *Si la vida del infectado especial es mayor a 0, entonces le resta
 *el daño, si no, se usa el setter para que su vida sea igual a 0
 *param: float (danio)
 *return
 */
void InfectadoEspecial::recibeAtaque(float danio){
    if (getVida() > 0){
        setVida(getVida() - danio);
        cout << getNombre() << " -" << danio <<  " vida." << endl;
    }
    else {
        setVida(0);
    }
}

#endif /* JUGADOR_H */
