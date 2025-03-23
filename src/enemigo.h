#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

class enemigo {
	Sprite spr_enem;
	Vector2f velocidad;
	float vel_segun_pant;
public:
	enemigo(Texture &tex_enem, Vector2f pos_prota, Vector2u tam_resol);
	void actualizar(Vector2f pos_prota);
	Vector2f posicion();
	float media_ajus_tam();
	void dibujar(RenderWindow &w);
	~enemigo();
};

#endif

