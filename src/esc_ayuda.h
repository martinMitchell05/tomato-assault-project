#ifndef ESC_AYUDA_H
#define ESC_AYUDA_H
#include "escena.h"
#include <SFML/Audio/Music.hpp>

class esc_ayuda : public escena {
	Music beat_F;
	Texture fondo, b_volver;
	Sprite spr_fondo, spr_volver;
	Clock t_espera_inic;
public:
	esc_ayuda(Time x_min, Vector2u tam_resol);
	void actualizar (RenderWindow & w, juego & j)override;
	void dibujar (RenderWindow & w, juego & j)override;
};

#endif

