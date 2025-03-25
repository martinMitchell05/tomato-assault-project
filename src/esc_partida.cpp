#include "esc_partida.h"
#include <cmath>
#include <iostream>
#include <string>
#include "esc_fin.h"
#include "pu_vida.h"
#include "pu_velocidad.h"
#include "powerup.h"
#include "pu_modDisparo.h"
#include "pu_granada.h"

using namespace std;

//Sobrecarga de funcion colision
//Obtengo posicion de las dos clases a colisionar, calcula la distancia entre ambas y si es menor a un valor (ajustado a la resolucion) colisionan
bool colision(enemigo &n, disparo &b){
	Vector2f p_enem = n.posicion();
	Vector2f p_bala = b.posicion();
	Vector2f dif = p_enem - p_bala;
	return (sqrt(dif.x*dif.x+dif.y*dif.y) < 35*n.media_ajus_tam());
}
	
bool colision(enemigo &n, prota &p){
	Vector2f p_enem = n.posicion();
	Vector2f p_prota = p.posicion();
	Vector2f dif = p_enem - p_prota;
	return (sqrt(dif.x*dif.x+dif.y*dif.y) < 40*p.media_ajus_tam());
}
	
bool colision(powerup *pu, prota &p){
	Vector2f p_pow = pu->posicion();
	Vector2f p_prota = p.posicion();
	Vector2f dif = p_pow - p_prota;
	return (sqrt(dif.x*dif.x+dif.y*dif.y) < 75*p.media_ajus_tam());
}

//Detecta todos los enemigos en un radio cercano al personaje para luego eliminarlos 
bool colision_tiempo_gracia(enemigo &n, prota &p){
	Vector2f p_enem = n.posicion();
	Vector2f p_prota = p.posicion();
	Vector2f dif = p_enem - p_prota;
	return (sqrt(dif.x*dif.x+dif.y*dif.y) <= 175*p.media_ajus_tam());
}


//Verifica si el disparo salio de los limites de la pantalla
bool lim_pant_excedido(disparo &b){
	Vector2f p_bala = b.posicion();
	Vector2u tam_resol = b.resol();
	return p_bala.x<0 or p_bala.x>(tam_resol.x+60) or p_bala.y<0 or p_bala.y>(tam_resol.y+20);
}


//Se guardan distintos tipos de enemigos 
void cargarEnemigos(vector<enemigo>&enems, int cant, Vector2f posicion, Texture &t1, Texture &t2,Texture &t3,Texture &t4 , Vector2u tam_resol){	
	for(int i=0;i<cant;i++) { 
		switch(1+rand()%4){
		case 1:
		{
			enemigo n1(t1,posicion,tam_resol);
			enems.push_back(n1);
		}
		break;
		case 2:
		{
			enemigo n2(t2,posicion,tam_resol);
			enems.push_back(n2);
		}
		break;
		case 3:
		{
			enemigo n3(t3,posicion,tam_resol);
			enems.push_back(n3);
		}
		break;
		case 4:
		{
			enemigo n4(t4,posicion,tam_resol);
			enems.push_back(n4);
		}
		break;
		}
	}
}

//Genera un powerup aleatorio (Si la vida esta al maximo, no se puede generar el powerup de adicionar una vida)
powerup* elegirPow(Vector2u tam_resol, prota p){
	int i;
	if(p.verVidas()==3){
		i = rand()%3;
	} else {
		i = rand()%4;
	}
	switch(i){
	case 0: 
		return new pu_velocidad(tam_resol);
	case 1: 
		return new pu_modDisparo(tam_resol);
	case 2:
		return new pu_granada(tam_resol);
	case 3:
		return new pu_vida(tam_resol);
	}
}
	

esc_partida::esc_partida(Vector2u tam_resol) : p1(tam_resol) {
	//Carga musica de fondo
	batalla.openFromFile("sounds/batalla.ogg");
	batalla.play();
	batalla.setVolume(20.0);
	batalla.setLoop(true);
	
	//Carga y configuracion de imagen de fondo
	tex_fondo.loadFromFile("textures/background.png");
	spr_fondo.setTexture(tex_fondo);
	spr_fondo.setOrigin(tex_fondo.getSize().x/2,tex_fondo.getSize().y/2);
	//Se ajusta al tama�o de la resolucion
	spr_fondo.scale(float(tam_resol.x)/tex_fondo.getSize().x,float(tam_resol.y)/tex_fondo.getSize().y);
	spr_fondo.setPosition((tam_resol.x)/2,(tam_resol.y)/2);
	
	//Carga de textura de enemigos
	tex_enem_1.loadFromFile("textures/enemigo.png");
	tex_enem_2.loadFromFile("textures/enemigo2.png");
	tex_enem_3.loadFromFile("textures/enemigo3.png");
	tex_enem_4.loadFromFile("textures/enemigo4.png");
	
	//Tipografia utilizada
	fuente.loadFromFile("fonts/DragonSlayer.ttf");
	
	//Configuracion del temporizador de tiempo vivo
	t_tiem.setFont(fuente);
	t_tiem.setPosition(tam_resol.x-70,10);
	t_tiem.setCharacterSize(20);
	t_tiem.setFillColor({0,0,0});
	//Se ajusta al tama�o de la resolucion
	t_tiem.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	//Configuracion texto preparacion
	preparate.setFont(fuente);
	preparate.setCharacterSize(40);
	preparate.setOrigin(150,20);
	preparate.setPosition(tam_resol.x/2,tam_resol.y/2-150);
	preparate.setString("�Preparate!");
	preparate.setFillColor({0,0,0});
	//Se ajusta al tama�o de la resolucion
	preparate.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
	
	//Configuracion sonido powerup y colision al personaje
	sb_powerup.loadFromFile("sounds/sonidoPowerUp.ogg");
	s_powerup.setBuffer(sb_powerup);
	sb_golpe.loadFromFile("sounds/sonidogolpe.ogg");
	s_golpe.setBuffer(sb_golpe);
	s_golpe.setVolume(100.0);
	
	//Carga y configura escudo de invulnerabilidad
	tex_escudo.loadFromFile("textures/escudo.png");
	spr_escudo.setTexture(tex_escudo);
	spr_escudo.setOrigin(tex_escudo.getSize().x/2,tex_escudo.getSize().y/2);
	spr_escudo.setPosition(250,35);
	//Se ajusta al tama�o de la resolucion
	spr_escudo.setScale(tam_resol.x/1280.0,tam_resol.y/720.0);
}


void esc_partida::actualizar(RenderWindow &w , juego &j) {
	//Actualizacion del protagonista, nuevos disparos, disparos existentes y enemigos
	p1.actualizar(w);
	if( p1.hayQueDisparar()){
		p1_disp.push_back(p1.salioDisparo());
	}
	for(disparo &x : p1_disp) {
		x.actualizar();
	}
	for(enemigo &y : enems){
		y.actualizar(p1.posicion());
	}
	
	//Verificar si colisionan enemigos con disparos
	for(auto it_bal=p1_disp.begin(); it_bal<p1_disp.end(); ++it_bal) {
		for (auto it_ene=enems.begin(); it_ene<enems.end(); ++it_ene){
			if (colision(*it_ene,*it_bal)){
				enems.erase(it_ene);
				p1_disp.erase(it_bal);
				break;
			}
		}
	}
	
	//Eliminar disparos que salieron del limites de la pantalla
	auto it = remove_if(p1_disp.begin(),p1_disp.end(),lim_pant_excedido);
	p1_disp.erase(it,p1_disp.end());
	
	//Spawn de nuevos enemigos en pantalla
	if(t_espera_inic.getElapsedTime().asSeconds() > 3 and t_recargar_enems.getElapsedTime().asSeconds() > 1 ){
		if(enems.size()<= 2+rand()%2 ){
			int cant2 = tiempo_vivo.getElapsedTime().asSeconds()*0.4; 
			cargarEnemigos(enems, cant2,p1.posicion(), tex_enem_1, tex_enem_2, tex_enem_3, tex_enem_4,w.getSize());
		}
	}
	
	//Actualizacion del tiempo vivo
	float tVivo = tiempo_vivo.getElapsedTime().asSeconds();
	string s_tvivo = to_string(tVivo);
	if(tiempo_vivo.getElapsedTime().asSeconds() < 1000){
		s_tvivo = s_tvivo.substr(0,5);
	}
	if(tiempo_vivo.getElapsedTime().asSeconds() < 100){
		s_tvivo = s_tvivo.substr(0,4);
	}
	if(tiempo_vivo.getElapsedTime().asSeconds() < 10 ){
		s_tvivo = s_tvivo.substr(0,3);
	}
	t_tiem.setString(s_tvivo);	
	
	//Si ya hay un powerup en pantalla (no puede aparecer otro mientras este est� activo), revisa la colision del powerup con el protagonista
	if ( !se_puede_agregar ){
		if(colision(pow_en_pant,p1)){	//Si colisiona se ejecuta el sonido de powerup, se aplica la ventaja de este, se borra el powerup, comienza el tiempo del powerup activo y se permite agregar uno nuevo
			s_powerup.play();
			pow_en_pant->aplicar(p1, *this);
			delete pow_en_pant;
			tiempo_pow_nuevo.restart();
			se_puede_agregar = true;
		}
	}
	//Si paso el tiempo requerido para que aparezca un nuevo powerup y todavia no aparecio otro, aparece otro en pantalla
	if(tiempo_pow_nuevo.getElapsedTime().asSeconds() > 7 and se_puede_agregar){
		pow_en_pant = elegirPow(w.getSize(),p1);
		se_puede_agregar = false;
	}
	
	
	//Si los enemigos colisionaron con el protagonista, se genera un escudo de invulnerabilidad de 3 segundos que elimina las colisiones con estos
	if(tiempo_evitar_colisiones.getElapsedTime().asSeconds() > 3){
		/*Si pasaron los 3 segundos de "gracia" las colisiones vuelven y si algunos de los enemigos en pantalla colisionan con el protagonista, 
		se modifica la vida, se aumenta la velocidad para poder escapar, se borra en un radio los enemigos cercanos y se activa el escudo
		*/
		inmune=false;
		for(auto it_ene_col=enems.begin(); it_ene_col<enems.end(); ++it_ene_col){
			if(colision(*it_ene_col,p1)){
				p1.cambiarVida(false);
				p1.cambiarVeloc();
				
				s_golpe.play();
				
				inmune=true;
		
				enems.erase(it_ene_col);
				for(auto it_ene=enems.begin(); it_ene<enems.end(); ++it_ene){
					if(colision_tiempo_gracia(*it_ene,p1)){
						enems.erase(it_ene);
					}
				}
				
				tiempo_evitar_colisiones.restart();
				break;
			}
		}
		//Si las vidas llegaron a 0, el jugador perdio 
		if(p1.verVidas() == 0) {
			
			batalla.stop();
			pierde = true;
			j.cambiarEsc(new esc_fin(s_tvivo, w.getSize()));
		}
	}
	
}

//Metodo utilizado para powerup (granada)
void esc_partida::borra_enems() {
	enems.erase(enems.begin()+1,enems.end());
	t_recargar_enems.restart(); 
}

//Tiempo de espera antes de pasar a la proxima escena (util para mostrar que el jugador murio)
void esc_partida::esperarTiempo() {
	if (pierde) {
		Clock cl;
		while (cl.getElapsedTime().asSeconds() <= 3) {}
	}
}

void esc_partida::dibujar(RenderWindow &w, juego &j) {
	//Limpia la pantalla, dibuja el fondo
	w.clear(Color(100,255,150,255));
	w.draw(spr_fondo);
	//Dibuja los powerups (si existen)
	if (!se_puede_agregar ){
		pow_en_pant->dibujar(w);
	}
	//Dibuja los enemigos y las balas mientras el protagonista esta vivo
	if ( !pierde ) {
		for(enemigo &y : enems){
			y.dibujar(w);
		}
		for(disparo &x : p1_disp) {
			x.dibujar(w);
		}
	}	
	//Dibuja el jugador y el tiempo
	w.draw(t_tiem);
	p1.dibujar(w);
	if(inmune){
		//Dibuja el escudo que hace referencia al tiempo de invulnerabilidad
		w.draw(spr_escudo);
	}
	if(t_espera_inic.getElapsedTime().asSeconds() < 2.5 ){
		//Dibuja la alerta al inicio de la partida
		w.draw(preparate);
	}
}

esc_partida::~esc_partida(){
	//Detiene el sonido de powerup y golpe al jugador
	s_powerup.stop();
	s_golpe.stop();
}




