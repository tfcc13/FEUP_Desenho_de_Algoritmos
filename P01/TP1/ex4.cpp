#include <list>
#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

template <typename T>
list<list<T>> sccTarjan( Graph<T>* g) {
    list<list<T>> res;
    stack<T> s;
    int index = 0;
    //TODO

    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
        v->setProcessing(false);
    }

    for (auto v : g->getVertexSet()) {
        if(!v->isVisited()) {
            dfs_scc(g, v,s,res, index);
        }
    }

    return res;
}

template <typename T>
void dfs_scc(Graph<T> *g, Vertex<T> *v, stack<T> &s, list<list<T>> &l, int &i){
    //TODO
    v->setVisited(true);
    v->setProcessing(true);
    v->setNum(i);
    v->setLow(i);
    i++;
    s.push(v->getInfo());

    for(auto e : v->getAdj()) {
        auto dest = e.getDest();
        if(!dest->isVisited()){
            dfs_scc(g,dest,s,l,i);
            v->setLow(min(v->getLow(),dest->getLow()));
        }

        else if(dest->isProcessing()) {
            v->setLow(min(v->getLow(),dest->getNum()));
        }
    }

    if(v->getNum() == v->getLow()) {
        list<T> comp;

        while(true) {
            auto node = s.top();
            s.pop();
            comp.push_back(node);
            if(node == v->getInfo()) {
                break;
            }
        }
        l.push_back(comp);
    }

    v->setProcessing(false);

}