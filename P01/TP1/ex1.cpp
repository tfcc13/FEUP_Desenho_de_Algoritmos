#include <iostream>
#include "../data_structures/Graph.h"

using namespace std;
template <typename T>

/****************** toposort ********************/
/*
 * Performs a topological sorting of the vertices of a graph.
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */
vector<T> topsort(const Graph<T>* g) {
    vector<T> res;

    //TODO
    if(!g->isDAG()) return res;

    queue<Vertex<T>*> q;

    for (auto vertex : g->getVertexSet()) {
        vertex->setVisited(false);
        vertex->setIndegree(0);
    }

    for (auto v : g->getVertexSet()) {
        for(auto e : v->getAdj()) {
            auto dest = e.getDest();
            dest->setIndegree(dest->getIndegree()+1);
        }
    }

    for(auto v: g->getVertexSet()) {
        if(v->getIndegree() == 0) {
            q.push(v);
        }
    }

    while(!q.empty()) {
        auto curr = q.front();
        q.pop();
        res.push_back(curr->getInfo());
        for(auto e: curr->getAdj()) {
            auto dest = e.getDest();
            dest->setIndegree(dest->getIndegree()-1);
            if(dest->getIndegree() == 0) {
                q.push(dest);
            }
        }
    }

    return res;
}