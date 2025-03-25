#include <SFML/Window/Keyboard.hpp>
#include "esc_inic.h"
#include "esc_partida.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include "esc_tabla.h"
#include "esc_ayuda.h"

using namespace std;

esc_inic::esc_inic(Vector2u tam_resol, Time x_min) {
	//Configuraci�n imagen que aparece al iniciar el juego
	fondo.loadFromFile("textures/Fondo_ini.png");
	spr_fondo.setTexture(fondo);
	spr_fondo.setColor({255,255,255,90});
	spr_fondo.setOrigin((fondo.getSize().x/2), (fondo.getSize().y/2));
	spr_fondo.setPosition(tam_resol.x/2, tam_resol.y/2);
	spr_fondo.setScale(float(tam_resol.x)/fondo.getSize().x,float(tam_resol.y)/fondo.getSize().y);
	
	//Tipograf�a utilizada en el menu de inicio
	fuente.loadFromFile("fonts/DragonSlayer.ttf");
	//Configuraci�n de la m�sica del men�
	beat1.openFromFile("sounds/beat_1.ogg");
	beat1.play();
	beat1.setPlayingOffset(x_min);
	beat1.setLoop(true);
	beat1.setVolume(25.0);
	
	//Configuraci�n de los botones jugar, puntajes, ayuda y salir 
	b_jugar.loadFromFile("textures/jugar.png");
	spr_jugar.setTexture(b_jugar);
	spr_jugar.setOrigin(0,0);
	spr_jugar.setPosition(60, tam_resol.y/2);
	spr_jugar.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	b_ptajes.loadFromFile("textures/verpuntajes.png");
	spr_ptajes.setTexture(b_ptajes);
	spr_ptajes.setOrigin(0,0);
	spr_ptajes.setPosition(60, tam_resol.y/2 + 80);
	spr_ptajes.setScale(tam_resol.x/1280.0 * 0.65, tam_resol.y/720.0 * 0.65);
	
	b_ayuda.loadFromFile("textures/ayuda.png");
	spr_ayuda.setTexture(b_ayuda);
	spr_ayuda.setOrigin(0,0);
	spr_ayuda.setPosition(60, tam_resol.y/2+130);
	spr_ayuda.setScale(tam_resol.x/1280.0 * 0.65,tam_resol.y/720.0 * 0.65);
	
	b_salir.loadFromFile("textures/saliralesc.png");
	spr_salir.setTexture(b_salir);
	spr_salir.setOrigin(0,0);
	spr_salir.setPosition(60, tam_resol.y/2 + 185);
	spr_salir.setScale(tam_resol.x/1280.0 * 0.65,tam_resol.y/720.0 * 0.65);
	
	//Configuraci�n del t�tulo
	titulo.setFont(fuente);
	titulo.setPosition(tam_resol.x/2 + 10,tam_resol.y/2 - 170);
	titulo.setCharacterSize(50);
	titulo.setOrigin(235.0,25.0);
	titulo.setString("Tomato Assault");
	titulo.setFillColor({0,191,255});
	titulo.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
}

void esc_inic :: actualizar(RenderWindow &w,juego &j) {
	
	//Cuando el tiempo de la creaci�n de pantalla haya sido mayor que 300 se podra comenzar a presionar los botones
	if (t_espera_inic.getElapsedTime().asMilliseconds() > 300 ){
		//Se obtiene el posicionamiento en pantalla de la imagen del bot�n
		FloatRect f1 = spr_jugar.getGlobalBounds();
		//Si el mouse se encuentra dentro de la imagen y si se presiona el click izquierdo en el, entonces la m�sica se detiene y cambia de escena
		if (f1.contains(Mouse::getPosition(w).x, Mouse::getPosition(w).y)) {
			if(Mouse::isButtonPressed(Mouse::Left)) {
				beat1.stop();
				j.cambiarEsc(new esc_partida(w.getSize()));
			}
		}
		
		FloatRect f2 = spr_salir.getGlobalBounds();
		if (f2.contains(Mouse::getPosition(w).x, Mouse::getPosition(w).y)) {
			if(Mouse::isButtonPressed(Mouse::Left)) {
				beat1.stop();
				w.close();
			}
		}
		
		FloatRect f3 = spr_ptajes.getGlobalBounds();
		if (f3.contains(Mouse::getPosition(w).x, Mouse::getPosition(w).y)) {
			if(Mouse::isButtonPressed(Mouse::Left)) {
				Time min = beat1.getPlayingOffset();
				beat1.stop();
				j.cambiarEsc(new esc_tabla(min,w.getSize()));
			}
		}
		
		FloatRect f4 = spr_ayuda.getGlobalBounds();
		if (f4.contains(Mouse::getPosition(w).x, Mouse::getPosition(w).y)) {
			if(Mouse::isButtonPressed(Mouse::Left)) {
				Time min = beat1.getPlayingOffset();
				beat1.stop();
				j.cambiarEsc(new esc_ayuda(min,w.getSize()));
			}
		}
	}
}

void esc_inic :: dibujar(RenderWindow &w, juego &j){
	//Se limpia la pantalla y se dibujan los elementos creados
	w.clear(Color(30,30,30));
	w.draw(spr_fondo);
	w.draw(titulo);
	w.draw(spr_ayuda);
	w.draw(spr_jugar);
	w.draw(spr_salir);
	w.draw(spr_ptajes);
}

