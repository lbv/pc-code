#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
using namespace std;

#define MAXN 200

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

// Graphs
struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    void init(int N) { n=N; adj.clear(); adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }
};

int n, l;
Graph g;
bool solvable;

int colors[MAXN];

void dfs(int v, int kol)
{
    colors[v] = kol;
    kol = kol == 1 ? 2 : 1;

    cFor (Graph::EL, e, g.adj[v]) {
        if (colors[e->v] == 0)
            dfs(e->v, kol);
        else if (colors[e->v] != kol) {
            solvable = false;
            return;
        }
    }
}

int main()
{
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        g.init(n);

        scanf("%d", &l);

        while (l--) {
            int u, v;
            scanf("%d%d", &u, &v);
            g.add(u, v);
            g.add(v, u);
        }

        Zero(colors);
        solvable = true;

        dfs(0, 1);

        if (solvable)
            puts("BICOLORABLE.");
        else
            puts("NOT BICOLORABLE.");
    }

    return 0;
}
