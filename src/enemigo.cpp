#include "enemigo.h"
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
using namespace std;

Vector2f zonaSpawn(Vector2f pos_prota, Vector2u tam_resol){
	//Calcula un valor cualquiera de "x" dentro del rango de la pantalla y determina el valor de "y" dependiendo la posicion del jugador
	float valorRx = rand()%tam_resol.x;
	float valorRy ;
	int dsa;
	//Diferenciamos si el valor de x esta en un rango de 200 pixeles alrededor del protagonista o no
	if(valorRx > pos_prota.x - 100 and valorRx < pos_prota.x + 100){
		//Si el protagonista esta en el borde superior de la pantalla, "y" toma todos los valores mayores hasta el borde inferior
		if(pos_prota.y - 100 <= 0){
			dsa = (tam_resol.y) - pos_prota.y;
			valorRy = (rand()%dsa)+(pos_prota.y+100);
		}
		else if(pos_prota.y > 100 and pos_prota.y<(tam_resol.y-100)){ //Si el protagonista esta alejado 100 pixeles de cada borde se spawnean enemigos arriba y abajo
			dsa=pos_prota.y-100;
			float valorSumable = rand()%dsa;
			if(rand()%2 == 0){
				valorRy = valorSumable;
			}else{
				dsa=tam_resol.y-(pos_prota.y+100);
				valorSumable=rand()%dsa;
				valorRy = (pos_prota.y+100) + valorSumable;
			}
		}
		//Si el protagonista esta en el borde inferior de la pantalla, spawnean enemigos solo arriba
		else if(pos_prota.y + 100 >= tam_resol.y){
			dsa= pos_prota.y-100;
			valorRy=rand()%dsa;
		}
	}else{
		valorRy = rand()%tam_resol.y;
	}
	//Vector de coordenadas donde aparecen el enemigo
	Vector2f coords(valorRx,valorRy);
	return coords;
}

enemigo::enemigo(Texture &tex_enem,Vector2f pos_prota, Vector2u tam_resol) {
	//Se crea el sprite del enemigo
	spr_enem.setTexture(tex_enem);
	spr_enem.setPosition(zonaSpawn(pos_prota, tam_resol));
	auto tam = tex_enem.getSize();
	spr_enem.setOrigin(tam.x/2,tam.y/2);
	//Se escala el tamaño del enemigos segun la resolucion de la pantalla
	spr_enem.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	//Se configura la velocidad segun la resolucion de la pantalla
	vel_segun_pant = (tam_resol.x/1280.0 + tam_resol.y/720.0)/2;
}

void enemigo::actualizar(Vector2f pos_prota){
	//Se calcula un triangulo en el que la hipotenusa es la distancia entre el enemigo y el protagonista y el cateto opuesto es la distancia en "y" en ambos
	Vector2f pos_enem = spr_enem.getPosition();
	float hip = sqrt(pow(pos_prota.x-pos_enem.x,2) + pow(pos_prota.y-pos_enem.y,2));
	float cat = abs(pos_prota.y-pos_enem.y);
	float ang = (asin(cat/hip));
	//primer cuadrante (pensando al personaje en el centro)
	if(pos_enem.x>pos_prota.x and pos_enem.y<pos_prota.y){ 
		velocidad = {-cos(ang),sin(ang)};
	}
	//segundo cuadrante (pensando al personaje en el centro)
	if(pos_enem.x<pos_prota.x and pos_enem.y<pos_prota.y){ 
		velocidad = {cos(ang),sin(ang)};
	}
	//tercer cuadrante (pensando al personaje en el centro)
	if(pos_enem.x<pos_prota.x and pos_enem.y>pos_prota.y){ 
		velocidad = {cos(ang),-sin(ang)};
	}
	//cuarto cuadrante (pensando al personaje en el centro)
	if(pos_enem.x>pos_prota.x and pos_enem.y>pos_prota.y){ 
		velocidad = {-cos(ang),-sin(ang)};
	}
	//Se mueve al enemigo segun la velocidad calculada antes multiplicada por una constante para ser mas rapido que el protagonista y se ajusta segun la resolucion de la pantalla
	spr_enem.move(velocidad*1.5f*vel_segun_pant);
	
}

Vector2f enemigo::posicion(){
	//Retorna la posicion del enemigo
	return spr_enem.getPosition();
}

float enemigo::media_ajus_tam() {
	//Retorna el factor de correccion segun la resolucion
	return vel_segun_pant;
}

void enemigo::dibujar(RenderWindow &w){
	//Dibuja al enemigo
	w.draw(spr_enem);
}

enemigo::~enemigo() {
	
}


