#include "esc_fin.h"
#include <string>
#include "esc_partida.h"
#include <cstring>
#include "esc_inic.h"
using namespace std;



esc_fin::esc_fin(string tiem_fin,Vector2u tam_resol): nom_jug(fuente,20,sf::Color::White) {
	//Guarda el tiempo del jugador
	tiempo_act = stof(tiem_fin);
	
	//Se crea y configura la imagen de fondo
	fondo.loadFromFile("fin.png");
	spr_fondo.setTexture(fondo);
	spr_fondo.setColor({255,255,255,90});
	spr_fondo.setOrigin((fondo.getSize().x/2), (fondo.getSize().y/2));
	spr_fondo.setPosition(tam_resol.x/2, tam_resol.y/2);
	spr_fondo.setScale(float(tam_resol.x)/fondo.getSize().x,float(tam_resol.y)/fondo.getSize().y);
	
	//Configuración de la música de la escena
	beat_2.openFromFile("beat_2.ogg");
	beat_2.play();
	beat_2.setVolume(25.0);
	beat_2.setLoop(true);
	
	//Se crea y configura los botones para volver a jugar y volver al menú
	b_volverMenu.loadFromFile("volveralmenu.png");
	spr_volMen.setTexture(b_volverMenu);
	spr_volMen.setPosition(150, tam_resol.y-120);
	spr_volMen.setScale(tam_resol.x/1280.0 * 0.65,tam_resol.y/720.0 * 0.65);
	
	b_volverJugar.loadFromFile("volverajugar.png");
	spr_volJug.setTexture(b_volverJugar);
	spr_volJug.setOrigin(b_volverJugar.getSize().x,0);
	spr_volJug.setPosition(tam_resol.x-150, tam_resol.y-120);
	spr_volJug.setScale(tam_resol.x/1280.0 * 0.65,tam_resol.y/720.0 * 0.65);
	
	//Tipografía utilizada
	fuente.loadFromFile("Melted Monster.ttf");
	
	//Configuración de textos que aparecen en la pantalla
	fin.setFont(fuente);
	fin.setCharacterSize(60);
	fin.setOrigin(130,30);
	fin.setPosition(tam_resol.x/2,150);
	fin.setString("Fue tu fin.");
	fin.setFillColor({0,0,0});
	fin.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	
	guard_exi.setFont(fuente);
	guard_exi.setCharacterSize(20);
	guard_exi.setOrigin(105,10);
	guard_exi.setPosition(tam_resol.x/2,285);
	guard_exi.setString("Guardado correctamente!");
	guard_exi.setFillColor({0,191,255});
	guard_exi.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	resul.setFont(fuente);
	resul.setCharacterSize(30);
	resul.setOrigin(200,15);
	resul.setPosition(tam_resol.x/2,230);
	resul.setString("Tu puntaje fue de " + tiem_fin + " segundos");
	resul.setFillColor({0,0,0});
	resul.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	paso_guard.setFont(fuente);
	paso_guard.setCharacterSize(20);
	paso_guard.setOrigin(80,10);
	paso_guard.setPosition(tam_resol.x/2,270);
	paso_guard.setString("Hay nuevo record!"s);
	paso_guard.setFillColor({0,191,255});
	paso_guard.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	entradaNombre.setFont(fuente);
	entradaNombre.setCharacterSize(20);
	entradaNombre.setOrigin(80,10);
	entradaNombre.setPosition(tam_resol.x/2-70,300);
	entradaNombre.setString("Ingrese su nombre: "s);
	entradaNombre.setFillColor({0,191,255});
	entradaNombre.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	//Se configura el input 
	nom_jug.setOrigin(0,10);
	nom_jug.setPosition(tam_resol.x/2+45,300);
	nom_jug.setMaxChars(10);
	nom_jug.setSingleWord(true);
	nom_jug.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
}

void esc_fin :: actualizar(RenderWindow &w,juego &j) {
	//Despues del tiempo de espera se habilita el uso del botón
	if (t_espera_inic.getElapsedTime().asMilliseconds() > 300 ){
		FloatRect f1 = spr_volMen.getGlobalBounds();
		if (f1.contains(Mouse::getPosition(w).x, Mouse::getPosition(w).y)) {
			if(Mouse::isButtonPressed(Mouse::Left)) {
				Clock r_fin;
				beat_2.stop();
				j.cambiarEsc(new esc_inic(w.getSize(), r_fin.getElapsedTime()));
			}
		}
		FloatRect f2 = spr_volJug.getGlobalBounds();
		if (f2.contains(Mouse::getPosition(w).x, Mouse::getPosition(w).y)) {
			if(Mouse::isButtonPressed(Mouse::Left)) {
				beat_2.stop();
				j.cambiarEsc(new esc_partida(w.getSize()));
			}
		}
		
		//Cuando se cumple la condición, se guarda el nombre del jugador en el archivo de puntuaciones
		if (Keyboard::isKeyPressed(Keyboard::Return) and hay_que_cambiar) {
			puntajes p; strcpy(p.name,nom.c_str()); p.puntaje = tiempo_act;
			tabla.Agregar(p);
			tabla.Guardar();
			hay_que_cambiar = false;
		}
	}
}

void esc_fin ::procesarEvento ( Event &e){
	//Se obtiene la palabra ingresada por el jugador y la guarda en un atributo de la clase
	if (t_espera_inic.getElapsedTime().asMilliseconds() > 3500 ){
		if (e.type==sf::Event::KeyPressed && e.key.code==sf::Keyboard::Return) { 
			nom = nom_jug.getValue(); 
		} else nom_jug.processEvent(e); 
	}
}
	
void esc_fin :: dibujar(RenderWindow &w, juego &j){
	//Se limpia la pantalla, se dibujan los textos y botones
	w.clear(Color(220,30,30));
	w.draw(spr_fondo);
	w.draw(fin);
	w.draw(resul);
	w.draw(spr_volMen);
	w.draw(spr_volJug);
	
	//Si el tiempo obtenido es un nuevo record, dibuja el input para guardar el nombre y los textos relacionados
	if (tabla.SeAgrega(tiempo_act) and hay_que_cambiar) {
		w.draw(paso_guard);
		w.draw(entradaNombre);
		nom_jug.update();
		w.draw(nom_jug);
	}
	//Si ya guardo el nombre se dibuja el texto guardado con éxito
	if(!hay_que_cambiar){
		w.draw(guard_exi);
	}
	
}
