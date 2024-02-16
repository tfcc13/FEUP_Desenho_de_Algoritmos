#include "../data_structures/Graph.h"

using namespace std;

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph, to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */
template <typename T>
bool isDAG(const Graph<T>* g)  {
    //TODO

    //inicializa as variáveis usadas a falso e a 0
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
        v->setProcessing(false);
    }

    // chama recursivamente a função de análise dos vértices
    for (auto v: g->getVertexSet()) {
        if(!v->isVisited()) {
            if(!dfsIsDAG(v)) return false;
        }
    }

    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template<class T>
bool dfsIsDAG(Vertex<T> *v)  {
    //TODO
    // marca como visitado
    v->setVisited(true);
    //Marca como em processamento
    v->setProcessing(true);

    /*
     * Processa os destinos dos vértices
     * se o vértice está marcado como estando a ser processado, indica que existe um ciclo
     * se não está a ser processado verifica se foi visitado
     * se não foi visitado chama a função recursivamente
     */
    for (auto e : v->getAdj()) {
        auto dest = e.getDest();
        if (dest->isProcessing()) return false;
        if (!dest->isVisited()) {
            if(!dfsIsDAG(dest)) return false;
        }
    }

    //Ao terminar a análise do vértice, marca-se como não estando a ser processado
    v->setProcessing(false);


    return true;
}

