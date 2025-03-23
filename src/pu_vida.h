#ifndef PU_VIDA_H
#define PU_VIDA_H
#include "powerup.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "esc_partida.h"

class pu_vida : public powerup {

public:
	pu_vida(Vector2u tam_resol);
	void aplicar(prota &p, esc_partida &ep) override;
};

#endif

