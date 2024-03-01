// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "../data_structures/Graph.h"

template <class T>
void edmondsKarp(Graph<T> *g, int source, int target) {
    // TODO

    //inicialmente coloca-se as aresta com o flow a  0
    // a cada passa usar uma bfs para encontrar o menor caminho de s até t
    // verifico quais as capacidades minimaas das arestas
    // introduz-se esse fluxo minimo no grafo, um fluxo residual
    // ao enviar esse fluxo minimo, significa que se pode receber os fluxos enviados ,
    // atualiza-se aresta com a capacidade restante.
    //soma-se os fluxos introduzidos
    // Vê-se quais caminhos se pode tomar  a seguir
    // Quando não existe mais caminhos possíveis atingiu-se o fluxo máximo


    auto s = g->findVertex(source);
    auto t = g->findVertex(target);

    if(!s || !t || s == t) {
        return ;
    }

    for(auto v : g->getVertexSet()) {
        for(auto e : v->getAdj()) {
            e->setFlow(0);
        }
    }


    while(findAugmentingPath(s,t)) {
       auto f = findMinResidualAlongPath(s,t);
        amountFlowAlongPath(s,t,f);
    }
    return;

}

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