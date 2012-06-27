#include <algorithm>
#include <cstdio>
#include <list>
#include <vector>
using namespace std;

#define BUFSIZE 15

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef unsigned int u32;

typedef pair<int, int> II;

typedef vector<int> IV;
typedef vector<II>  IIV;

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
    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
};

// Graphs
struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    void init(int N) { n=N; adj.clear(); adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }

    // Articulations/bridges
    struct Artic {
        IV low, idx;
        IIV bridges;
        int cnt;
        Graph &g;
        Artic(Graph &G) : g(G) { low = IV(g.n); idx = IV(g.n); cnt = 1; }
        void dfs(int u, int v) {
            low[v] = idx[v] = cnt++;
            cFor(EL, e, g.adj[v]) {
                if (idx[e->v] == 0) {
                    dfs(v, e->v);
                    low[v] = min(low[v], low[e->v]);
                    if (low[e->v] == idx[e->v])
                        bridges.push_back(II(min(v, e->v), max(v, e->v)));
                }
                else if (e->v != u)
                    low[v] = min(low[v], idx[e->v]);
            }
        }
    };
    void articulations(IIV &bridges) {
        Artic a(*this);
        for (int i = 0; i < n; ++i)
            if (a.idx[i] == 0) a.dfs(i, i);
        bridges = a.bridges;
    }
};

char buf[BUFSIZE + 1];
int n;
Graph g;

int main()
{
    Reader rr;
    u32 T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();

        g.init(n);

        int u, k, v;
        for (int i = 0; i < n; ++i) {
            u = rr.next_u32();
            rr.next(buf);
            sscanf(buf, "(%d)", &k);

            while (k--) {
                v = rr.next_u32();
                g.add(u, v);
            }
        }

        IIV bridges;
        g.articulations(bridges);

        sort(bridges.begin(), bridges.end());

        printf("Case %d:\n%d critical links\n", ++ncase, bridges.size());
        cFor (IIV, p, bridges)
            printf("%d - %d\n", p->first, p->second);
    }

    return 0;
}
