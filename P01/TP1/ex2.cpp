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

    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
        v->setProcessing(false);
    }

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
    v->setVisited(true);
    v->setProcessing(true);

    for (auto e : v->getAdj()) {
        auto dest = e.getDest();
        if (dest->isProcessing()) return false;
        if (!dest->isVisited()) {
            if(!dfsIsDAG(dest)) return false;
        }
    }
    v->setProcessing(false);


    return true;
}

