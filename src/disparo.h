#ifndef DISPARO_H
#define DISPARO_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

class disparo {
	CircleShape bala;
	Vector2f velocidad;
	Vector2u tam_pant;
	float vel_segun_pant;
public:
	disparo(Vector2f pos, Vector2f dir, Vector2u tam_resol);
	void actualizar();
	Vector2f posicion();
	Vector2u resol();
	void dibujar(RenderWindow &w);
};

#endif

