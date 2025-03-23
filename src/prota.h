#ifndef PROTA_H
#define PROTA_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "disparo.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

using namespace sf;

class prota {
	Texture tex_prota,tex_prota_2v,tex_prota_1v ,tex_prota_0v;
	Sprite spr_prota;
	
	Texture text_0vida, text_1vida, text_2vida, text_3vida;
	Sprite spr_contvida;
	int vidas = 3;
	
	float veloc = 1.2;
	Clock tiempo_pow_act;
	bool por_corregir = false;
	int vel_disparo = 300;
	float vel_segun_pant;
	
	Clock tiempo_tiro;
	Sound m_disparo;
	SoundBuffer m_son_disp;
	Vector2u tam_pant;
public: 
	prota(Vector2u tam_resol);
	void actualizar(RenderWindow &w);
	bool hayQueDisparar();
	disparo salioDisparo();
	Vector2f posicion();
	void dibujar(RenderWindow &w);
	void cambiarVida(bool mod);
	int verVidas();
	void cambiarVeloc();
	void cambiarV_Disparo();
	float media_ajus_tam();
	~prota();
};

#endif

