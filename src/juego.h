#ifndef JUEGO_H
#define JUEGO_H
#include "escena.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "InputBox.h"
#include <string>
using namespace std;
using namespace sf;

class escena;

class juego {
	escena *esc_en_pant, *esc_prox = nullptr;
	RenderWindow vent;
	
public:
	juego(escena *prim, Vector2u tam_resol);
	void jugar();
	void cambiarEsc(escena *camb);
	~juego();
};

#endif

