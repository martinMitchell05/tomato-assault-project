#include "disparo.h"

disparo::disparo(Vector2f pos, Vector2f dir, Vector2u tam_resol) {
	//Se crea y configura el disparo 
	tam_pant = tam_resol;
	bala.setPosition(pos);
	bala.setRadius(2);
	bala.setOrigin(2,2);
	bala.setFillColor({0,0,0});
	velocidad = dir*5.f;
	//El tamaño y velocidad de la bala se ajustan al tamaño de la pantalla
	bala.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	vel_segun_pant = (tam_resol.x/1280.0 + tam_resol.y/720.0)/2;
}

void disparo::actualizar(){
	//Mueve la bala por la pantalla y corrige la velocidad según la resolución
	bala.move(velocidad * vel_segun_pant);
}

Vector2f disparo::posicion(){
	//Retorna la posicion de la bala
	return bala.getPosition();
}

Vector2u disparo::resol(){
	//Retorna el tamaño de la pantalla
	return tam_pant;
}


void disparo::dibujar(RenderWindow &w){
	//Dibuja el disparo
	w.draw(bala);
}
