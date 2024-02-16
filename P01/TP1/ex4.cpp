#include <list>
#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

template <typename T>
list<list<T>> sccTarjan( Graph<T>* g) {
    list<list<T>> res;
    stack<T> s; // stack para guardar os SCC atual
    int index = 0; //em que indice de chamada está
    //TODO

    //inicializa as variáveis usadas a falso e a 0
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
        v->setProcessing(false);
    }

    //Chama a função auxiliar dfs_scc
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

    //marca como visitado
    v->setVisited(true);

    //marca como a processar
    v->setProcessing(true);

    // indica a posição do vertice no indice
    v->setNum(i);

    //indica na árvore qual é o valor minimo do indice que se pode chegar através do vértice
    v->setLow(i);

    //avança no indice
    i++;

    //empurra para a stack os vértices do SCC
    s.push(v->getInfo());

    //faz visita recursiva
    for(auto e : v->getAdj()) {
        auto dest = e.getDest();
        if(!dest->isVisited()){
            dfs_scc(g,dest,s,l,i);

            //Se o vertice nao foi visitado
            //define o valor minimo de indice possível chegar (este é o valor minimo dos dois vertices em analise)
            v->setLow(min(v->getLow(),dest->getLow()));
        }

        /*Se visitado e está a ser processado então o valor de indice minimo que se pode chegar através
        * do vertice é o menor do vertice V ou do valor do indice do vertice que está a ser processado
         */
        else if(dest->isProcessing()) {
            v->setLow(min(v->getLow(),dest->getNum()));
        }
    }

    //se o valor minimo de v == ao valor do indice atual de v então estamos perante a root do SCC
    if(v->getNum() == v->getLow()) {
        //cria a lista de SCC
        list<T> comp;

        //enquanto a stack não esvazia ou enquanto a o valor do vértice em análise não é igual ao vérticee da stack
       // adiciona-se os vertices da stack ao SCC
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

    //apos terminar a analise do vertice desmarca-se o processamento
    v->setProcessing(false);

}