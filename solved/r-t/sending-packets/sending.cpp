#include <cstdio>
#include <list>
#include <set>
#include <utility>
#include <vector>
using namespace std;

typedef vector<bool>   BV;
typedef vector<double> DV;
typedef pair<double, int> DI;
typedef set<DI> DIS;
typedef DIS::iterator Iter;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

#define INF 2.0

// Graphs
namespace Graph {
    struct Edge { int v; double w; Edge(int V, double W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    void init(ELV &g, int n) { g.clear(); g.resize(n); }
    void add(ELV &g, int u, int v, double w) { g[u].push_back(Edge(v, w)); }

    double dijkstra(ELV &g) {
        int n = g.size();
        DIS q;
        DV dis(n);
        BV flg(n);
        dis[0] = 1.0;
        q.insert(DI(1.0, 0));
        while (! q.empty()) {
            Iter it = q.end(); it--;
            double d = it->first;
            int v    = it->second;
            q.erase(it);
            if (flg[v]) continue;
            flg[v] = true;
            if (v == n - 1) return d;
            cFor (EL, e, g[v]) {
                double d = dis[v] * e->w;
                if (!flg[e->v] && d > dis[e->v]) {
                    if (dis[e->v] != 0.0) q.erase(DI(dis[e->v], e->v));
                    dis[e->v] = d;
                    q.insert(DI(dis[e->v], e->v));
                }
            }
        }
        return 0.0;
    }
};

typedef Graph::ELV GT;

GT g;
int N, M, S, K;

double mintime()
{
    double p = Graph::dijkstra(g);
    return 1.0/p * 2*K*S;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%d%d%d%d", &N, &M, &S, &K);

        Graph::init(g, N);
        while (M--) {
            int u, v, p;
            scanf("%d%d%d", &u, &v, &p);
            Graph::add(g, u, v, p/100.0);
            Graph::add(g, v, u, p/100.0);
        }

        printf("Case %d: %.6lf\n", ncase++, mintime());
    }

    return 0;
}
