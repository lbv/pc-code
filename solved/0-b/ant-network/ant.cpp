#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 10000
#define MAXM 20000

#define Neg(v)  memset((v), -1, sizeof(v))
#define Zero(v) memset((v), 0, sizeof(v))

const int MAX_EDGES = 2 * MAXM;


typedef unsigned int       u32;
typedef unsigned long long u64;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};

struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };

template <typename ET>
struct Graph {
    ET edges[MAX_EDGES];
    int next[MAX_EDGES], adj[MAXN];
    int n, m;
    void init(int N) { n=N; m=0; Neg(adj); }
    void add(int u, ET e) { next[m] = adj[u], edges[m] = e, adj[u] = m++; }

    // Articulations/bridges
    int low[MAXN], idx[MAXN], cnt;
    bool is_artic[MAXN];

    void dfs(int u, int v) {
        int children = 0;
        low[v] = idx[v] = cnt++;
        for (int i = adj[v]; i >= 0; i = next[i]) {
            Edge &e = edges[i];
            if (idx[e.v] == 0) {
                ++children;
                dfs(v, e.v);
                low[v] = min(low[v], low[e.v]);
                if (low[e.v] >= idx[v] && u != v)
                    is_artic[v] = true;
            }
            else if (e.v != u)
                low[v] = min(low[v], idx[e.v]);
        }
        if (u == v && children > 1)
            is_artic[v] = true;
    }
    void articulations() {
        Zero(idx); Zero(low);
        Zero(is_artic);
        cnt = 1;
        for (int i = 0; i < n; ++i) if (idx[i] == 0) dfs(i, i);
    }
};


int n, m;
int shafts;
u64 ways;

Graph<Edge> g;

bool vis[MAXN];
int  q[MAXN];


// a: stores number of articulations reachable from src (0, 1, or more than
//    1)
// b: stores number of non-articulation nodes reachable from src
void bfs(int src, int &a, int &b)
{
    int front = -1, back = 0;

    q[++front] = src;
    vis[src] = true;

    a = 0, b = 0;
    int last_artic = -1;

    while (back <= front) {
        int u = q[back++];
        ++b;

        for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
            Edge &e = g.edges[i];

            if (g.is_artic[e.v] && e.v != last_artic) {
                ++a;
                last_artic = e.v;
            }

            if (g.is_artic[e.v] || vis[e.v]) continue;
            q[++front] = e.v;
            vis[e.v] = true;
        }
    }
}

void solve()
{
    shafts = 0;
    ways   = 1;

    g.articulations();
    Zero(vis);

    for (int i = 0; i < n; ++i) {
        if (g.is_artic[i] || vis[i]) continue;

        int n_artic, nodes;
        bfs(i, n_artic, nodes);
        if (n_artic == 0) {
            shafts += 2;
            ways *= nodes * (nodes - 1) / 2;
        }
        else if (n_artic == 1) {
            ++shafts;
            ways *= nodes;
        }
    }
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
            g.add(u, Edge(v));
            g.add(v, Edge(u));
        }

        solve();
        printf("Case %d: %d %llu\n", ++ncase, shafts, ways);
    }

    return 0;
}
