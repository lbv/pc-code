#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXM 100
#define MAXW 3000

#define Neg(v)  memset((v), -1, sizeof(v))

const int MAX_EDGES = 2 * MAXW + MAXM;
const int MAXN      = 2 * MAXM;
const int INF       = MAX_EDGES * 100000 + 100;


struct Edge {
    int v, c, f;
    Edge() {}
    Edge(int V, int C) : v(V), c(C), f(0) {}
};

template <typename ET>
struct Graph {
    ET edges[MAX_EDGES];
    int next[MAX_EDGES], adj[MAXN];
    int n, m;
    void init(int N) { n=N; m=0; Neg(adj); }
    void add(int u, ET e) { next[m] = adj[u], edges[m] = e, adj[u] = m++; }

    // Ford-Fulkerson
    int dist[MAXN], q[MAXN];
    bool find_aug_paths(int src, int snk) {
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
    int dfs(int u, int snk, int f, int d) {
        if (u == snk) return f;
        int ans = 0;
        for (int i = adj[u]; f > 0 && i >= 0; i = next[i]) {
            Edge &e = edges[i];
            if (e.f >= e.c || dist[e.v] != d + 1) continue;
            int r = dfs(e.v, snk, min(f, e.c - e.f), d + 1);
            if (r > 0) e.f += r, ans += r, f -= r;
        }
        return ans;
    }
    int mod_paths(int src, int snk) { return dfs(src, snk, INF, 0); }
    int max_flow(int src, int snk) {
        int total = 0;
        while (find_aug_paths(src, snk)) total += mod_paths(src, snk);
        return total;
    }
};


int M, W;

Graph<Edge> g;


int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &M, &W);
        g.init(2 * M);

        g.add(0, Edge(1, INF));
        g.add(2*(M-1), Edge(2*(M-1) + 1, INF));

        for (int i = 1, I = M - 1; i < I; ++i) {
            int cost;
            scanf("%d", &cost);
            g.add(2*i, Edge(2*i + 1, cost));
        }

        while (W--) {
            int i, j, c;
            scanf("%d%d%d", &i, &j, &c);
            --i, --j;

            g.add(2*i + 1, Edge(2*j, c));
            g.add(2*j + 1, Edge(2*i, c));
        }

        printf("Case %d: %d\n", ++ncase, g.max_flow(0, 2*(M - 1) + 1));
    }

    return 0;
}
