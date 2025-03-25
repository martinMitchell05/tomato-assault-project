#include "pu_granada.h"

pu_granada::pu_granada(Vector2u tam_resol) : powerup(tam_resol, "textures/granada.png") {

}

//Metodo virtual de powerup :
void pu_granada::aplicar (prota & p, esc_partida &ep) {
	//Metodo de escena partida (Elimina a los enemigos cercanos)
	ep.borra_enems();	
}
