#include "juego.h"
#include <SFML/Window/Event.hpp>


juego::juego(escena *p,Vector2u tam_resol) {
	//Creación de la ventana
	VideoMode vm(tam_resol.x,tam_resol.y);
	vent.create(vm,"Tomato Assault");
	vent.setFramerateLimit(60);
	//Guarda la primer escena obtenida 
	esc_en_pant = p;
}

void juego :: jugar(){
	//Bucle principal de eventos
	while(vent.isOpen()){
		Event e;
		while(vent.pollEvent(e)) {
			if(e.type == Event::Closed){
				vent.close();	
			} else {
				esc_en_pant -> procesarEvento(e);
			}
		}
		
		//Actualizacion escena en pantalla
		esc_en_pant->actualizar(this->vent,*this);
		
		//Dibujo escena en pantalla
		esc_en_pant->dibujar(this->vent,*this);
		vent.display();
		esc_en_pant->esperarTiempo();
		
		//Transición de escenas
		if(esc_prox != nullptr){
			delete esc_en_pant;
			esc_en_pant = esc_prox;
			esc_prox = nullptr;
		}
	}
}
//Método para cambiar la escena sin interferir en los procesos que se realizan 
void juego::cambiarEsc(escena *camb){
	esc_prox = camb;
}
//Borra la escena actual del juego
juego::~juego(){
	delete esc_en_pant;
}
