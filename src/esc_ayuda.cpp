#include "esc_ayuda.h"
#include "esc_inic.h"
#include <SFML/System/Time.hpp>

esc_ayuda::esc_ayuda(Time x_min, Vector2u tam_resol) {
	//Configuraci�n imagen que aparece al iniciar la escena de ayuda
	fondo.loadFromFile("textures/fondoAyuda.png");
	spr_fondo.setTexture(fondo);
	spr_fondo.setColor({255,255,255});
	spr_fondo.setOrigin((fondo.getSize().x/2), (fondo.getSize().y/2));
	spr_fondo.setPosition(tam_resol.x/2, tam_resol.y/2);
	spr_fondo.setScale(float(tam_resol.x)/fondo.getSize().x,float(tam_resol.y)/fondo.getSize().y);
	
	//La m�sica continua desde la escena anterior
	beat_F.openFromFile("sounds/beat_1.ogg");
	beat_F.play();
	beat_F.setPlayingOffset(x_min);
	beat_F.setVolume(25.0);
	beat_F.setLoop(true);
	
	//Se configura el bot�n para volver al men�
	b_volver.loadFromFile("textures/volver.png");
	spr_volver.setTexture(b_volver);
	spr_volver.setOrigin(0,b_volver.getSize().y);
	spr_volver.setPosition(80,tam_resol.y-30);
	spr_volver.setScale(tam_resol.x/1280.0 * 0.65,tam_resol.y/720.0 * 0.65);
}


void esc_ayuda::actualizar (RenderWindow & w, juego & j) {
	//Despues del tiempo de espera se habilita el uso del bot�n
	if (t_espera_inic.getElapsedTime().asMilliseconds() > 300 ){
		FloatRect f1 = spr_volver.getGlobalBounds();
		if (f1.contains(Mouse::getPosition(w).x, Mouse::getPosition(w).y)) {
			if(Mouse::isButtonPressed(Mouse::Left)) {
				Time min2 = beat_F.getPlayingOffset();
				beat_F.stop();
				j.cambiarEsc(new esc_inic(w.getSize(), min2));
			}
		}
	}
}


void esc_ayuda::dibujar (RenderWindow & w, juego & j) {
	//Limpia la pantalla y dibuja la imagen de fondo y el bot�n
	w.clear(Color(0,0,0));
	w.draw(spr_fondo);
	w.draw(spr_volver);
}


