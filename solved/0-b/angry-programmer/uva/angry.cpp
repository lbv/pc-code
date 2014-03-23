#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXM 50
#define MAXW 1000

#define Neg(v)  memset((v), -1, sizeof(v))

const int MAX_EDGES = 2 * 2 * (MAXW + MAXM);
const int MAXN      = 2 * MAXM;
const int INF       = MAX_EDGES * 100000 + 100;


struct Edge {
    int v, c, f, o;
    Edge() {}
    Edge(int V, int C, int O) : v(V), c(C), f(0), o(O) {}
};

template <typename ET>
struct Graph {
    ET edges[MAX_EDGES];
    int next[MAX_EDGES], adj[MAXN];
    int n, m;
    void init(int N) { n=N; m=0; Neg(adj); }
    void add(int u, ET e) { next[m] = adj[u], edges[m] = e, adj[u] = m++; }
    void bi_add(int u, int v, int c) {
        add(u, Edge(v, c, m + 1));
        add(v, Edge(u, 0, m - 1));
    }

    // Ford-Fulkerson
    int dist[MAXN], q[MAXN], src, snk;
    bool find_aug_paths() {
        Neg(dist);
        int qfront = -1, qback = 0;
        q[++qfront] = src;
        dist[src] = 0;
        while (qback <= qfront) {
            int u = q[qback++];
            if (u == snk) return true;
            for (int i = adj[u]; i >= 0; i = next[i]) {
                Edge &e = edges[i];
                if (dist[e.v] >= 0 || e.f >= e.c) continue;
                q[++qfront] = e.v;
                dist[e.v] = dist[u] + 1;
            }
        }
        return false;
    }
    int dfs(int u, int f, int d) {
        if (u == snk) return f;
        int ans = 0;
        for (int i = adj[u]; f > 0 && i >= 0; i = next[i]) {
            Edge &e = edges[i];
            if (e.f >= e.c || dist[e.v] != d + 1) continue;
            int r = dfs(e.v, min(f, e.c - e.f), d + 1);
            if (r > 0) e.f += r, edges[e.o].f -= r, ans += r, f -= r;
        }
        return ans;
    }
    int mod_paths() {
        int ans = 0;
        for (int f = dfs(src, INF, 0); f > 0; f = dfs(src,INF, 0))
            ans += f;
        return ans;
    }
    int max_flow(int a, int b) {
        src = a, snk = b;
        int total = 0;
        while (find_aug_paths()) total += mod_paths();
        return total;
    }
};


int M, W;

Graph<Edge> g;


int main()
{
    while (true) {
        scanf("%d%d", &M, &W);
        if (M == 0) break;

        g.init(2 * M);

        g.bi_add(0, 1, INF);
        g.bi_add(2*(M-1), 2*(M-1) + 1, INF);

        for (int i = 2; i < M; ++i) {
            int id, cost;
            scanf("%d%d", &id, &cost);
            --id;
            g.bi_add(2*id, 2*id + 1, cost);
        }

        while (W--) {
            int i, j, c;
            scanf("%d%d%d", &i, &j, &c);
            --i, --j;
            g.bi_add(2*i + 1, 2*j, c);
            g.bi_add(2*j + 1, 2*i, c);
        }

        printf("%d\n", g.max_flow(0, 2*(M - 1) + 1));
    }

    return 0;
}
