#ifndef ESC_INIC_H
#define ESC_INIC_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>
#include "escena.h"
#include <SFML/System/Clock.hpp>
using namespace sf;

class esc_inic : public escena{
	Font fuente;
	Text titulo;
	Music beat1;
	Texture fondo,b_jugar, b_salir, b_ptajes, b_ayuda;
	Sprite spr_fondo, spr_jugar, spr_salir, spr_ptajes, spr_ayuda;
	Clock t_espera_inic;
public:
	esc_inic(Vector2u tam_resol, Time x_min);
	void actualizar(RenderWindow &w,juego &j) override;
	void dibujar(RenderWindow &w, juego &j) override;
};

#endif
