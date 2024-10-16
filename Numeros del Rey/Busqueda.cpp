#include "Busqueda.h"
#include <string>


using namespace std;

#pragma warning(disable : 6011)

Busqueda::Busqueda(Grafo& grafo)
{
    Busqueda::grafo = grafo;
}

Busqueda::~Busqueda()
{

}

bool Busqueda::busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final, int & nodo_encontrado)
{
    Agenda agenda;
    informacion_agenda nodo_actual_agenda;
    informacion_agenda nodo_a_agregar_agenda;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    vector<tipo_enlace_de_grafo> vecinos;

    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda, -1, informacion_del_nodo_inicio))
        return false;

    nodo_actual_agenda = agenda.crea_nodo_de_agenda(informacion_del_nodo_inicio.nombre_del_nodo, 0);
    
    arbol_de_busqueda.crear_arbol(informacion_del_nodo_inicio);
    agenda.borra_agenda();
    agenda.agregar_al_inicio_de_la_agenda(nodo_actual_agenda);
    
    while (!agenda.esta_vacia())
    {
        agenda.devolver_y_eliminar_primer_nodo_de_la_agenda(nodo_actual_agenda);

        if (nodo_actual_agenda.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual_agenda.indice_del_nodo;
            return true;
        }
        grafo.devuelve_vecinos_grafo_no_dirigido(nodo_actual_agenda.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual_agenda.indice_del_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, 
                                            arbol_de_busqueda, nodo_actual_agenda.indice_del_nodo, 
                                            informacion_del_hijo_a_adicionar);
            
            nodo_a_agregar_agenda = agenda.crea_nodo_de_agenda(informacion_del_hijo_a_adicionar.nombre_del_nodo,
                arbol_de_busqueda.agregar_hijo_a_un_nodo(nodo_actual_agenda.indice_del_nodo,
                    informacion_del_hijo_a_adicionar));

            agenda.agregar_al_inicio_de_la_agenda(nodo_a_agregar_agenda);
        }
    }
    return false;
}

bool Busqueda::busqueda_a_lo_ancho(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    Agenda agenda;
    informacion_agenda nodo_actual_agenda;
    informacion_agenda nodo_a_agregar_agenda;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    vector<tipo_enlace_de_grafo> vecinos;

    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda, -1, informacion_del_nodo_inicio))
        return false;

    nodo_actual_agenda = agenda.crea_nodo_de_agenda(informacion_del_nodo_inicio.nombre_del_nodo, 0);

    arbol_de_busqueda.crear_arbol(informacion_del_nodo_inicio);
    agenda.borra_agenda();
    agenda.agregar_al_inicio_de_la_agenda(nodo_actual_agenda);

    while (!agenda.esta_vacia())
    {
        agenda.devolver_y_eliminar_primer_nodo_de_la_agenda(nodo_actual_agenda);

        if (nodo_actual_agenda.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual_agenda.indice_del_nodo;
            return true;
        }
        grafo.devuelve_vecinos_grafo_no_dirigido(nodo_actual_agenda.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual_agenda.indice_del_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                arbol_de_busqueda, nodo_actual_agenda.indice_del_nodo,
                informacion_del_hijo_a_adicionar);

            nodo_a_agregar_agenda = agenda.crea_nodo_de_agenda(informacion_del_hijo_a_adicionar.nombre_del_nodo,
                arbol_de_busqueda.agregar_hijo_a_un_nodo(nodo_actual_agenda.indice_del_nodo,
                    informacion_del_hijo_a_adicionar));

            agenda.agregar_al_final_de_la_agenda(nodo_a_agregar_agenda);
        }
    }
    return false;
}

bool Busqueda::busqueda_profundidad_limitada(string nodo_inicio, string nodo_final,
                                    unsigned int limite_de_profundidad, int& nodo_encontrado)
{
    Agenda agenda;
    informacion_agenda nodo_actual_agenda;
    informacion_agenda nodo_a_agregar_agenda;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    vector<tipo_enlace_de_grafo> vecinos;

    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda, -1, informacion_del_nodo_inicio))
        return false;

    nodo_actual_agenda = agenda.crea_nodo_de_agenda(informacion_del_nodo_inicio.nombre_del_nodo, 0);

    arbol_de_busqueda.crear_arbol(informacion_del_nodo_inicio);
    agenda.borra_agenda();
    agenda.agregar_al_inicio_de_la_agenda(nodo_actual_agenda);

    while (!agenda.esta_vacia())
    {
        agenda.devolver_y_eliminar_primer_nodo_de_la_agenda(nodo_actual_agenda);

        if (nodo_actual_agenda.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual_agenda.indice_del_nodo;
            return true;
        }
        if (arbol_de_busqueda.devolver_profundidad(nodo_actual_agenda.indice_del_nodo) < limite_de_profundidad)
        {
            grafo.devuelve_vecinos_grafo_no_dirigido(nodo_actual_agenda.nombre_del_nodo, vecinos);
            for (unsigned int i = 0; i < vecinos.size(); i++)
                if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual_agenda.indice_del_nodo, vecinos[i].nodo_2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual_agenda.indice_del_nodo,
                    informacion_del_hijo_a_adicionar);

                nodo_a_agregar_agenda = agenda.crea_nodo_de_agenda(informacion_del_hijo_a_adicionar.nombre_del_nodo,
                    arbol_de_busqueda.agregar_hijo_a_un_nodo(nodo_actual_agenda.indice_del_nodo,
                        informacion_del_hijo_a_adicionar));

                agenda.agregar_al_inicio_de_la_agenda(nodo_a_agregar_agenda);
            }
        }
    }
    return false;
}

bool Busqueda::busqueda_profundidad_iterativa(string nodo_inicio, string nodo_final,
                                unsigned int limite_de_profundidad, unsigned int incremento_de_profundidad,
                                int& nodo_encontrado)
{
    unsigned int profundidad_actual = limite_de_profundidad; 
    do
    {
        if (busqueda_profundidad_limitada(nodo_inicio, nodo_final,
            profundidad_actual, nodo_encontrado))
            return true;
        profundidad_actual += incremento_de_profundidad;
    } while (true);
    return false;
}



bool Busqueda::busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado_desde_el_inicio,
                                      int& nodo_encontrado_desde_el_final)
{
    Agenda agenda_desde_el_inicio, agenda_desde_el_final;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_nodo_final;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    informacion_agenda nodo_actual_desde_el_inicio;
    informacion_agenda nodo_actual_desde_el_final;
    informacion_agenda nodo_a_agregar_agenda;
    vector<tipo_enlace_de_grafo> vecinos_desde_el_inicio;
    vector<tipo_enlace_de_grafo> vecinos_desde_el_final;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda_desde_el_inicio, 
                                                                -1, informacion_del_nodo_inicio))
        return false;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_final, arbol_de_busqueda_desde_el_final, 
                                                            -1, informacion_del_nodo_final))
        return false;
    arbol_de_busqueda_desde_el_inicio.crear_arbol(informacion_del_nodo_inicio);
    arbol_de_busqueda_desde_el_final.crear_arbol(informacion_del_nodo_final);
    agenda_desde_el_inicio.borra_agenda();
    agenda_desde_el_final.borra_agenda();

    nodo_actual_desde_el_inicio = agenda_desde_el_inicio.crea_nodo_de_agenda(informacion_del_nodo_inicio.nombre_del_nodo, 0);
    nodo_actual_desde_el_final = agenda_desde_el_final.crea_nodo_de_agenda(informacion_del_nodo_final.nombre_del_nodo, 0);

    agenda_desde_el_inicio.agregar_al_final_de_la_agenda(nodo_actual_desde_el_inicio);
    agenda_desde_el_final.agregar_al_final_de_la_agenda(nodo_actual_desde_el_final);

    while (true)
    {
        if (agenda_desde_el_inicio.esta_vacia() && agenda_desde_el_final.esta_vacia())
            return false;
        if (!agenda_desde_el_inicio.esta_vacia())
        {
            agenda_desde_el_inicio.devolver_y_eliminar_primer_nodo_de_la_agenda(nodo_actual_desde_el_inicio);
            if (nodo_actual_desde_el_inicio.nombre_del_nodo == nodo_final)
            {
                nodo_encontrado_desde_el_inicio = nodo_actual_desde_el_inicio.indice_del_nodo;
                nodo_encontrado_desde_el_final = -1;
                return true;
            }
            grafo.devuelve_vecinos_grafo_no_dirigido(nodo_actual_desde_el_inicio.nombre_del_nodo,
                vecinos_desde_el_inicio);
            for (unsigned int i = 0; i < vecinos_desde_el_inicio.size(); i++)
                if (arbol_de_busqueda_desde_el_inicio.esta_un_nodo_en_ancestros(nodo_actual_desde_el_inicio.indice_del_nodo,
                                              vecinos_desde_el_inicio[i].nodo_2))
                {
                    vecinos_desde_el_inicio.erase(vecinos_desde_el_inicio.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos_desde_el_inicio.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos_desde_el_inicio[i].nodo_2,
                                                                    arbol_de_busqueda_desde_el_inicio,
                                                                    nodo_actual_desde_el_inicio.indice_del_nodo,
                                                                    informacion_del_hijo_a_adicionar);
                nodo_a_agregar_agenda = agenda_desde_el_inicio.crea_nodo_de_agenda(informacion_del_hijo_a_adicionar.nombre_del_nodo,
                    arbol_de_busqueda_desde_el_inicio.agregar_hijo_a_un_nodo(nodo_actual_desde_el_inicio.indice_del_nodo,
                        informacion_del_hijo_a_adicionar));

                agenda_desde_el_inicio.agregar_al_final_de_la_agenda(nodo_a_agregar_agenda);
            }
        }
        if (!agenda_desde_el_final.esta_vacia())
        {
            agenda_desde_el_final.devolver_y_eliminar_primer_nodo_de_la_agenda(nodo_actual_desde_el_final);

            if (nodo_actual_desde_el_final.nombre_del_nodo == nodo_inicio)
            {
                nodo_encontrado_desde_el_inicio = -1;
                nodo_encontrado_desde_el_final = nodo_actual_desde_el_final.indice_del_nodo;
                return true;
            }
            grafo.devuelve_vecinos_grafo_no_dirigido(nodo_actual_desde_el_final.nombre_del_nodo, vecinos_desde_el_final);
            for (unsigned int i = 0; i < vecinos_desde_el_final.size(); i++)
                if (arbol_de_busqueda_desde_el_final.esta_un_nodo_en_ancestros(nodo_actual_desde_el_final.indice_del_nodo, vecinos_desde_el_final[i].nodo_2))
                {
                    vecinos_desde_el_final.erase(vecinos_desde_el_final.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos_desde_el_final.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos_desde_el_final[i].nodo_2,
                    arbol_de_busqueda_desde_el_final, nodo_actual_desde_el_final.indice_del_nodo,
                    informacion_del_hijo_a_adicionar);

                nodo_a_agregar_agenda = agenda_desde_el_final.crea_nodo_de_agenda(informacion_del_hijo_a_adicionar.nombre_del_nodo,
                    arbol_de_busqueda_desde_el_final.agregar_hijo_a_un_nodo(nodo_actual_desde_el_final.indice_del_nodo,
                        informacion_del_hijo_a_adicionar));

                agenda_desde_el_final.agregar_al_inicio_de_la_agenda(nodo_a_agregar_agenda);
            }
        }

        if (agenda_desde_el_inicio.existe_un_nodo_comun_en_las_agendas(agenda_desde_el_final,
            nodo_encontrado_desde_el_inicio, nodo_encontrado_desde_el_final, arbol_de_busqueda_desde_el_inicio, arbol_de_busqueda_desde_el_final))
            return true;
    }
    return false;
}


bool Busqueda::busqueda_ascenso_a_la_colina(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    Agenda agenda;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    tipo_nodo_informacion informacion_del_nodo_a_comparar_1;
    tipo_nodo_informacion informacion_del_nodo_a_comparar_2;
    informacion_agenda nodo_actual;
    informacion_agenda mejor_nodo;
    informacion_agenda nodo_a_agregar_agenda;
    informacion_agenda nodo_auxiliar_agenda;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    arbol_de_busqueda.crear_arbol(informacion_del_nodo_inicio);
    agenda.borra_agenda();

    nodo_actual = agenda.crea_nodo_de_agenda(informacion_del_nodo_inicio.nombre_del_nodo, 0);

    agenda.agregar_al_final_de_la_agenda(nodo_actual);

    while (!agenda.esta_vacia())
    {
        agenda.devolver_y_eliminar_primer_nodo_de_la_agenda(nodo_actual);

        if (nodo_actual.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual.indice_del_nodo;
            return true;
        }

        grafo.devuelve_vecinos_grafo_no_dirigido(nodo_actual.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual.indice_del_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                nodo_actual.indice_del_nodo, informacion_del_hijo_a_adicionar);
            nodo_a_agregar_agenda = agenda.crea_nodo_de_agenda(informacion_del_hijo_a_adicionar.nombre_del_nodo,
                arbol_de_busqueda.agregar_hijo_a_un_nodo(nodo_actual.indice_del_nodo,
                    informacion_del_hijo_a_adicionar));

            agenda.agregar_al_final_de_la_agenda(nodo_a_agregar_agenda);
        }
        if (agenda.tamano_de_la_agenda() == 0)
            return false;

        agenda.devolver_elemento_de_la_agenda(0, mejor_nodo);
        arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, informacion_del_nodo_a_comparar_1);

        for (unsigned int i = 1; i < agenda.tamano_de_la_agenda(); i++)
        {
            agenda.devolver_elemento_de_la_agenda(i, nodo_auxiliar_agenda);
            arbol_de_busqueda.informacion_de_un_nodo(nodo_auxiliar_agenda.indice_del_nodo, informacion_del_nodo_a_comparar_2);
            if (informacion_del_nodo_a_comparar_1.costo_acumulado <
                informacion_del_nodo_a_comparar_2.costo_acumulado)
            {
                agenda.devolver_elemento_de_la_agenda(i, mejor_nodo);
                arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, informacion_del_nodo_a_comparar_1);
            }
                
        }
            
        agenda.borra_agenda();
        agenda.agregar_al_final_de_la_agenda(mejor_nodo);
    }
    return false;
}

bool Busqueda::busqueda_primero_el_mejor(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    Agenda agenda;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;    
    informacion_agenda nodo_actual;        
    informacion_agenda nodo_a_agregar_agenda;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    arbol_de_busqueda.crear_arbol(informacion_del_nodo_inicio);
    agenda.borra_agenda();

    nodo_actual = agenda.crea_nodo_de_agenda(informacion_del_nodo_inicio.nombre_del_nodo, 0);

    agenda.agregar_al_final_de_la_agenda(nodo_actual);

    while (!agenda.esta_vacia())
    {
        agenda.devolver_y_eliminar_primer_nodo_de_la_agenda(nodo_actual);

        if (nodo_actual.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual.indice_del_nodo;
            return true;
        }

        grafo.devuelve_vecinos_grafo_no_dirigido(nodo_actual.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual.indice_del_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                nodo_actual.indice_del_nodo, informacion_del_hijo_a_adicionar);
            nodo_a_agregar_agenda = agenda.crea_nodo_de_agenda(informacion_del_hijo_a_adicionar.nombre_del_nodo,
                arbol_de_busqueda.agregar_hijo_a_un_nodo(nodo_actual.indice_del_nodo,
                    informacion_del_hijo_a_adicionar));

            agenda.agregar_al_final_de_la_agenda(nodo_a_agregar_agenda);
        }

        agenda.ordenar_por_costo(arbol_de_busqueda);        
    }
    return false;
}

bool Busqueda::busqueda_k_beans(string nodo_inicio, string nodo_final, unsigned int k, int& nodo_encontrado)
{
    Agenda agenda;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    informacion_agenda nodo_actual;
    informacion_agenda nodo_a_agregar_agenda;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    arbol_de_busqueda.crear_arbol(informacion_del_nodo_inicio);
    agenda.borra_agenda();

    nodo_actual = agenda.crea_nodo_de_agenda(informacion_del_nodo_inicio.nombre_del_nodo, 0);

    agenda.agregar_al_final_de_la_agenda(nodo_actual);

    while (!agenda.esta_vacia())
    {
        agenda.devolver_y_eliminar_primer_nodo_de_la_agenda(nodo_actual);

        if (nodo_actual.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual.indice_del_nodo;
            return true;
        }

        grafo.devuelve_vecinos_grafo_no_dirigido(nodo_actual.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual.indice_del_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                nodo_actual.indice_del_nodo, informacion_del_hijo_a_adicionar);
            nodo_a_agregar_agenda = agenda.crea_nodo_de_agenda(informacion_del_hijo_a_adicionar.nombre_del_nodo,
                arbol_de_busqueda.agregar_hijo_a_un_nodo(nodo_actual.indice_del_nodo,
                    informacion_del_hijo_a_adicionar));

            agenda.agregar_al_final_de_la_agenda(nodo_a_agregar_agenda);
        }

        agenda.ordenar_por_costo(arbol_de_busqueda);
        agenda.mantener_solo_k_elementos(k);
    }
    return false;
}

bool Busqueda::busqueda_branch_and_bound(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    Agenda agenda;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;    
    tipo_nodo_informacion info_nodo_auxiliar;    
    informacion_agenda mejor_nodo;    
    unsigned int posicion_del_mejor_nodo = 0;
    informacion_agenda meta_temporal;    
    informacion_agenda info_agenda_auxiliar;
    tipo_nodo_informacion info_mejor_nodo;
    tipo_nodo_informacion info_meta_temporal;
    informacion_agenda nodo_a_agregar_agenda;
    vector<tipo_enlace_de_grafo> vecinos;

    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    arbol_de_busqueda.crear_arbol(informacion_del_nodo_inicio);

    meta_temporal.indice_del_nodo = -1;

    agenda.borra_agenda();

    mejor_nodo = agenda.crea_nodo_de_agenda(informacion_del_nodo_inicio.nombre_del_nodo, 0);

    agenda.agregar_al_final_de_la_agenda(mejor_nodo);

    while (!agenda.esta_vacia())
    {
        posicion_del_mejor_nodo = 0;
        agenda.devolver_elemento_de_la_agenda(0, mejor_nodo);                
        arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, info_mejor_nodo);        

        for (unsigned int i = 1; i < agenda.tamano_de_la_agenda(); i++)
        {
            agenda.devolver_elemento_de_la_agenda(i, info_agenda_auxiliar);
            arbol_de_busqueda.informacion_de_un_nodo(info_agenda_auxiliar.indice_del_nodo, info_nodo_auxiliar);
            if (info_mejor_nodo.costo_acumulado >
                (info_nodo_auxiliar.costo_acumulado))
            {
                posicion_del_mejor_nodo = i;
                agenda.devolver_elemento_de_la_agenda(i, mejor_nodo);
                arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, info_mejor_nodo);
            }
        }

        arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, info_mejor_nodo);
        agenda.eliminar_elemento_de_la_agenda(posicion_del_mejor_nodo);

        if (info_mejor_nodo.nombre_del_nodo == nodo_final)
        {
            if (meta_temporal.indice_del_nodo == -1)
            {
                meta_temporal = mejor_nodo;
                arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, info_meta_temporal);
            }
            else if (info_meta_temporal.costo_acumulado > info_mejor_nodo.costo_acumulado)
            {
                meta_temporal = mejor_nodo;
                arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, info_meta_temporal);
            }

            for (unsigned int i = 0; i < agenda.tamano_de_la_agenda(); i++)
            {
                agenda.devolver_elemento_de_la_agenda(i, info_agenda_auxiliar);
                arbol_de_busqueda.informacion_de_un_nodo(info_agenda_auxiliar.indice_del_nodo, info_nodo_auxiliar);

                if (info_nodo_auxiliar.costo_acumulado >= info_meta_temporal.costo_acumulado)
                {
                    agenda.eliminar_elemento_de_la_agenda(i);
                    i--;
                }
            }

            if (agenda.esta_vacia())
            {
                nodo_encontrado = meta_temporal.indice_del_nodo;
                return true;
            }
        }

        grafo.devuelve_vecinos_grafo_no_dirigido(mejor_nodo.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(mejor_nodo.indice_del_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                mejor_nodo.indice_del_nodo, informacion_del_hijo_a_adicionar);
            if (meta_temporal.indice_del_nodo != -1)                
                if (info_meta_temporal.costo_acumulado <
                    informacion_del_hijo_a_adicionar.costo_acumulado)
                    continue;            
            nodo_a_agregar_agenda = agenda.crea_nodo_de_agenda(informacion_del_hijo_a_adicionar.nombre_del_nodo,
                arbol_de_busqueda.agregar_hijo_a_un_nodo(mejor_nodo.indice_del_nodo,
                    informacion_del_hijo_a_adicionar));

            agenda.agregar_al_final_de_la_agenda(nodo_a_agregar_agenda);
        }
    }

    nodo_encontrado = meta_temporal.indice_del_nodo;
    return (meta_temporal.indice_del_nodo != -1);
}


bool Busqueda::busqueda_A_estrella(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    Agenda agenda;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    tipo_nodo_informacion info_nodo_auxiliar;    
    informacion_agenda mejor_nodo;
    informacion_agenda meta_temporal;
    informacion_agenda info_agenda_auxiliar;
    tipo_nodo_informacion info_mejor_nodo;
    tipo_nodo_informacion info_meta_temporal;
    informacion_agenda nodo_a_agregar_agenda;
    vector<tipo_enlace_de_grafo> vecinos;
    
    unsigned int posicion_del_mejor_nodo = 0;
    float costo_del_mejor_nodo = 0.0f;    

    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    arbol_de_busqueda.crear_arbol(informacion_del_nodo_inicio);

    meta_temporal.indice_del_nodo = -1;

    agenda.borra_agenda();

    mejor_nodo = agenda.crea_nodo_de_agenda(informacion_del_nodo_inicio.nombre_del_nodo, 0);

    agenda.agregar_al_final_de_la_agenda(mejor_nodo);

    while (!agenda.esta_vacia())
    {
        agenda.devolver_elemento_de_la_agenda(0, mejor_nodo);
        arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, info_mejor_nodo);        
        posicion_del_mejor_nodo = 0;
        costo_del_mejor_nodo = info_mejor_nodo.costo_acumulado + grafo.calcula_heuristica_a_la_meta(mejor_nodo.nombre_del_nodo, nodo_final);

        for (unsigned int i = 1; i < agenda.tamano_de_la_agenda(); i++)
        {
            agenda.devolver_elemento_de_la_agenda(i, info_agenda_auxiliar);
            arbol_de_busqueda.informacion_de_un_nodo(info_agenda_auxiliar.indice_del_nodo, info_nodo_auxiliar);

            if (costo_del_mejor_nodo > (info_nodo_auxiliar.costo_acumulado + 
                grafo.calcula_heuristica_a_la_meta(info_nodo_auxiliar.nombre_del_nodo, nodo_final)))
            {
                posicion_del_mejor_nodo = i;
                agenda.devolver_elemento_de_la_agenda(i, mejor_nodo);                                
                costo_del_mejor_nodo = info_mejor_nodo.costo_acumulado + grafo.calcula_heuristica_a_la_meta(info_mejor_nodo.nombre_del_nodo, nodo_final);
            }
        }

        arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, info_mejor_nodo);
        agenda.eliminar_elemento_de_la_agenda(posicion_del_mejor_nodo);

        if (info_mejor_nodo.nombre_del_nodo == nodo_final)
        {
            if (meta_temporal.indice_del_nodo == -1)
            {
                meta_temporal = mejor_nodo;
                arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, info_meta_temporal);
            }
            else if (info_meta_temporal.costo_acumulado > info_mejor_nodo.costo_acumulado)
            {
                meta_temporal = mejor_nodo;
                arbol_de_busqueda.informacion_de_un_nodo(mejor_nodo.indice_del_nodo, info_meta_temporal);
            }

            for (unsigned int i = 0; i < agenda.tamano_de_la_agenda(); i++)
            {
                agenda.devolver_elemento_de_la_agenda(i, info_agenda_auxiliar);
                arbol_de_busqueda.informacion_de_un_nodo(info_agenda_auxiliar.indice_del_nodo, info_nodo_auxiliar);

                if (info_nodo_auxiliar.costo_acumulado >= info_meta_temporal.costo_acumulado)
                {
                    agenda.eliminar_elemento_de_la_agenda(i);
                    i--;
                }
            }

            if (agenda.esta_vacia())
            {
                nodo_encontrado = meta_temporal.indice_del_nodo;
                return true;
            }
        }

        grafo.devuelve_vecinos_grafo_no_dirigido(mejor_nodo.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(mejor_nodo.indice_del_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                mejor_nodo.indice_del_nodo, informacion_del_hijo_a_adicionar);
            if (meta_temporal.indice_del_nodo != -1)
                if (info_meta_temporal.costo_acumulado <
                    informacion_del_hijo_a_adicionar.costo_acumulado)
                    continue;

            informacion_del_hijo_a_adicionar.costo_estimado = grafo.calcula_heuristica_a_la_meta(vecinos[i].nodo_2,
                nodo_final);
            nodo_a_agregar_agenda = agenda.crea_nodo_de_agenda(informacion_del_hijo_a_adicionar.nombre_del_nodo,
                arbol_de_busqueda.agregar_hijo_a_un_nodo(mejor_nodo.indice_del_nodo,
                    informacion_del_hijo_a_adicionar));

            agenda.agregar_al_final_de_la_agenda(nodo_a_agregar_agenda);
        }
    }

    nodo_encontrado = meta_temporal.indice_del_nodo;
    return (meta_temporal.indice_del_nodo != -1);
}

string Busqueda::devolver_ruta(unsigned int nodo_encontrado) const
{
    return arbol_de_busqueda.devolver_ruta_encontrada(nodo_encontrado);
}

string Busqueda::devolver_ruta_bidireccional(int nodo_encontrado_desde_el_inicio, int nodo_encontrado_desde_el_final) const
{
    return arbol_de_busqueda_desde_el_inicio.devolver_la_ruta_encontrada_busqueda_bidireccional(nodo_encontrado_desde_el_inicio, nodo_encontrado_desde_el_final,
        arbol_de_busqueda_desde_el_final);
}


