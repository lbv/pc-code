#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100

#define Neg(v)  memset((v), -1, sizeof(v))

const int MAX_V = 2*MAXN + 2;
const int MAX_E = MAX_V * (MAX_V - 1);
const int INF   = MAX_E * 1000 + 100;


struct Edge {
    int v, c, f, o;
    Edge() {}
    Edge(int V, int C, int O) : v(V), c(C), f(0), o(O) {}
};

template <typename ET>
struct Graph {
    ET edges[MAX_E];
    int next[MAX_E], adj[MAX_V];
    int n, m;
    void init(int N) { n=N; m=0; Neg(adj); }
    void add(int u, ET e) { next[m] = adj[u], edges[m] = e, adj[u] = m++; }
    void bi_add(int u, int v, int c) {
        add(u, Edge(v, c, m + 1));
        add(v, Edge(u, 0, m - 1));
    }

    // Ford-Fulkerson
    int dist[MAX_V], q[MAX_V], src, snk;
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

int N, M, B, D;

Graph<Edge> g;


int main()
{
    while (true) {
        if (scanf("%d", &N) != 1) break;
        g.init(2*N + 2);

        for (int i = 0; i < N; ++i) {
            int C;
            scanf("%d", &C);
            g.bi_add(2*i, 2*i + 1, C);
        }

        scanf("%d", &M);
        while (M--) {
            int i, j, C;
            scanf("%d%d%d", &i, &j, &C);
            --i, --j;
            g.bi_add(2*i + 1, 2*j, C);
        }

        int src = 2*N, snk = 2*N + 1;
        scanf("%d%d", &B, &D);
        while (B--) {
            int idx;
            scanf("%d", &idx);
            --idx;
            g.bi_add(src, 2*idx, INF);
        }
        while (D--) {
            int idx;
            scanf("%d", &idx);
            --idx;
            g.bi_add(2*idx + 1, snk, INF);
        }

        printf("%d\n", g.max_flow(src, snk));
    }

    return 0;
}
