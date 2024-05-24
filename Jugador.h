#ifndef Jugador_h
#define Jugador_h

#include <iostream>
using namespace std;

//Declaración de clase Jugador
class Jugador{
    //Declaración de los atributos
private:
    string nombre;
    float vida;
    //Declaración de los métodos
public:
    Jugador();
    Jugador(string,float); //Sobrecarga
    void ataque(Jugador);
    void recibeAtaque(float);
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


/**
 *Recibe un objeto de tipo Jugador, usa el método recibeAtaque() que recibe la cantidad de daño (float).
 *Imprime el nombre del jugador que atacó, así como al atacado.
 *No devuelve nada.
*/
void Jugador::ataque(Jugador player){
    player.recibeAtaque(5.0);
    cout << getNombre() << " atacó a " << player.getNombre() << endl;
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
    }
    else{
        cout << getNombre() << " ha muerto." << endl;
    }
}

//Declaración de clase Sobreviviente que deriva de Jugador
class Sobreviviente:public Jugador{
    //Declaración de los métodos
public:
    Sobreviviente():Jugador("Bot",100.0){}
    Sobreviviente(string name,float health):Jugador(name,health){} //Sobrecarga
    Sobreviviente(string name):Jugador(name,100.0){} //Sobrecarga
    void ataque(Jugador); //Uso de sobreescritura
    void recibeAtaque(float); //Uso de sobreescritura
 };

 /**
 *Uso de sobreescritura
 *Recibe un objeto de tipo Jugador
 *Usa el método recibeAtaque() del infectado
 *Dependiendo del tipo de arma y munición, es la cantidad de daño
 *y se le resta munición al arma ¡¡¡-pero todavía no están esas clases-!!!
 *
 */
void Sobreviviente::ataque(Jugador infected){
    infected.recibeAtaque(20.0);
}

/**
 *Uso de sobreescritura
 *Recibe la variable danio (float).
 *Si la vida es mayor a 0, entonces le resta el daño, si esta es menor o igual a 30, imprime el nombre del sobreviviente
 *que esté muriendo, si no, imprime que ha muerto y que puede ser revivido.
 *No devuelve nada.
 */
void Sobreviviente::recibeAtaque(float danio){
    if (getVida() > 0){
        setVida(getVida() - danio);
        cout << getNombre() << " -" << danio <<  " vida." << endl;
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
    void ataque(Sobreviviente); //Uso de sobrecarga
};

/**
*Uso de sobrecarga
*Recibe un objeto de tipo Sobreviviente, usa el método recibeAtaque() que recibe la cantidad de daño (float).
*No devuelve nada.
*/

void Infectado::ataque(Sobreviviente survivor){
    cout << getNombre() << " atacó a " << survivor.getNombre() << endl;
    survivor.recibeAtaque(5.0);
}

//Declaración de clase InfectadoEspecial que deriva de Infectado
class InfectadoEspecial:public Infectado{
    //Declaración de los atributos
private:
    string habilidad;
    //Declaración de los métodos
public:
    InfectadoEspecial();
    InfectadoEspecial(string,string,float); //Sobrecarga
    void ataque(Sobreviviente); //Uso de sobreescritura
    string getHabilidad();
    void setHabilidad(string);
};

InfectadoEspecial::InfectadoEspecial():Infectado("Jockey",100.0){
    habilidad = "montar y atacar al jugador hasta que muere.";
}

InfectadoEspecial::InfectadoEspecial(string hab,string name,float health):Infectado(name,health){
    habilidad = hab;
}

/**
 *Uso de sobreescritura
 *Recibe un objeto de tipo Sobreviviente
 *Dependiendo del tipo de infectado es el daño que hará (todavía no está hecho) y el mensaje que imprimirá.
 *No devuelve nada
 */
void InfectadoEspecial::ataque(Sobreviviente survivor){
    if (getNombre() == "Jockey"){
        cout << "Jockey ha montado a " << survivor.getNombre() << endl;
    }
    else if (getNombre() == "Boomer"){
        cout << getNombre() << " ha atacado a " << survivor.getNombre() << endl;
    }
    else if (getNombre() == "Spitter"){
        cout << getNombre() << " le ha escupido a " << survivor.getNombre() << endl;
    }
    else if (getNombre() == "Charger"){
        cout << getNombre() << " está atacando a " << survivor.getNombre() << endl;
    }
    else if (getNombre() == "Hunter"){
        cout << getNombre() << " está atacando a " << survivor.getNombre() << endl;
    }
    else if (getNombre() == "Smoker"){
        cout << getNombre() << " ha atrapado a " << survivor.getNombre() << endl;
    }
    else if (getNombre() == "Witch"){
        cout << getNombre() << " está atacando a " << survivor.getNombre() << endl;
    }
    else if (getNombre() == "Tank"){
        cout << getNombre() << " ha aventado a " << survivor.getNombre() << endl;
        survivor.recibeAtaque(75.5);
    }
    survivor.recibeAtaque(5.0);
}

#endif /* Jugador_h */
