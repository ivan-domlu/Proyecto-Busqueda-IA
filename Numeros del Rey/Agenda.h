#pragma once
#include <string>
#include <vector>
#include "Arbol.h"

using namespace std;

struct informacion_agenda 
{
	string nombre_del_nodo = "";
	int indice_del_nodo = 0;
};

class Agenda
{
	public:
		Agenda(void);
		~Agenda(void);
		void borra_agenda(void);
		void agregar_al_inicio_de_la_agenda(informacion_agenda elemento);
		void agregar_al_final_de_la_agenda(informacion_agenda elemento);
		bool devolver_y_eliminar_primer_nodo_de_la_agenda(informacion_agenda& elemento);
		size_t tamano_de_la_agenda(void);
		void devolver_elemento_de_la_agenda(unsigned int indice, informacion_agenda& elemento);
		bool esta_vacia(void) const;
		informacion_agenda crea_nodo_de_agenda(string nombre_del_nodo, unsigned int indice_del_nodo);
		bool existe_un_nodo_comun_en_las_agendas(Agenda agenda_a_comparar, int& nodo_comun_inicio, int& nodo_comun_final,
			Arbol arbol_de_busqueda_desde_el_inicio, Arbol arbol_de_busqueda_desde_el_final) const;
		void ordenar_por_costo(Arbol arbol_de_busqueda);
		void mantener_solo_k_elementos(unsigned int elementos_por_mantener);
		void eliminar_elemento_de_la_agenda(unsigned int indice);

	private:
		vector<informacion_agenda> agenda;
};

