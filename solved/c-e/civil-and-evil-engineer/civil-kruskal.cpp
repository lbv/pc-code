#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> IV;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)
#define crFor(t,v,c) \
    for(t::const_reverse_iterator v=c.rbegin(); v != c.rend(); v++)

// Union-Find disjoint set
struct Set {
    IV s; int n; Set(int N) : n(N) { init(); }
    void init() { s.clear(); for (int i = 0; i <= n; i++) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};

// Graphs
namespace Graph {
    struct FullEdge { int u, v, w;
        FullEdge(int U, int V, int W) : u(U), v(V), w(W) {} };
    typedef vector<FullEdge> FV;
    void init(FV &g, size_t m=16) { g.clear(); g.reserve(m); }
    void add(FV &g, int u, int v, int w) { g.push_back(FullEdge(u, v, w)); }
    bool cmpFE(const FullEdge &a, const FullEdge &b) { return a.w < b.w; }
    // Minimum Spanning Tree
    void kruskalMST(FV &g, int n, int &sum) {
        sort(g.begin(), g.end(), cmpFE);
        Set set(n);
        sum = 0;
        int nedges = 0;
        cFor (FV, e, g) {
            if (set.find(e->u) == set.find(e->v)) continue;
            set.merge(e->u, e->v);
            sum += e->w;
            if (++nedges == n - 1) break;
        }

        set.init();
        nedges = 0;
        crFor (FV, e, g) {
            if (set.find(e->u) == set.find(e->v)) continue;
            set.merge(e->u, e->v);
            sum += e->w;
            if (++nedges == n - 1) break;
        }
    }
}

typedef Graph::FV GT;
GT g;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n;
        scanf("%d", &n);

        Graph::init(g);
        while (1) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            if (u == 0 && v == 0 && w == 0) break;
            Graph::add(g, u, v, w);
        }

        int sum;
        Graph::kruskalMST(g, n + 1, sum);

        printf("Case %d: ", ncase++);
        if (sum % 2 == 0)
            printf("%d\n", sum/2);
        else
            printf("%d/2\n", sum);
    }
}
