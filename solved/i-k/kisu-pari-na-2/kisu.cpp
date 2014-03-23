#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100000
#define MAXK 100000

#define Neg(v)  memset((v), -1, sizeof(v))
#define Zero(v) memset((v), 0, sizeof(v))
#define SInf(v) memset((v), 0x7f, sizeof(v))


const int MAX_V = MAXN;
const int MAX_E = MAXN * 2;
const int INF   = 0x7f7f7f7f;


typedef unsigned int u32;


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
    ET edges[MAX_E];
    int next[MAX_E], adj[MAX_V];
    int n, m;
    void init(int N) { n=N; m=0; Neg(adj); }
    void add(int u, ET e) { next[m] = adj[u], edges[m] = e, adj[u] = m++; }
};


int N, M;
int nodes;    // number of nodes of a connected component
int diam;     // diameter of component

int toll[MAXK + 1];
int q[MAXN];
int dist[MAXN];

bool vis1[MAXN];
bool vis2[MAXN];

Graph<Edge> g;


void bfs(int src)
{
    nodes = diam = 0;
    int front = -1, back = 0;
    int farthest = src;

    q[++front] = src;
    vis1[src]  = true;

    while (back <= front) {
        int u = q[back++];

        ++nodes;
        if (dist[u] > diam) diam = dist[u], farthest = u;

        for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
            Edge &e = g.edges[i];

            if (vis1[e.v]) continue;
            q[++front] = e.v;
            dist[e.v] = dist[u] + 1;
            vis1[e.v] = true;
        }
    }

    front = -1, back = 0;

    q[++front]     = farthest;
    vis2[farthest] = true;
    dist[farthest] = 0;
    diam           = 0;

    while (back <= front) {
        int u = q[back++];

        if (dist[u] > diam) diam = dist[u];

        for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
            Edge &e = g.edges[i];

            if (vis2[e.v]) continue;
            q[++front] = e.v;
            dist[e.v] = dist[u] + 1;
            vis2[e.v] = true;
        }
    }
}

void solve()
{
    SInf(toll);

    Zero(vis1);
    Zero(vis2);
    Zero(dist);

    for (int i = 0; i < N; ++i) {
        if (vis1[i]) continue;

        bfs(i);
        for (int i = 1, I = diam + 1; i <= I; ++i)
            toll[i] = i - 1;

        for (int i = diam + 2; i <= nodes; ++i)
            toll[i] = min(toll[i], 2*i - diam - 2);
    }
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        N = rr.next_u32();
        M = rr.next_u32();

        g.init(N);

        while (M--) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            --u, --v;
            g.add(u, Edge(v));
            g.add(v, Edge(u));
        }

        solve();

        printf("Case %d:\n", ++ncase);

        int q = rr.next_u32();
        while (q--) {
            int K = rr.next_u32();
            if (toll[K] == INF)
                puts("impossible");
            else
                printf("%d\n", toll[K]);
        }
    }

    return 0;
}
