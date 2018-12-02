#include <iostream>
#include <cstring>
#include <cstdlib>
#include "graph.h"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    unsigned n;
    std::cin >> n;
    Graph graph(n);
    graph.init();
    graph.isDAG();
    graph.prim();
    return 0;
}