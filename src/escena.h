#ifndef ESCENA_H
#define ESCENA_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "juego.h"
using namespace sf;
class juego;


//Clase madre de las escenas 
class escena {
public: 
	virtual void actualizar(RenderWindow &w, juego &j) = 0;
	virtual void dibujar(RenderWindow &w, juego &j) = 0;
	virtual void procesarEvento(Event &e) {};
	virtual void esperarTiempo() {};
};

#endif
