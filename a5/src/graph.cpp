#include "graph.h"

#define is_r_edge(x) (x&1)

bool Graph::topoSort() {
    std::queue<unsigned> degqueue;
    unsigned cnt = 0;
    for (unsigned u = 0; u < n; ++u) if (indeg[u] == 0) degqueue.push(u);
    
    while (!degqueue.empty()) {
        unsigned u = degqueue.front();
        degqueue.pop();
        ++cnt;
        for (int i = head[u]; i != -1; i = edges[i]->next) {
            if (is_r_edge(i)) continue;
            unsigned v = edges[i]->to;
            if (--indeg[v] == 0) degqueue.push(v);
        }
    }
    return cnt == n;
}

void Graph::addEdge(const unsigned &from, const unsigned &to, const int &weight) {
    ++indeg[to]; // in degree
    edges.emplace_back(std::make_shared<Edge>(head[from], to, weight));
    head[from] = numEdge++;
    edges.emplace_back(std::make_shared<Edge>(head[to], from, weight));
    head[to] = numEdge++;
}

void Graph::init() {
    unsigned from, to, weight;
    std::string s;
    while (getline(std::cin, s)) {
        if (s.empty()) continue;
        std::istringstream sin(s);
        sin >> from >> to >> weight;
        addEdge(from, to, weight);
    }
}

void Graph::print() {
    for (unsigned u = 0; u < n; ++u) {
        std::cout << u << std::endl;
        for (int i = head[u]; i != -1 ; i = edges[i]->next) {
            std::cout << u << " " << edges[i]->to << " " << edges[i]->weight << std::endl;
        }
    }
}

void Graph::isDAG() {
    std::cout << "The graph is" << (topoSort() ? " " : " not ") <<  "a DAG" << std::endl;
}

void Graph::prim() {
    int MST = 0;
    unsigned cnt = 1;
    std::priority_queue<Edge::Ptr, std::vector<Edge::Ptr>, greater_t> minHeap;
    std::vector<bool> vis(n, false);
    for (int i = head[0]; i != -1; i = edges[i]->next) minHeap.push(edges[i]);
    vis[0] = true;
    while (!minHeap.empty()) {
        while (!minHeap.empty() && vis[minHeap.top()->to]) minHeap.pop();
        if (minHeap.empty()) break;
        Edge::Ptr e = std::move(minHeap.top());
        minHeap.pop();
        vis[e->to] = true;
        MST += e->weight;
        if (++cnt == n) break;
        for (int i = head[e->to]; i != -1; i = edges[i]->next) minHeap.push(edges[i]);
    }
    if (cnt == n) std::cout << "The total weight of MST is " << MST << '\n';
    else std::cout << "No MST exists!\n";
}