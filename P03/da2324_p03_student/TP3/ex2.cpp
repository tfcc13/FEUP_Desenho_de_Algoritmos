// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "../data_structures/Graph.h"
#include "MSTTestAux.h"
#include <queue>



template <class T>
std::vector<Vertex<T> *> prim(Graph<T> * g) {
    // TODO

    if (g->getVertexSet().empty()) {
        return g->getVertexSet();
    }

    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex<T>* s = g->getVertexSet().front();
    s->setDist(0);

    priority_queue<Vertex<T>*> priorQueue;

    priorQueue.push(s);

    while(!priorQueue.empty()) {
        Vertex<T>* v = priorQueue.top();
    }

    return g->getVertexSet();

    /* PESUDO CODIGO
     *
     * while (!q.empty())
     *      v = q.extractMin();
     *      v->setVisited(true)
     *      for(auto & e: v->getAdj() {
     *          w = e->getDest();
     *          if(!w->isVisited()) {
     *              oldDist = w->getDist
     *              if(e->getWeight() < oldDist) {
     *                  w->setDist(e->getWeight())
     *                  w->setPath(e)
     *                  if(oldDist == INF) {
     *                      q.push(w);
     *                  }
     *                  else {
     *                      q.decreaseKey();
     *                  }
     *              }
     *          }
     *      }
     *  return g->getVertexSet();
     */
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, test_prim) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = prim(&graph);

    std::stringstream ss;
    for(const auto v : res) {
        ss << v->getInfo() << "<-";
        if ( v->getPath() != nullptr ) {
            ss << v->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    std::cout << ss.str() << std::endl;

    EXPECT_TRUE(isSpanningTree(res));
    EXPECT_EQ(spanningTreeCost(res), 11);
}