#pragma once
#include <string>
#include <vector>

using namespace std;

struct tipo_nodo_informacion
{
	string nombre_del_nodo = "";
	float costo_acumulado = 0.0f;
	float costo_estimado = 0.0f;
};

struct tipo_nodo_del_arbol
{
	tipo_nodo_informacion contenido;
	int padre = -1;
	unsigned int profundidad = 0;
	vector<unsigned int> hijos;
};

class Arbol
{
	public: 
		Arbol();
		~Arbol();
		void crear_arbol(tipo_nodo_informacion contenido);
		void borrar_arbol();
		unsigned int agregar_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido);
		bool esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const;
		bool informacion_de_un_nodo(unsigned int nodo, tipo_nodo_informacion& contenido) const;
		int devolver_padre(unsigned int nodo) const;
		unsigned int devolver_profundidad(unsigned int nodo) const;
		string devolver_ruta_encontrada(unsigned int nodo_encontrado) const;
		string devolver_la_ruta_encontrada_busqueda_bidireccional(int nodo_encontrado_desde_el_inicio,
			int nodo_encontrado_desde_el_final, Arbol arbol_de_busqueda_desde_el_final) const;

	private:
		vector<tipo_nodo_del_arbol> arbol;
};

