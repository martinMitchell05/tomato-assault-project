#include "pu_vida.h"

pu_vida::pu_vida(Vector2u tam_resol) : powerup(tam_resol, "textures/powerup_vida.png") {

}

//Metodo virtual de powerup :
void pu_vida::aplicar(prota &p, esc_partida &ep) {
	//Metodo del prota (agrega una vida al jugador)
	p.cambiarVida(true);
}

