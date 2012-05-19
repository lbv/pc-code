#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
using namespace std;

typedef unsigned int u32;

#define MAXN 1000

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

// Graphs
typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj;
    void init(int n) { adj.clear(); adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }
};

Graph g;
int nim[MAXN];
bool vis[MAXN];

void dfs(int u)
{
    int n = 0;
    vis[u] = true;

    cFor (Graph::EL, e, g.adj[u]) {
        if (vis[e->v]) continue;
        dfs(e->v);

        if (e->w == 1)
            n ^= nim[e->v] + 1;
        else
            n ^= nim[e->v] ^ (e->w & 1);
    }

    nim[u] = n;
}

void solve()
{
    Zero(vis);
    dfs(0);
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        int n = rr.next_u32();
        g.init(n);

        for (int i = 0, I = n-1; i < I; ++i) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            int w = rr.next_u32();
            g.add(u, v, w);
            g.add(v, u, w);

        }

        solve();

        printf("Case %d: %s\n", ++ncase, nim[0] == 0 ? "Jolly" : "Emily");
    }

    return 0;
}
