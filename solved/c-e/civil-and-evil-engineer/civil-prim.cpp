#include <algorithm>
#include <cstdio>
#include <list>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

typedef vector<bool> BV;
typedef vector<int> IV;
typedef pair<int, int> II;
typedef set<II> IIS;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)
#define crFor(t,v,c) \
    for(t::const_reverse_iterator v=c.rbegin(); v != c.rend(); v++)

#define INF (10000 + 10)

// Graphs
namespace Graph {
    struct Edge { int v, w; Edge(int V, int W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    void init(ELV &g, int n) { g.clear(); g.resize(n); }
    void add(ELV &g, int u, int v, int w) { g[u].push_back(Edge(v, w)); }

    int primMin(ELV &g, int src) {
        IIS q;
        int n = g.size();
        IV dis(n, INF);
        BV flg(n);
        dis[src] = 0;
        q.insert(II(0, src));
        int cost = 0;
        while (! q.empty()) {
            int d = q.begin()->first;
            int v = q.begin()->second;
            q.erase(q.begin());
            if (flg[v]) continue;
            flg[v] = true;
            cost += d;
            cFor (EL, e, g[v]) {
                if (!flg[e->v] && e->w < dis[e->v]) {
                    if (dis[e->v] != INF) q.erase(II(dis[e->v], e->v));
                    dis[e->v] = e->w;
                    q.insert(II(dis[e->v], e->v));
                }
            }
        }
        return cost;
    }
    int primMax(ELV &g, int src) {
        set<II> q;
        int n = g.size();
        IV dis(n);
        BV flg(n);
        q.insert(II(0, src));
        int cost = 0;
        while (! q.empty()) {
            int d = (--q.end())->first;
            int v = (--q.end())->second;
            q.erase(--q.end());
            if (flg[v]) continue;
            flg[v] = true;
            cost += d;
            cFor (EL, e, g[v]) {
                if (!flg[e->v] && e->w > dis[e->v]) {
                    if (dis[e->v] != 0) q.erase(II(dis[e->v], e->v));
                    dis[e->v] = e->w;
                    q.insert(II(dis[e->v], e->v));
                }
            }
        }
        return cost;
    }
}

typedef Graph::ELV GT;
GT g;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n;
        scanf("%d", &n);

        Graph::init(g, n + 1);
        while (true) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            if (u == 0 && v == 0 && w == 0) break;
            Graph::add(g, u, v, w);
            Graph::add(g, v, u, w);
        }

        int sum = 0;
        sum += Graph::primMin(g, 0);
        sum += Graph::primMax(g, 0);

        printf("Case %d: ", ncase++);
        if (sum % 2 == 0)
            printf("%d\n", sum/2);
        else
            printf("%d/2\n", sum);
    }
}
