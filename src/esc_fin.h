#ifndef ESC_FIN_H
#define ESC_FIN_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>
#include "escena.h"
#include <string>
#include "Maneja_Punt.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
using namespace std;
using namespace sf;

class esc_fin : public escena {
	Font fuente;
	Text fin,resul,paso_guard, guard_exi, entradaNombre;
	float tiempo_act;
	
	Maneja_Punt tabla;
	Music beat_2;
	InputText nom_jug;
	string nom;
	bool hay_que_cambiar = true;
	Clock t_espera_inic;
	
	Texture fondo, b_volverMenu, b_volverJugar;
	Sprite spr_fondo, spr_volMen, spr_volJug;
public:
	esc_fin(string tiem_fin, Vector2u tam_resol);
	void actualizar(RenderWindow &w,juego &j) override;
	void dibujar(RenderWindow &w, juego &j) override;
	void procesarEvento(Event &e);
};

#endif

