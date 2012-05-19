#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> IV;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Union-Find disjoint set
struct Set {
    IV s;
    void init(int n) { s.clear(); for (int i=0; i <= n; ++i) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};

struct Graph {
    struct Edge {
        int u, v, w;
        Edge(int U, int V, int W) : u(U), v(V), w(W) {}
        bool operator<(const Edge &e) const { return w < e.w; }
    };
    typedef vector<Edge> EV;
    EV edges, mst;
    EV *ep, *mp;
    void init(size_t m=16) {
        ep = &edges; mp = &mst;
        edges.clear(); edges.reserve(m);
    }
    void add(int u, int v, int w) { ep->push_back(Edge(u, v, w)); }

    // Minimum Spanning Tree
    void kruskalMST(int n, int &ans) {
        sort(ep->begin(), ep->end());
        Set uf; uf.init(n);
        int nedges = 0;
        ans = 0;
        mp->clear();
        cFor (EV, e, (*ep)) {
            if (uf.find(e->u) == uf.find(e->v)) continue;
            mp->push_back(*e);
            uf.merge(e->u, e->v);
            ans += e->w;
            if (++nedges == n - 1) break;
        }
        if (nedges < n - 1) ans = -1;
        swap(ep, mp);
    }
};

Graph g;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int N, W;
        scanf("%d%d", &N, &W);

        g.init(W);

        printf("Case %d:\n", ++ncase);
        while (W--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g.add(u, v, w);

            int ans;
            g.kruskalMST(N, ans);

            printf("%d\n", ans);
        }
    }

    return 0;
}
