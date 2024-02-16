#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

// Helper function to reverse the edges of a directed graph
template <typename T>
void aux_reverseGraphEdges(Graph<T>* g) {
    // TODO
    std::vector<std::pair<T, T>> edgesToReverse;
    for (auto& v : g->getVertexSet()) {
        for(auto& e : v->getAdj()) {
            auto dest = e.getDest();
            //Guarda as edges a serem reversas posteriormete, para não entrar num loop de edges adicionadas e retiradas
            edgesToReverse.push_back({v->getInfo(), dest->getInfo()});
        }
    }

    // Adiciona as edges inversas
    for (const auto& edge : edgesToReverse) {
        g->removeEdge(edge.first, edge.second);
        g->addEdge(edge.second, edge.first, 0);
    }

}

// Kosaraju-Sharir algorithm to find strongly connected components
template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g)  {
    vector<vector<T>> sccs;
    stack<Vertex<T>*> vertexStack; //Stack de vértices a ser processadas
    //TODO

    //variáveis usadas a falso
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }


    // faz uma dfs para adicionar os vértices a processar à stack
    for( auto v : g->getVertexSet()) {
        if(!v->isVisited()) {
            firstDFSKosarajuSharir(v, &vertexStack);
        }
    }

    //como as variáveis são reutilizadas é necessário pôr-las a falso novamente
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    //chama a função que adiciona as edges invertidas
    aux_reverseGraphEdges(g);

    //como as variáveis são reutilizadas é necessário pôr-las a falso novamente
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }


    /*
     * Processa os vértices na stack
     * chama a segunda dfs e adiciona um vector de inteiros ao vector de vector de inteiros
     */
    while(!vertexStack.empty()) {

        auto curr = vertexStack.top();
        vertexStack.pop();
        if(!curr->isVisited()) {
            //garante a criação de um vetor diferente a cada chamada recursiva da segunda dfs
            vector<int> res;
            secondDFSKosarajuSharir(curr, res);
            sccs.push_back(res);
        }

    }



    return sccs;
}

// First depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void firstDFSKosarajuSharir(Vertex<T> *v, stack<Vertex <T> *> *vertexStack)  {
    // TODO

    //marca como visitado
    v->setVisited(true);

    //dfs do grafo
    for(auto e : v->getAdj()) {
        auto dest = e.getDest();
        if(!dest->isVisited()) {
            firstDFSKosarajuSharir(dest, vertexStack);
        }
    }

    //Adiciona o vértice processado à stack pela ordem de visita
    vertexStack->push(v);

}

// Second depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void secondDFSKosarajuSharir(Vertex<T> *v, std::vector<int> & res)  {
    // TODO
    //marca como visitado
    v->setVisited(true);

    //adiciona ao vetor os numeros dos vértices processadas na chamada recursiva atual
    res.push_back(v->getInfo());
    for(auto e : v->getAdj()) {
        auto dest = e.getDest();
        if(!dest->isVisited()) {
            secondDFSKosarajuSharir(dest,res);
        }
    }



}
