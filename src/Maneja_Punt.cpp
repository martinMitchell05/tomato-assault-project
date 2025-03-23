#include "Maneja_Punt.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

//Sobrecarga operador menor, para poder trabajar con el struct "puntajes"
bool operator<(puntajes p1, puntajes p2) {
	return p1.puntaje < p2.puntaje;
}


Maneja_Punt::Maneja_Punt() {
	
	//Se abre un archivo binario para guardar las puntuaciones
	fstream archi("puntajes.dat", ios::binary | ios::in | ios::out);
	if(!archi.is_open()){ //Si no se puede abrir el archivo, se crea uno con valores por defecto para su uso 
		archi.open("puntajes.dat",ios::binary |ios::out| ios::in |ios::trunc);
		for(int i=0;i<10;i++) { 
			string baseName = "AAAAAAAAAA";
			puntajes p;
			strcpy(p.name,baseName.c_str());
			p.puntaje = 0;
			archi.write(reinterpret_cast<char*>(&p),sizeof(puntajes));
		}
	}
	//Trabajo de Binario -> Vector
	archi.seekg(0,ios::end);
	int s = archi.tellg()/sizeof(puntajes);
	archi.seekg(0,ios::beg);
	for (int i=0; i<s; i++) {
		puntajes aux;
		archi.read(reinterpret_cast<char*>(&aux), sizeof(aux));
		m_datos.push_back(aux);
	}
	archi.close();
}

//Metodo para agregar al vector un nuevo puntaje (nombre y puntuación obtenida)
void Maneja_Punt::Agregar(puntajes puntos_final) {
	m_datos.push_back(puntos_final);
	sort(m_datos.begin(),m_datos.end());
	reverse(m_datos.begin(),m_datos.end());
	m_datos.erase(m_datos.end()-1); //Borra el que estaba antes en la última posición
	
}

//Devuelve el vector con todos los puntajes
vector<puntajes> Maneja_Punt::Muestra() {
	return m_datos;
}

//Metodo para ver si agregar o no, un puntaje obtenido
bool Maneja_Punt::SeAgrega(float puntajex) {
	auto it_min = min_element(m_datos.begin(), m_datos.end());
	if (puntajex < (*it_min).puntaje) {
		return false;
	} else {
		return true;
	}
}

//Guarda los datos (nombres y puntajes) desde el vector al archivo binario
void Maneja_Punt::Guardar() {
	ofstream archi("puntajes.dat", ios::binary | ios::trunc);
	for (size_t i=0; i<m_datos.size(); ++i) {
		archi.write(reinterpret_cast<char*>(&m_datos[i]),sizeof(puntajes));
	}
	
	archi.close();
}
