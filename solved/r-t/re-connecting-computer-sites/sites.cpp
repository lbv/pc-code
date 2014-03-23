#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef long long i64;

typedef vector<int> IV;


// Union-Find disjoint set
struct Set {
    IV s;
    Set(int n) { for (int i=0; i <= n; ++i) s.push_back(i); }
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
    EV edges;
    void add(int u, int v, int w) { edges.push_back(Edge(u, v, w)); }

    // Minimum Spanning Tree
    void kruskal_mst(int n, i64 &ans) {
        sort(edges.begin(), edges.end());
        Set uf(n);
        int nedges = 0;
        ans = 0;
        EV mst;
        cFor (EV, e, edges) {
            if (uf.find(e->u) == uf.find(e->v)) continue;
            mst.push_back(*e);
            uf.merge(e->u, e->v);
            ans += e->w;
            if (++nedges == n - 1) break;
        }
        if (nedges < n - 1) ans = -1;
        else edges = mst;
    }
};

Graph g;
int N;

int main()
{
    bool first = true;
    while (true) {
        if (scanf("%d", &N) != 1) break;

        g = Graph();

        i64 cost1 = 0;
        int u, v, w;

        for (int i = 0, I = N - 1; i < I; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            g.add(u - 1, v - 1, w);
            cost1 += w;
        }

        int K;
        scanf("%d", &K);

        while (K--) {
            scanf("%d%d%d", &u, &v, &w);
            g.add(u - 1, v - 1, w);
        }

        int M;
        scanf("%d", &M);

        while (M--) scanf("%*d%*d%*d");

        i64 cost2;
        g.kruskal_mst(N, cost2);

        if (first) first = false;
        else putchar('\n');

        printf("%lld\n%lld\n", cost1, cost2);
    }

    return 0;
}
