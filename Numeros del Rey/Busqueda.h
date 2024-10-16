#pragma once

#include <string>
#include <vector>
#include "Grafo.h"
#include "Agenda.h"

using namespace std;


class Busqueda
{
	public:
		Busqueda(Grafo& grafo);
		~Busqueda();
		bool busqueda_a_lo_ancho(string numero, int& nodo_encontrado);
		bool busqueda_primero_en_profundidad(string numero, int& nodo_encontrado);		
		bool buscar_todas_las_soluciones(string numero);

		string devolver_ruta(unsigned int nodo_encontrado) const;				
	
	private:
		Grafo grafo;
		Arbol arbol_de_busqueda;				
		vector<string> soluciones;
};

