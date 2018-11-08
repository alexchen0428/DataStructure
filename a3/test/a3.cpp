#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <getopt.h>
#include "unsorted_heap.h"
#include "binary_heap.h"
#include "fib_heap.h"

#define TEST

#define MAXN 5010
#define MAXM 5010
#define point(u) "(" << u.x << ", " << u.y << ")"

struct coord {
    unsigned x, y;
    int pathcost;
} s, t;

struct compare_t {
    bool operator()(const coord &a, const coord &b) const {
        if (a.pathcost == b.pathcost) {
            if (a.x == b.x) return a.y < b.y;
            return a.x < b.x; 
        }
        return a.pathcost < b.pathcost;
    }
};

enum im_t {UNSORTED, BINARY, FIBONACCI, IM_SIZE};

unsigned m, n;
static unsigned step = 0;
int map[MAXM][MAXN];
bool reached[MAXM][MAXN];
coord pred[MAXM][MAXN];
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

static int v_flag = 0;
static im_t i_flag = IM_SIZE;

const static char *im_name[] = {"UNSORTED", "BINARY", "FIBONACCI"};

bool hasNeighbor(const coord &u, unsigned d) {
    int nx = u.x + dx[d];
    int ny = u.y + dy[d];
    return (nx >= 0 && nx < (int)m && ny >= 0 && ny < (int)n);
}

void read() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> m >> n;
    std::cin >> s.x >> s.y >> t.x >> t.y;
    for (unsigned j = 0; j < n; ++j)
        for (unsigned i = 0; i < m; ++i)
            std::cin >> map[i][j];
}

void trace_helper(const coord &u) {
    if (u.x != s.x || u.y != s.y)
        trace_helper(pred[u.x][u.y]);
    std::cout << point(u) << "\n";    
}

void trace_back_path(const int &dist) {
    std::cout << "The shortest path from " << point(s) << " to " << point(t) << " is " << dist << "." << "\n";
    std::cout << "Path:" << "\n";
    trace_helper(t);
}

void log_u(const coord &u) {
    std::cout << "Step " << step++ << "\n";
    std::cout << "Choose cell " << point(u) << " with accumulated length " <<  u.pathcost << ".\n";
}

void log_v(const coord &v) {
    std::cout << "Cell " << point(v) << " with accumulated length " <<  v.pathcost << " is added into the queue." << "\n";
}

void log_t(const coord &v) {
    std::cout << "Cell " << point(v) << " with accumulated length " <<  v.pathcost << " is the ending point." << "\n";
}

void dijkstra_heap() {
    priority_queue<coord, compare_t> *heap;
    switch (i_flag) {
        case UNSORTED: 
            heap = new unsorted_heap<coord, compare_t>;
            break;
        case BINARY:
            heap = new binary_heap<coord, compare_t>;
            break;
        case FIBONACCI:
            heap = new fib_heap<coord, compare_t>;
            break;
        default:
            return;
    }
    reached[s.x][s.y] = true;
    s.pathcost = map[s.x][s.y];
    heap->enqueue(s);
    while (!heap->empty()) {
        coord u = heap->dequeue_min();
#ifndef TEST
        if (v_flag) log_u(u);
#endif
        for (unsigned d = 0; d < 4; ++d) {
            if (!hasNeighbor(u, d)) continue;
            unsigned nx = u.x + dx[d], ny = u.y + dy[d];
            if (reached[nx][ny]) continue;
            coord v = {nx, ny, u.pathcost + map[nx][ny]};
            reached[nx][ny] = true;
            pred[nx][ny] = u;
            if (t.x == nx && t.y == ny) {
#ifndef TEST
                if (v_flag) log_t(v);
                trace_back_path(v.pathcost);
#endif
                delete heap;
                return;
            }
#ifndef TEST
            if (v_flag) log_v(v);
#endif
            heap->enqueue(v);
        }
    }
}

void getoptions(const int &argc, char **argv) {
    static option long_options[] = {
          {"implementation", required_argument, 0, 'i'},
          {"verbose", no_argument, 0, 'v'},
          {0, 0, 0, 0}
    };

    int option_index = 0, c = -1;
    while ((c = getopt_long(argc, argv, "i:v", long_options, &option_index)) != -1) {
        switch(c) {
            case 'v':
                v_flag = 1;
                break;

            case 'i':
                for (unsigned i = 0; i < IM_SIZE; ++i)
                    if (strcmp(optarg, im_name[i]) == 0) {
                        i_flag = (im_t)i;
                        break;
                    }
                break;
            
            default:
                break;
        }
    }
}

int bg;
double runtime;

void set_clock() {
    bg = clock();
}

void get_clock() {
    runtime = (clock() - bg) * 1.0 / CLOCKS_PER_SEC;
}

int main(int argc, char **argv) {
    getoptions(argc, argv);
    read();
    set_clock();
    dijkstra_heap();
    get_clock();
    std::cout << runtime << "\n";
    return 0;
}