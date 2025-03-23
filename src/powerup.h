#ifndef POWERUP_H
#define POWERUP_H
#include "prota.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "esc_partida.h"
class esc_partida;


//Clase madre de los powerups
class powerup {
public:
	powerup(Vector2u tam_resol, string textura);
	virtual void aplicar(prota &p, esc_partida &ep) =0;
	void dibujar(RenderWindow &w);
	Vector2f posicion();
private:
	Texture tex_pu;
	Sprite spr_pu;
};

#endif

