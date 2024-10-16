#include "Arbol.h"

Arbol::Arbol()
{

}

Arbol::~Arbol()
{

}

void Arbol::borrar_arbol()
{
    arbol.clear();
}

void Arbol::crear_arbol(tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = -1;
    temporal.profundidad = 0;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol.clear();
    arbol.push_back(temporal);
}

unsigned int Arbol::agregar_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = padre;
    temporal.profundidad = arbol[padre].profundidad + 1;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol.push_back(temporal);
    arbol[padre].hijos.push_back((unsigned int)(arbol.size() - 1));
    return (arbol.size() - 1);
}

bool Arbol::esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const
{
    int temporal = arbol[nodo_origen].padre;
    while (temporal != -1)
    {
        if (arbol[temporal].contenido.nombre_del_nodo == nombre_del_nodo)
            return true;
        temporal = arbol[temporal].padre;
    }
    return false;
}

bool Arbol::informacion_de_un_nodo(unsigned int nodo, tipo_nodo_informacion& contenido) const 
{
    if (nodo < arbol.size())
    {
        contenido = arbol[nodo].contenido;
        return true;
    }
    return false;
}

int Arbol::devolver_padre(unsigned int nodo) const
{
    return arbol[nodo].padre;
}

unsigned int Arbol::devolver_profundidad(unsigned int nodo) const
{
    return arbol[nodo].profundidad;
}


string Arbol::devolver_ruta_encontrada(unsigned int nodo_encontrado) const
{
    vector<unsigned int> temporal;
    string camino = "";
    temporal.clear();
    while (nodo_encontrado != -1)
    {
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol[nodo_encontrado].padre;
    }
    for (int i = (int)(temporal.size() - 1); i >= 0; i--)
        camino = camino + " - " + arbol[temporal[i]].contenido.nombre_del_nodo;
    camino.erase(camino.begin(), camino.begin() + 3);
    return camino;
}

string Arbol::devolver_la_ruta_encontrada_busqueda_bidireccional(int nodo_encontrado_desde_el_inicio,
    int nodo_encontrado_desde_el_final, Arbol arbol_de_busqueda_desde_el_final) const
{    
    vector<unsigned int> temporal;
    tipo_nodo_informacion info_nodo;
    string camino_desde_el_inicio = "";
    string camino_desde_el_final = "";
    if (nodo_encontrado_desde_el_inicio != -1)
    {
        temporal.clear();
        while (nodo_encontrado_desde_el_inicio != -1)
        {
            temporal.push_back(nodo_encontrado_desde_el_inicio);
            nodo_encontrado_desde_el_inicio = arbol[nodo_encontrado_desde_el_inicio].padre;
        }
        for (int i = (int)(temporal.size() - 1); i >= 0; i--)
            camino_desde_el_inicio = camino_desde_el_inicio + " - " +
            arbol[temporal[i]].contenido.nombre_del_nodo;
    }
    camino_desde_el_inicio.erase(camino_desde_el_inicio.begin(), camino_desde_el_inicio.begin() + 3);
    if (nodo_encontrado_desde_el_final != -1)
    {
        temporal.clear();     
        nodo_encontrado_desde_el_final = arbol_de_busqueda_desde_el_final.devolver_padre(nodo_encontrado_desde_el_final);
        while (nodo_encontrado_desde_el_final != -1)
        {
            temporal.push_back(nodo_encontrado_desde_el_final);
            nodo_encontrado_desde_el_final = arbol_de_busqueda_desde_el_final.devolver_padre(nodo_encontrado_desde_el_final);
        }
        for (int i = (int)(temporal.size() - 1); i >= 0; i--)
        {
            arbol_de_busqueda_desde_el_final.informacion_de_un_nodo(temporal[i], info_nodo);
            camino_desde_el_final = info_nodo.nombre_del_nodo + " - " + camino_desde_el_final;
        }
        camino_desde_el_final.erase(camino_desde_el_final.end() - 3, camino_desde_el_final.end());
    }
    return camino_desde_el_inicio + " - " + camino_desde_el_final;
}