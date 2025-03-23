#ifndef MANEJA_PUNT_H
#define MANEJA_PUNT_H
#include <fstream>
#include <vector>
using namespace std;

struct puntajes {
	char name[10];
	float puntaje;
};

class Maneja_Punt {
private:
	vector<puntajes> m_datos;
	
public:
	Maneja_Punt();
	void Agregar(puntajes puntos_final);
	vector<puntajes> Muestra();
	void Guardar();
	bool SeAgrega(float puntajex);

};

#endif

