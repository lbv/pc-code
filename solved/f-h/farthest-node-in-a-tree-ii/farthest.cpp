#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
using namespace std;


#define MAXN 30000

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)
#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};

typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }
};


int n;
int cost[MAXN];
bool vis[MAXN];
int dist;
int node;


void dfs(int u, int c, Graph &g)
{
    vis[u] = true;
    if (c > cost[u]) cost[u] = c;
    if (c > dist) {
        dist = c;
        node = u;
    }

    For (Graph::EL, e, g.adj[u])
        if (! vis[e->v])
            dfs(e->v, c + e->w, g);
}

void solve(Graph &g)
{
    Zero(cost);

    Zero(vis);
    dist = node = 0;
    dfs(0, 0, g);
    int u = node;

    Zero(vis);
    dist = node = 0;
    dfs(u, 0, g);
    int v = node;

    Zero(vis);
    dist = node = 0;
    dfs(v, 0, g);
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();

        Graph g(n);
        for (int i = 1; i < n; ++i) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            int w = rr.next_u32();

            g.add(u, v, w);
            g.add(v, u, w);
        }

        solve(g);
        printf("Case %d:\n", ++ncase);
        for (int i = 0; i < n; ++i)
            printf("%d\n", cost[i]);
    }

    return 0;
}
