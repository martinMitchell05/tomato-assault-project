#include "arch_tam.h"
#include <fstream>
#include <string>

#include <iostream>
using namespace std;

arch_tam::arch_tam(){
	//Abre el archivo de resolución, si no lo encuentra lo vuelve a crear y lee los valores que se encuentran dentro
	fstream l("Relacion_Pantalla.txt",ios::in|ios::out);
	if(!l.is_open()){
		l.open("Relacion_Pantalla.txt",ios::in|ios::out|ios::trunc);
		l << "Resolucion=1280x720" << endl;
		par.x = 1280;
		par.y = 720;
	} else {
		string line;
		l >> line;
		size_t it = line.find("=");
		size_t it2 = line.find("x",it);
		string x = line.substr(it+1,it2-it-1);
		string y = line.substr(it2+1);
		par.x = stoi(x);
		par.y = stoi(y);
		l.close();
	}
}

//Metodo que devuelve la resolución leída
Vector2u arch_tam::DefineResol(){
	return par;
}


