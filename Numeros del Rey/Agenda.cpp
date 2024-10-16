#include "Agenda.h"

Agenda::Agenda()
{
	agenda.clear();
}

Agenda::~Agenda()
{

}

void Agenda::borra_agenda(void)
{
	agenda.clear();
}

void Agenda::agregar_al_inicio_de_la_agenda(informacion_agenda elemento)
{
	agenda.insert(agenda.begin(), elemento);
}

void Agenda::agregar_al_final_de_la_agenda(informacion_agenda elemento)
{
	agenda.push_back(elemento);
}

bool Agenda::devolver_y_eliminar_primer_nodo_de_la_agenda(informacion_agenda& elemento)
{
	if (!agenda.empty())
	{
		elemento = agenda.front();
		agenda.erase(agenda.begin());
		return true;
	}

	return false;
}

size_t Agenda::tamano_de_la_agenda(void)
{
	return agenda.size();
}

void Agenda::devolver_elemento_de_la_agenda(unsigned int indice, informacion_agenda& elemento)
{
	elemento = agenda[indice];
}

bool Agenda::esta_vacia(void) const
{
	return agenda.empty();
}

informacion_agenda Agenda::crea_nodo_de_agenda(string nombre_del_nodo, unsigned int indice_del_nodo)
{
	informacion_agenda temporal;
	temporal.nombre_del_nodo = nombre_del_nodo;
	temporal.indice_del_nodo = indice_del_nodo;
	return temporal;
}

bool Agenda::existe_un_nodo_comun_en_las_agendas(Agenda agenda_a_comparar, int& nodo_comun_inicio, int& nodo_comun_final,
	Arbol arbol_de_busqueda_desde_el_inicio, Arbol arbol_de_busqueda_desde_el_final) const
{
	tipo_nodo_informacion info_nodo_arbol_inicio, info_nodo_arbol_final;
	informacion_agenda info_nodo_agenda_a_comparar;

	for (unsigned int i = 0; i < agenda.size(); i++)
	{
		arbol_de_busqueda_desde_el_inicio.informacion_de_un_nodo(agenda[i].indice_del_nodo, info_nodo_arbol_inicio);
		for (unsigned int j = 0; j < agenda_a_comparar.tamano_de_la_agenda(); j++)
		{
			agenda_a_comparar.devolver_elemento_de_la_agenda(j, info_nodo_agenda_a_comparar);
			arbol_de_busqueda_desde_el_final.informacion_de_un_nodo(info_nodo_agenda_a_comparar.indice_del_nodo, info_nodo_arbol_final);
			if (info_nodo_arbol_inicio.nombre_del_nodo == info_nodo_arbol_final.nombre_del_nodo)
			{
				nodo_comun_inicio = agenda[i].indice_del_nodo;
				nodo_comun_final = info_nodo_agenda_a_comparar.indice_del_nodo;
				return true;
			}
		}
	}
	return false;
}

void Agenda::ordenar_por_costo(Arbol arbol_de_busqueda)
{
	tipo_nodo_informacion info_nodo_1;
	tipo_nodo_informacion info_nodo_2;
	informacion_agenda temporal;

	if (!agenda.empty())
		for (unsigned int i = 0; i < agenda.size() - 1; i++)
		{			
			for (unsigned int j = i + 1; j < agenda.size(); j++)
			{
				arbol_de_busqueda.informacion_de_un_nodo(agenda[i].indice_del_nodo, info_nodo_1);
				arbol_de_busqueda.informacion_de_un_nodo(agenda[j].indice_del_nodo, info_nodo_2);
				if (info_nodo_1.costo_acumulado > info_nodo_2.costo_acumulado)
				{
					temporal = agenda[i];
					agenda[i] = agenda[j];
					agenda[j] = temporal;					
				}
			}
		}			
}

void Agenda::mantener_solo_k_elementos(unsigned int elementos_por_mantener)
{
	if (agenda.size() > elementos_por_mantener)
		agenda.erase(agenda.begin() + elementos_por_mantener, agenda.end());
}

void Agenda::eliminar_elemento_de_la_agenda(unsigned int indice)
{
	agenda.erase(agenda.begin() + indice);
}