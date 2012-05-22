#include <cstdio>
#include <cstdlib>
#include <list>
#include <vector>
using namespace std;

typedef vector<bool> BV;
typedef vector<int>  IV;

#define MAXN 20000

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Graphs
namespace Graph {
    struct Edge { int v, w; Edge(int V, int W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    void init(ELV &g, int n) { g.clear(); g.resize(n); }
    void add(ELV &g, int u, int v, int w) { g[u].push_back(Edge(v, w)); }
}
using namespace Graph;

ELV g;
BV flg;
IV paths;
int total, N;

void dfs(int v)
{
    flg[v] = true;

    cFor (EL, e, g[v]) {
        if (flg[e->v]) continue;
        dfs(e->v);

        if (e->w < 0) {
            if (paths[e->v] > 0)
                paths[v] += paths[e->v];
            else
                total += abs(paths[e->v]) + 1, paths[v]++;
        }
        else {
            if (paths[e->v] < 0)
                paths[v] += paths[e->v];
            else
                paths[v]--;
        }
    }
}

void solve()
{
    flg.clear();
    flg.resize(N);
    paths.clear();
    paths.resize(N);

    total = 0;
    dfs(0);
    if (paths[0] < 0) total += abs(paths[0]);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%d", &N);
        init(g, N);

        for (int i = 0; i < N-1; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            add(g, u, v, 1);
            add(g, v, u, -1);
        }

        solve();

        printf("Case %d: %d\n", ncase++, total);
    }

    return 0;
}
