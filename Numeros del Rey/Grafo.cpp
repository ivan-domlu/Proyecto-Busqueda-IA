#include "Grafo.h"

Grafo::Grafo()
{
    grafo.clear();
}

Grafo::~Grafo()
{

}

bool Grafo::lee_grafo(string archivo)
{
    string leida;
    tipo_enlace_de_grafo enlace;
    fstream newfile;
    vector<string> vector_de_cadenas;
    grafo.clear();
    newfile.open(archivo, ios::in);
    if (newfile.is_open())
    {
        getline(newfile, leida);
        while (getline(newfile, leida))
        {
            vector_de_cadenas.clear();
            stringstream cadena(leida);
            string temporal;
            while (getline(cadena, temporal, ','))
                vector_de_cadenas.push_back(temporal);
            enlace.nodo_1 = vector_de_cadenas[0];
            enlace.costo_nodo_1 = (float)atof(vector_de_cadenas[1].c_str());
            enlace.posicion_x_nodo_1 = (float)atof(vector_de_cadenas[2].c_str());
            enlace.posicion_y_nodo_1 = (float)atof(vector_de_cadenas[3].c_str());
            enlace.nodo_2 = vector_de_cadenas[4];
            enlace.costo_nodo_2 = (float)atof(vector_de_cadenas[5].c_str());
            enlace.posicion_x_nodo_2 = (float)atof(vector_de_cadenas[6].c_str());
            enlace.posicion_y_nodo_2 = (float)atof(vector_de_cadenas[7].c_str());
            enlace.costo_del_enlace = (float)atof(vector_de_cadenas[8].c_str());
            grafo.push_back(enlace);
        }
        newfile.close();
        return true;
    }
    else
        return false;
}


void Grafo::devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const
{
    vecinos.clear();
    tipo_enlace_de_grafo temporal;
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == nodo)
            vecinos.push_back(grafo[i]);
        else if (grafo[i].nodo_2 == nodo)
        {
            temporal.nodo_1 = grafo[i].nodo_2;
            temporal.costo_nodo_1 = grafo[i].costo_nodo_2;
            temporal.posicion_x_nodo_1 = grafo[i].posicion_x_nodo_2;
            temporal.posicion_y_nodo_1 = grafo[i].posicion_y_nodo_2;
            temporal.nodo_2 = grafo[i].nodo_1;
            temporal.costo_nodo_2 = grafo[i].costo_nodo_1;
            temporal.posicion_x_nodo_2 = grafo[i].posicion_x_nodo_1;
            temporal.posicion_y_nodo_2 = grafo[i].posicion_y_nodo_1;
            temporal.costo_del_enlace = grafo[i].costo_del_enlace;
            vecinos.push_back(temporal);
        }

}

bool Grafo::devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nodo, Arbol arbol,
    int nodo_padre, tipo_nodo_informacion& informacion) const
{
    float costo_acumulado_del_padre = 0.0f;
    string nombre_del_nodo_padre = "";
    tipo_nodo_informacion info_padre;

    if (nodo_padre != -1)
    {
        if (arbol.informacion_de_un_nodo(nodo_padre, info_padre))
        {
            costo_acumulado_del_padre = info_padre.costo_acumulado;
            nombre_del_nodo_padre = info_padre.nombre_del_nodo;
        }
        
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo &&
                grafo[i].nodo_2 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;
                return true;
            }

        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo &&
                grafo[i].nodo_1 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;
                return true;
            }
        return false;
    }
    else
    {
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1;
                return true;
            }
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2;
                return true;
            }
        return false;
    }
}

