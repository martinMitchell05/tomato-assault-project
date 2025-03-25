#include "esc_tabla.h"
#include <cstring>
#include <vector>
#include "esc_inic.h"

using namespace std;

esc_tabla::esc_tabla(Time x_min, Vector2u tam_resol) {
	//Se crea y configura la imagen de fondo
	fondo.loadFromFile("textures/Fondo_ini.png");
	spr_fondo.setTexture(fondo);
	spr_fondo.setColor({255,255,255,90});
	spr_fondo.setOrigin((fondo.getSize().x/2), (fondo.getSize().y/2));
	spr_fondo.setPosition(tam_resol.x/2, tam_resol.y/2);
	spr_fondo.setScale(float(tam_resol.x)/fondo.getSize().x,float(tam_resol.y)/fondo.getSize().y);
	
	//La m�sica continua desde la escena anterior
	beat_F.openFromFile("sounds/beat_1.ogg");
	beat_F.play();
	beat_F.setPlayingOffset(x_min);
	beat_F.setVolume(25.0);
	beat_F.setLoop(true);
	
	//Se crea y configura el bot�n para volver al men�
	b_volver.loadFromFile("textures/volver.png");
	spr_volver.setTexture(b_volver);
	spr_volver.setPosition(80,tam_resol.y-100);
	spr_volver.setScale(tam_resol.x/1280.0*0.65,tam_resol.y/720.0*0.65);
	
	//Tipograf�a utilizada 
	fuente2.loadFromFile("fonts/DragonSlayer.ttf");
	
	//Creaci�n del texto para los nombres de la tabla 
	tex_tabla.setFont(fuente2);
	tex_tabla.setCharacterSize(20);
	tex_tabla.setOrigin(150,150);
	tex_tabla.setPosition(tam_resol.x/2,tam_resol.y/2-30);
	tex_tabla.setFillColor({255,255,255});
	tex_tabla.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	//Creaci�n del texto para los valores de la tabla 
	pto_tabla.setFont(fuente2);
	pto_tabla.setCharacterSize(20);
	pto_tabla.setOrigin(20,150);
	pto_tabla.setPosition(tam_resol.x/2+110,tam_resol.y/2-30);
	pto_tabla.setFillColor({255,255,255});
	pto_tabla.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	//Se obtiene la tabla desde la clase creada
	vector<puntajes> punt_tabla = tabla.Muestra();
	string datos_tex_tabla;
	datos_tex_tabla = "Top 10 mejores puntajes:\n";
	
	//Obtiene y guarda los nombres 
	for(size_t i=0;i<punt_tabla.size();i++) { 
		string l(punt_tabla[i].name);
		datos_tex_tabla += l + "\n";
	}
	tex_tabla.setString(datos_tex_tabla);
	
	//Obtiene y guarda los puntajes
	string dato_pto_tabla = "\n";
	for(size_t i=0;i<punt_tabla.size();i++) { 
		
		string n = to_string(punt_tabla[i].puntaje);
		
		//Depende el valor del puntaje se cortan de manera distinta para que los decimales coincidan
		if(punt_tabla[i].puntaje < 10 ){
			n = n.substr(0,3);
		}else if(punt_tabla[i].puntaje < 100){
			n = n.substr(0,4);
		}else if(punt_tabla[i].puntaje < 1000){
			n = n.substr(0,5);
		}
		
		dato_pto_tabla += n + "\n";
	}
	pto_tabla.setString(dato_pto_tabla);
}

void esc_tabla :: actualizar(RenderWindow &w,juego &j) {
	//Despues del tiempo de espera se habilita el uso del bot�n
	if (t_espera_inic.getElapsedTime().asMilliseconds() > 300 ){
		FloatRect f1 = spr_volver.getGlobalBounds();
		if (f1.contains(Mouse::getPosition(w).x, Mouse::getPosition(w).y)) {
			if(Mouse::isButtonPressed(Mouse::Left)) {
				Time min2 = beat_F.getPlayingOffset();
				beat_F.stop();
				j.cambiarEsc(new esc_inic(w.getSize(), min2));
			}
		}
	}
}


void esc_tabla :: dibujar(RenderWindow &w, juego &j) {
	//Se limpia la pantalla, se dibuja la imagen de fondo con los botones y la tabla de puntajes
	w.clear(Color(0,0,0));
	w.draw(spr_fondo);
	w.draw(tex_tabla);
	w.draw(pto_tabla);
	w.draw(spr_volver);
}
