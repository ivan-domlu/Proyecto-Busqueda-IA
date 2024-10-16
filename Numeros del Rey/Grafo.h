#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  
#include "Arbol.h"
#include <cmath>

using namespace std;

struct tipo_enlace_de_grafo
{
	char num_1 = ' ';
	char operacion = ' ';
	char num_2 = ' ';
};


class Grafo
{
	public:
		Grafo();
		~Grafo();
		bool lee_grafo(string archivo);	
		void devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const;
		bool devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nodo, Arbol arbol_creado,
			int nodo_padre, tipo_nodo_informacion& informacion) const;

	private:
		vector<tipo_enlace_de_grafo> grafo;
};

