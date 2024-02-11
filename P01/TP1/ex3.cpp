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
            edgesToReverse.push_back({v->getInfo(), dest->getInfo()});
        }
    }

    for (const auto& edge : edgesToReverse) {
        g->removeEdge(edge.first, edge.second);
        g->addEdge(edge.second, edge.first, 0);
    }

}

// Kosaraju-Sharir algorithm to find strongly connected components
template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g)  {
    vector<vector<T>> sccs;
    stack<Vertex<T>*> vertexStack;
    //TODO

    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    for( auto v : g->getVertexSet()) {
        if(!v->isVisited()) {
            firstDFSKosarajuSharir(v, &vertexStack);
        }
    }
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    aux_reverseGraphEdges(g);

    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }



    while(!vertexStack.empty()) {

        auto curr = vertexStack.top();
        vertexStack.pop();
        if(!curr->isVisited()) {
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

    v->setVisited(true);

    for(auto e : v->getAdj()) {
        auto dest = e.getDest();
        if(!dest->isVisited()) {
            firstDFSKosarajuSharir(dest, vertexStack);
        }
    }

    vertexStack->push(v);

}

// Second depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void secondDFSKosarajuSharir(Vertex<T> *v, std::vector<int> & res)  {
    // TODO
    v->setVisited(true);
    res.push_back(v->getInfo());
    for(auto e : v->getAdj()) {
        auto dest = e.getDest();
        if(!dest->isVisited()) {
            secondDFSKosarajuSharir(dest,res);
        }
    }



}
