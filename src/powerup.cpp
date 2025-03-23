#include "powerup.h"

powerup::powerup(Vector2u tam_resol, string textura) {
	tex_pu.loadFromFile(textura);
	spr_pu.setTexture(tex_pu);
	spr_pu.setOrigin(0,0);
	//Se calculan valores randoms en x e y, seg�n la resoluci�n y el tama�o de la textura
	int tam_x = rand()%(tam_resol.x-tex_pu.getSize().x), tam_y = rand()%(tam_resol.y-tex_pu.getSize().y);
	spr_pu.setPosition(tam_x,tam_y); //Se posiciona el powerup usando esos valores aleatorios
	spr_pu.setScale(tam_resol.x/1280.0,tam_resol.y/720.0); //Se escala el sprite seg�n la resoluci�n de pantalla
};

Vector2f powerup::posicion() {
	//Vector2f que se utilizar� para la funci�n de colisi�n
	Vector2f tam(tex_pu.getSize().x/2,tex_pu.getSize().y/2);
	return spr_pu.getPosition()+tam;
}

void powerup::dibujar(RenderWindow &w) {
	w.draw(spr_pu);
}
