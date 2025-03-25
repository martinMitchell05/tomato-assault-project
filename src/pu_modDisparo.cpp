#include "pu_modDisparo.h"

pu_modDisparo::pu_modDisparo(Vector2u tam_resol) : powerup(tam_resol, "textures/bullet.png") {

}

//Metodo virtual de powerup :
void pu_modDisparo::aplicar(prota &p, esc_partida &ep) {
	//Metodo del prota (Modifica la cadencia de disparo)
	p.cambiarV_Disparo();
}

