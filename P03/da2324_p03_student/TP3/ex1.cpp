// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "../data_structures/Graph.h"
#include <queue>

template <class T>
void edmondsKarp(Graph<T> *g, int source, int target) {
    // TODO

    // encontra vértice fonte
    Vertex<T> *srcVert = g->findVertex(source);


    // encontra vértice destino
    Vertex<T> *destVert = g->findVertex(target);

    // se os vértices forem iguais ou não existirem termina
    if (srcVert == destVert || srcVert == nullptr || destVert == nullptr) {
        printf("Those vertices don't exist or they are the same");
        return;
    }

    for (auto v: g->getVertexSet()) {
        auto w = v->getAdj();
        for (auto e: w) {
            e->setFlow(0);
        }
    }

    while(findAugmentingPath(g,srcVert,destVert)) {
        double flow = findMinResInPath(srcVert,destVert);
        augmentFlowAlongPath(srcVert,destVert,flow);

    }

    // encontrar as capacidades mínimas das arestas





    //inicialmente coloca-se as aresta com o flow a  0
    // a cada passa usar uma bfs para encontrar o menor caminho de s até t
    // verifico quais as capacidades minimaas das arestas
    // introduz-se esse fluxo minimo no grafo, um fluxo residual
    // ao enviar esse fluxo minimo, significa que se pode receber os fluxos enviados ,
    // atualiza-se aresta com a capacidade restante.
    //soma-se os fluxos introduzidos
    // Vê-se quais caminhos se pode tomar  a seguir
    // Quando não existe mais caminhos possíveis atingiu-se o fluxo máximo

    /*
    auto s = g->findVertex(source);
    auto t = g->findVertex(target);

    if (!s || !t || s == t) {
        return;
    }

    for (auto v: g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
*/

    /*
    while(findAugmentingPath(s,t)) {
       auto f = findMinResidualAlongPath(s,t);
        amountFlowAlongPath(s,t,f);
    }
    return;

}
*/



/* pseudo cósigo
int findAugmentingPath(int s, int t) {
    for (v in VertexSet)
        v->setVisitedFalse
    s-> setVisited(true)
    q.queue()
    q.push(s)
}

 while(!q.empty()&& !t->isVisited()
 {
  v <- q.front,q.pop();

  for(e in v->getAdj() {
    if(!e->getDest()->isVisited() && e->getWight() - e->getFlow() > 0) {
    e->getDest() ->setVisited(True)
    e->getPath();
    q.push(e->getest());
    }
    }
    return
    }
 */

}

template<class T>
void testAndVisit(std::queue<Vertex<T>*> &q, Edge<T> *e, Vertex<T>* w, double residual) {

    // se não tiver capacidade residual passa a frente e não põe em fila o vértice
    if(!w->isVisited() && residual > 0) {
        w->setVisited(true);
        //põe o e como caminho para atingir o w
        w->setPath(e);
        //põe na fila
        q.push(w);
    }
}

template<class T>
bool findAugmentingPath( Graph<T>* g, Vertex<T>* s, Vertex<T>* t) {
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    s->setVisited(true);
    std::queue<Vertex<T>*> q;
    q.push(s);

    //BFS

    while(!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();

        //processa edges de saida
        for (auto e : v->getAdj()) {
            testAndVisit(q, e,e->getDest(), e->getWeight() - e->getFlow());
        }

        // processa incoming Edges
        for(auto e : v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }

    //retorna verdadeiro se for encontrado caminho ate t
    return t->isVisited();
}


template<class T>
double findMinResInPath(Vertex<T>* s, Vertex<T>* t) {
    double flow = INF;


    // percorre os vértices até se chegar ao vértice source, anda-se para trás
    for(auto v = t; v != s;) {
        auto p = v->getPath();
        //para cada caminho verifica-se se a aresta tem como destino o  path
        // (verifica os vertices que estão no path
        if(p->getDest()==v) {
            //verifica e compara o flow minimo com a capacidade restante do vértice em análise
            flow = std::min(flow, p->getWeight() - p->getFlow());
            v = p->getOrig();
        }

        //se o vértice não estiver no caminho  vemos outro vértice no caminho
        else {
            // compara o flow minimo com o flow do vértice atual
            flow = std::min(flow, p->getFlow());
            // muda para outro vértice
            v = p->getDest();

        }

        return flow;
    }


}

template<class T>
void augmentFlowAlongPath(Vertex<T>* s, Vertex<T>* t, double flow) {
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        double currFlow = e->getFlow();

        if(e->getDest() == v) {
            e->setFlow(flow+currFlow);
            v= e->getOrig();
        }
        else  {
            e->setFlow(currFlow-flow);
            v= e->getDest();
        }
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex1, test_edmondsKarp) {
    Graph<int> myGraph;

    for(int i = 1; i <= 6; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 3);
    myGraph.addEdge(1, 3, 2);
    myGraph.addEdge(2, 5, 4);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 3, 1);
    myGraph.addEdge(3, 5, 2);
    myGraph.addEdge(4, 6, 2);
    myGraph.addEdge(5, 6, 3);

    edmondsKarp(&myGraph, 1, 6);

    std::stringstream ss;
    for(auto v : myGraph.getVertexSet()) {
        ss << v->getInfo() << "-> (";
        for (const auto e : v->getAdj())
            ss << (e->getDest())->getInfo() << "[Flow: " << e->getFlow() << "] ";
        ss << ") || ";
    }

    std::cout << ss.str() << std::endl << std::endl;

    EXPECT_EQ("1-> (2[Flow: 3] 3[Flow: 2] ) || 2-> (5[Flow: 1] 4[Flow: 2] 3[Flow: 0] ) || 3-> (5[Flow: 2] ) || 4-> (6[Flow: 2] ) || 5-> (6[Flow: 3] ) || 6-> () || ", ss.str());

}