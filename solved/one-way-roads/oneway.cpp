#include <algorithm>
#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
using namespace std;

namespace Graph {
    struct Edge { int v, w; Edge(int V, int W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    void init(ELV &g, int n) { g.clear(); g.resize(n); }
    void add(ELV &g, int u, int v, int w) { g[u].push_back(Edge(v, w)); }
}

#define MAXN 100
#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v!=c.end(); v++)
#define crFor(t,v,c) for(t::const_reverse_iterator v=c.rbegin();v!=c.rend();v++)

typedef Graph::ELV GT;
GT g;
int cost;
bool flg[MAXN + 1];

void dfs1(int v)
{
    flg[v] = true;
    cFor (Graph::EL, e, g[v]) {
        if (flg[e->v]) continue;
        cost += e->w;
        dfs1(e->v);
        return;
    }
}

void dfs2(int v)
{
    flg[v] = true;
    crFor (Graph::EL, e, g[v]) {
        if (flg[e->v]) continue;
        cost += e->w;
        dfs2(e->v);
        return;
    }
}

int costOf(int from, int to)
{
    cFor (Graph::EL, e, g[from])
        if (e->v == to) return e->w;

    return 0;
}

int mincost()
{
    int c1, c2;

    Zero(flg);
    cost = costOf(g[0].back().v, 0);
    dfs1(0);
    c1 = cost;

    Zero(flg);
    cost = costOf(g[0].front().v, 0);
    dfs2(0);
    c2 = cost;

    return min(c1, c2);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n;
        scanf("%d", &n);
        Graph::init(g, n);
        while (n--) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            a--; b--;
            Graph::add(g, a, b, 0);
            Graph::add(g, b, a, c);
        }

        printf("Case %d: %d\n", ncase++, mincost());
    }

    return 0;
}
