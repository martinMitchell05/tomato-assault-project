#ifndef PU_GRANADA_H
#define PU_GRANADA_H
#include "powerup.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "esc_partida.h"
#include <SFML/Graphics/RenderWindow.hpp>

class pu_granada : public powerup {
public:
	pu_granada(Vector2u tam_resol);
	void aplicar(prota &p, esc_partida &ep) override;

};

#endif

