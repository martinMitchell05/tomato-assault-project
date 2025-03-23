#include "juego.h"
#include "esc_inic.h"
#include "arch_tam.h"

int main(int argc, char *argv[]){
	//Archivo para la lectura de resolución
	arch_tam resol;
	//Cronometro auxiliar para que comience desde cero la música
	Clock min_z;
	//Se instancia el juego con los parametros necesarios para su inicio
	juego g(new esc_inic(resol.DefineResol(), min_z.restart()), resol.DefineResol());
	//Se inicia el juego
	g.jugar();
	return 0;
}

