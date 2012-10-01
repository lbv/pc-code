#include <algorithm>
#include <cstdio>
#include <list>
#include <vector>
using namespace std;


#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef unsigned int u32;

typedef vector<int> IV;


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }

    // Articulations/bridges
    struct Artic {
        IV low, idx;
        IV nbridges;
        int cnt;
        int leaves;
        Graph &g;
        Artic(Graph &G) : g(G) {
            low = IV(g.n);
            idx = IV(g.n);
            nbridges = IV(g.n);
            cnt = 1;
            leaves = 0;
        }
        void dfs(int u, int v) {
            int children = 0;
            int bridges = 0;
            low[v] = idx[v] = cnt++;
            cFor(EL, e, g.adj[v]) {
                if (idx[e->v] == 0) {
                    ++children;
                    dfs(v, e->v);
                    low[v] = min(low[v], low[e->v]);

                    bridges += nbridges[e->v];

                    if (low[e->v] == idx[e->v]) {
                        ++bridges;
                        if (nbridges[e->v] == 0)
                            ++leaves;
                    }
                }
                else if (e->v != u)
                    low[v] = min(low[v], idx[e->v]);
            }

            nbridges[v] = bridges;
            if (u == v && g.adj[v].size() == 1)
                ++leaves;
        }
    };
    int solve() {
        Artic a(*this);
        a.dfs(0, 0);
        return (a.leaves + 1) / 2;
    }
};


int n, m;


int main()
{
    Reader rr;

    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        m = rr.next_u32();

        Graph g(n);

        while (m--) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            g.add(u, v);
            g.add(v, u);
        }

        printf("Case %d: %d\n", ++ncase, g.solve());
    }

    return 0;
}
