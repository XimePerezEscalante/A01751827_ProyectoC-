# Proyecto Left 4 Dead

<h2>CONTEXTO</h2>

Este proyecto se basará en su totalidad en los juegos Left 4 Dead y Left 4 Dead 2, así que se busca recrearlo (en un menor nivel claro).
Left 4 Dead y Left 4 Dead 2 están ubicados en un apocalipsis zombie, donde hay 4 sobrevivientes respectivamente que tienen que luchar contra las hordas de infectados,los cuales se dividen en infectados normales y especiales. El jugador puede escoger a uno de los 4 sobrevivientes; puede tener dos armas, un item extra que pueden encontrar en el mapa y otros dos para curarse, los cuales pueden ser un botiquín, adrenalina o pastillas. Así que en total su inventario cuenta con 5 objetos.
En este programa se crearon 6 clases: Jugador, Sobreviviente, Infectado, Infectado Especial, Arma y Mapa. Jugador es una clase abstracta de la cual Sobreviviente, Infectado e
Infectado Especial derivan, poniendo en práctica el concepto de herencia; de igual manera se hace uso de composición en la clase Mapa, la cual crea a los infectados y al equipo de
sobrevivientes, y de agregración entre la clase Arma y Jugador, al igual que al usuario con el mapa.
Además, se usa el polimorfismo dentro de la clase Mapa en donde se simula una pequeña partida en la que apuntadores de tipo Jugador interactúan entre sí mismos usando 
sobreescritura y funciones de tipo virtual.

<h2>CÓMO DEJARÍA DE FUNCIONAR EL PROGRAMA</h2>
Esto ocurriría en caso de no incluir los headers en el main, tener errores de sintaxis, no programar las clases de manera correcta y/o no revisar las consideraciones.

<h2>FUNCIONALIDAD</h2>
El programa simula una partida en la que se crea un arreglo con apuntadores de tipo Jugador que apuntan tanto a Sobreviviente, como a Infectado e Infectado Especial. En ella,
pueden atacarse unos con otros o utilizar los distintos items disponibles. La partida acaba cuando el usuario muere.

<h2>CONSIDERACIONES</h2>
El programa solo corre en la consola y esta hecho con c++ standard por lo que corre en todos los sistemas operativos. Compilar con: "g++ Jugador.h main.cpp". Correr en linux: "/a.out". Correr en windows: "a.exe".

<h2>CORRECCIONES</h2>
Se agregaron los casos en los que el programa dejaría de funcionar, se corrigió el formato del código y se implementó polimorfismo en la clase Mapa, donde se creó un sólo arreglo
de apuntadores de tipo Jugador.

