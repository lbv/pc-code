#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 100

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef vector<int> IV;


typedef double p_t;
struct Point {
    p_t x, y;
    Point(p_t X=0, p_t Y=0) : x(X), y(Y) {}
    p_t distance(const Point &p) {
        p_t dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }
};

struct Set {
    IV s;
    Set(int n) { for (int i=0; i < n; ++i) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};

typedef double w_t;
struct Graph {
    struct Edge {
        int u, v; w_t w;
        Edge(int U, int V, w_t W) : u(U), v(V), w(W) {}
        bool operator<(const Edge &e) const { return w < e.w; }
    };
    typedef vector<Edge> EV;
    EV edges;
    void add(int u, int v, w_t w) { edges.push_back(Edge(u, v, w)); }

    void kruskal_mst(int n, double &ans) {
        sort(edges.begin(), edges.end());
        Set uf(n);
        int nedges = 0;
        ans = 0;
        For (EV, e, edges) {
            if (uf.find(e->u) == uf.find(e->v)) continue;
            uf.merge(e->u, e->v);
            ans += e->w;
            if (++nedges == n - 1) break;
        }
    }
};


int n;
Point pts[MAXN];


int main()
{
    int T;
    scanf("%d", &T);

    bool first = true;
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            pts[i] = Point(x, y);
        }

        Graph g;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                g.add(i, j, pts[i].distance(pts[j]));

        if (first) first = false;
        else       putchar('\n');

        double ans;
        g.kruskal_mst(n, ans);
        printf("%.2lf\n", ans);
    }

    return 0;
}
