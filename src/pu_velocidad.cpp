#include "pu_velocidad.h"

pu_velocidad::pu_velocidad(Vector2u tam_resol) : powerup(tam_resol, "textures/zapatillas_ligeras.png") {

}

//Metodo virtual de powerup :
void pu_velocidad::aplicar(prota &p, esc_partida &ep) {
	//Metodo del prota (modifica la velocidad de movimiento)
	p.cambiarVeloc();
}
