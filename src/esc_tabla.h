#ifndef ESC_TABLA_H
#define ESC_TABLA_H
#include "escena.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Maneja_Punt.h"
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace std;
using namespace sf;

class esc_tabla : public escena {
	Text tex_tabla,pto_tabla;
	Font fuente2;
	Maneja_Punt tabla;
	float tiem_jug;
	
	Music beat_F;
	Texture fondo, b_volver;
	Sprite spr_fondo, spr_volver;
	Clock t_espera_inic;
public:
	esc_tabla(Time x_min, Vector2u tam_resol);
	void actualizar(RenderWindow &w,juego &j) override;
	void dibujar(RenderWindow &w, juego &j) override;
};

#endif

