#include "prota.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
using namespace std;

prota::prota(Vector2u tam_resol){
	//Cargar texturas y configurar sprites del protagonista
	tam_pant = tam_resol;
	tex_prota.loadFromFile("textures/prota.png");
	tex_prota_2v.loadFromFile("textures/prota_2vid.png");
	tex_prota_1v.loadFromFile("textures/prota_1vid.png");
	tex_prota_0v.loadFromFile("textures/fantasma.png");
	spr_prota.setTexture(tex_prota);
	spr_prota.setPosition(tam_pant.x/2,tam_pant.y/2);
	spr_prota.setOrigin(35,25);
	spr_prota.setRotation(90);	
	//Se escala el tama�o segun la resolucion en pantalla
	spr_prota.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	//Configuraci�n del sonido de disparo
	m_son_disp.loadFromFile("sounds/burbujita.ogg");
	m_disparo.setBuffer(m_son_disp);
	
	//Cargar texturas y configurar sprites de las vidas 
	text_0vida.loadFromFile("textures/0_vida.png");
	text_1vida.loadFromFile("textures/1_vida.png");
	text_2vida.loadFromFile("textures/2_vidas.png");
	text_3vida.loadFromFile("textures/3_vidas.png");
	spr_contvida.setTexture(text_3vida);
	spr_contvida.setOrigin(text_3vida.getSize().x/2, text_3vida.getSize().y/2);
	spr_contvida.setPosition(100, 35);
	//Se escala el tama�o segun la resolucion en pantalla
	spr_contvida.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	vel_segun_pant = (tam_resol.x/1280.0 + tam_resol.y/720.0)/2;
}

void prota::actualizar(RenderWindow &w){
	//Se obtiene la posici�n del protagonista para calcular los limites de la pantalla y configurar su movimiento
	Vector2f pos_prota = spr_prota.getPosition();
	if(Keyboard::isKeyPressed(Keyboard::W) and pos_prota.y>25){
		//Se multiplica por la velocidad (por defecto = 1) para cambiarla con los powerups y se multiplica por un corrector de velocidad seg�n la resoluci�n
		spr_prota.move(0,-1*veloc*vel_segun_pant);
	}
	if(Keyboard::isKeyPressed(Keyboard::S) and pos_prota.y < (tam_pant.y-20)){
		spr_prota.move(0,1*veloc*vel_segun_pant);
	}
	if(Keyboard::isKeyPressed(Keyboard::D) and pos_prota.x < (tam_pant.x-20)){
		spr_prota.move(1*veloc*vel_segun_pant,0);
	}
	if(Keyboard::isKeyPressed(Keyboard::A) and pos_prota.x>25){
		spr_prota.move(-1*veloc*vel_segun_pant,0);
	}
	
	//Seguimiento del personaje al cursor
	Vector2i posMou = Mouse::getPosition(w);
	Vector2f posPro = spr_prota.getPosition();
	//Se crea un triangulo entre el cursor y el personaje, donde la hipotenusa es la distancia entre ambos y el cateto adyacente la diferencia en y
	float hip = sqrt(pow(posMou.x-posPro.x,2) + pow(posMou.y-posPro.y,2));
	float cat = abs(posMou.y-posPro.y);
	//Se calcula el angulo y se pasa a grados
	float ang = (acos(cat/hip))*180/M_PI;
	//primer cuadrante (pensando al personaje en el centro)
	if(posMou.x>posPro.x and posMou.y<posPro.y){ 
		spr_prota.setRotation(-90+ang);
	}
	//segundo cuadrante (pensando al personaje en el centro)
	if(posMou.x<posPro.x and posMou.y<posPro.y){ 
		spr_prota.setRotation(-90-ang);
	}
	//tercer cuadrante (pensando al personaje en el centro)
	if(posMou.x<posPro.x and posMou.y>posPro.y){ 
		spr_prota.setRotation(90+ang);
	}
	//cuarto cuadrante (pensando al personaje en el centro)
	if(posMou.x>posPro.x and posMou.y>posPro.y){ 
		spr_prota.setRotation(90-ang);
	}
	
	//Volver a sus valores originales los modificados por powerups
	if(tiempo_pow_act.getElapsedTime().asSeconds() > 5 and por_corregir ) {
		veloc = 1;
		vel_disparo = 300;
		por_corregir = false;
	}
}


bool prota::hayQueDisparar(){
	//no deja disparar si el tiempo del tiro anterior fue antes de esa cant de segundos
	if(tiempo_tiro.getElapsedTime().asMilliseconds()<vel_disparo){
		return false;
	}
	//Si detecta el bot�n de disparo reinicia el temporizador para el pr�ximo disparo y retorna true porque hay que disparar
	if (Mouse::isButtonPressed(Mouse::Left)){
		tiempo_tiro.restart();
		return true;
	}
	return false;
}


disparo prota::salioDisparo(){
	//Guardas la posici�n del protagonista, su �ngulo de rotaci�n, se calcula la direcci�n a la que apunta y se crea el disparo
	Vector2f pos = spr_prota.getPosition();
	float ang = spr_prota.getRotation()*M_PI/180;
	Vector2f dir(cos(ang),sin(ang)); 
	disparo c1(pos+20.f*dir,dir,tam_pant);
	m_disparo.play();
	m_disparo.setVolume(70.0);
	return c1;
}

//Metodo que devuelve la posicion del protagonista
Vector2f prota::posicion(){
	return spr_prota.getPosition();
}

//Metodo que dibuja al protagonista y sus vidas
void prota::dibujar(RenderWindow &w){
	w.draw(spr_prota);
	w.draw(spr_contvida);
}

//Metodo para quitar o adicionar una vida al jugador
void prota::cambiarVida(bool mod){
	if(mod){
		++vidas;
	} else {
		--vidas;
	}
	if (vidas==3){
		spr_prota.setTexture(tex_prota);
		spr_contvida.setTexture(text_3vida);
	} else if(vidas == 2){
		spr_prota.setTexture(tex_prota_2v);
		spr_contvida.setTexture(text_2vida);
		} else if(vidas==1){
		spr_prota.setTexture(tex_prota_1v);
		spr_contvida.setTexture(text_1vida);
		} else {
			spr_prota.setTexture(tex_prota_0v);
			spr_prota.setRotation(0);
			spr_contvida.setTexture(text_0vida);
		}
}

//Retorna la cantidad de vidas
int prota::verVidas(){
	return vidas;
}

//Metodo para cambiar de velocidad de movimiento del jugador (utilizado en powerup)
void prota::cambiarVeloc(){
	veloc = 1.6;
	tiempo_pow_act.restart();
	por_corregir = true;
}
//Metodo para cambiar de velocidad de disparo del jugador (utilizado en powerup)
void prota::cambiarV_Disparo() {
	vel_disparo = 150;
	tiempo_pow_act.restart();
	por_corregir = true;
}

//Retorna el factor de correccion de pantalla (utilizado en las funciones de colision)
float prota::media_ajus_tam() {
	return vel_segun_pant;
}

prota::~prota(){
	m_disparo.stop();
}
