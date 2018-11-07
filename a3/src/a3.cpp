#include <iostream>
#include "unsorted_heap.h"
#include "binary_heap.h"
#include "fib_heap.h"

#define MAXN 5010
#define MAXM 5010

int map[MAXN][MAXM];

struct coord {
    unsigned x, y;
} s, t;

unsigned m, n;

void read() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> m >> n;
    std::cin >> s.x >> s.y >> t.x >> t.y;
    for (unsigned i = 0; i < n; ++i)
        for (unsigned j = 0; j < m; ++j)
            std::cin >> map[i][j];
}

void dijkstra() {
    
}

int main(int argc, char **argv) {
    read();
    dijkstra();
    return 0;
}