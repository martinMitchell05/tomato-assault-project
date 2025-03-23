#ifndef PU_MODDISPARO_H
#define PU_MODDISPARO_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "prota.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "powerup.h"

class pu_modDisparo : public powerup {

public:
	pu_modDisparo(Vector2u tam_resol);
	void aplicar(prota &p, esc_partida &ep) override;
};

#endif

