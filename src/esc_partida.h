#ifndef ESC_PARTIDA_H
#define ESC_PARTIDA_H
#include "prota.h"
#include "enemigo.h"
#include "disparo.h"
#include <vector>
#include <ctime>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>
#include "escena.h"
#include "powerup.h"

using namespace std;

class powerup;

class esc_partida : public escena {
	prota p1;
	vector<enemigo> enems;
	vector<disparo> p1_disp;
	
	Clock tiempo_vivo;
	Clock tiempo_evitar_colisiones;
	Clock  t_recargar_enems;
	Text t_tiem;
	Font fuente;
	Music batalla;
	Sound s_powerup, s_golpe;
	SoundBuffer sb_powerup, sb_golpe;
	
	Text preparate;
	
	bool inmune=true;
	Texture tex_fondo, tex_escudo;
	Sprite spr_fondo, spr_escudo;
	Texture tex_enem_1 , tex_enem_2, tex_enem_3, tex_enem_4;
	Clock t_espera_inic;
	
	powerup *pow_en_pant = nullptr;
	Clock tiempo_pow_nuevo;
	bool se_puede_agregar = true;
	bool pierde = false;
	
public:
	esc_partida(Vector2u tam_resol);
	void actualizar(RenderWindow &w, juego &j) override;
	void dibujar(RenderWindow &w, juego &j) override;
	void borra_enems();
	void esperarTiempo() override;
	~esc_partida();
};

#endif

