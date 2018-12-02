#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
#include <memory>
#include <sstream>

class Graph {
private:
    typedef int EdgeIndexType;

    struct Edge {
        typedef std::shared_ptr<Edge> Ptr;
        EdgeIndexType next;
        unsigned to;
        int weight;
        Edge(): next(-1) {}
        Edge(const EdgeIndexType &nxt, const unsigned &v, const int &w): next(nxt), to(v), weight(w) {}
    };

    unsigned n, numEdge = 0;
    std::vector<EdgeIndexType> head;
    std::vector<unsigned> indeg;
    std::vector<Edge::Ptr> edges;

    void addEdge(const unsigned &from, const unsigned &to, const int &weight);
    bool topoSort();

    struct greater_t {
        bool operator()(const Edge::Ptr x, const Edge::Ptr y) const {
            return x->weight > y->weight;
        }
    };

public:
    Graph(const unsigned &n): n(n), head(n, -1), indeg(n, 0) {} 
    void init();
    void print();
    void isDAG();
    void prim();
};

#endif