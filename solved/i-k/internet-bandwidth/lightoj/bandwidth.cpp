#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100
#define MAXC 5000

#define Neg(v)  memset((v), -1, sizeof(v))
#define Zero(v) memset((v), 0, sizeof(v))

const int INF = 1000 * 5000 + 100;
const int MAX_EDGES = 2 * MAXC;


int n;
int s, t, c;


struct Edge {
    int v, c, f;
    Edge() {}
    Edge(int V, int C, int F) : v(V), c(C), f(F) {}
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


Graph<Edge> g;


int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d%d", &n, &s, &t, &c);

        g.init(n);
        while (c--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            --u, --v;
            g.add(u, Edge(v, w, 0));
            g.add(v, Edge(u, w, 0));
        }

        printf("Case %d: %d\n", ++ncase, g.max_flow(s-1, t-1));
    }

    return 0;
}
