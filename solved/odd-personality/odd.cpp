#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 10000
#define MAXM 20000

#define Zero(v) memset((v), 0, sizeof(v))
#define Neg(v)  memset((v), -1, sizeof(v))

const int MAX_EDGES = 2 * MAXM;


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};

struct Edge {
    int v, o;
    Edge() {}
    Edge(int V, int O) : v(V), o(O) {}
};

template <typename ET>
struct Graph {
    ET edges[MAX_EDGES];
    int next[MAX_EDGES], adj[MAXN];
    int n, m;
    void init(int N) { n=N; m=0; Neg(adj); }
    void add(int u, ET e) { next[m] = adj[u], edges[m] = e, adj[u] = m++; }
    void bi_add(int u, int v) {
        add(u, Edge(v, m + 1));
        add(v, Edge(u, m - 1));
    }

    // Articulations/bridges
    int low[MAXN], idx[MAXN], cnt;
    bool is_bridge[MAX_EDGES];

    void dfs(int u, int v) {
        int children = 0;
        low[v] = idx[v] = cnt++;
        for (int i = adj[v]; i >= 0; i = next[i]) {
            Edge &e = edges[i];
            if (idx[e.v] == 0) {
                ++children;
                dfs(v, e.v);
                low[v] = min(low[v], low[e.v]);
                if (low[e.v] == idx[e.v])
                    is_bridge[i] = is_bridge[e.o] = true;
            }
            else if (e.v != u)
                low[v] = min(low[v], idx[e.v]);
        }
    }
    void articulations() {
        Zero(idx); Zero(low);
        Zero(is_bridge);
        cnt = 1;
        for (int i = 0; i < n; ++i) if (idx[i] == 0) dfs(i, i);
    }
};


Graph<Edge> g;

int  n, m;
int  q[MAXN];
bool vis_even[MAXN];
bool vis_odd[MAXN];


int bfs(int src)
{
    int front = -1, back = 0;

    q[++front] = src;
    vis_even[src] = true;
    int nodes = 0;

    bool odd_cycle = false;

    while (back <= front) {
        int u = q[back++];
        ++nodes;

        for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
            if (g.is_bridge[i]) continue;
            Edge &e = g.edges[i];

            if (! vis_even[e.v] && ! vis_odd[e.v]) q[++front] = e.v;
            if (vis_even[u] && vis_even[e.v]) odd_cycle = true;

            if (vis_even[u]) vis_odd[e.v] = true;
            if (vis_odd[u]) vis_even[e.v] = true;
        }
    }

    return odd_cycle ? nodes : 0;
}

int solve()
{
    g.articulations();
    Zero(vis_even);
    Zero(vis_odd);

    int ans = 0;
    for (int i = 0; i < n; ++i)
        if (! vis_even[i] && ! vis_odd[i])
            ans += bfs(i);

    return ans;
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        m = rr.next_u32();

        g.init(n);

        while (m--) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            g.bi_add(u, v);
        }

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
