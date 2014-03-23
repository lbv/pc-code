#include <cmath>
#include <cstdio>
#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
using namespace std;


#define MAXN 100
#define INF (1e9)

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)
#define Neg(v)  memset((v), -1, sizeof(v))

const int MaxPoints = 2*MAXN;


typedef vector<bool> BV;
typedef vector<BV>   BVV;

typedef vector<double> DV;
typedef vector<DV>     DVV;

typedef pair<int, int> II;
typedef map<II, int>   IIIM;


struct Point {
    double x, y;
    Point() {}
    Point(double X, double Y) : x(X), y(Y) {}
    Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
    double distance(const Point &p) {
        double dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }
};

struct Vector {
    double x, y;
    Vector(const Point &p) : x(p.x), y(p.y) {}
    double cross(const Vector &v) const { return x * v.y  - y * v.x; }
};


Point pts[MaxPoints + 1];
int np;


//
// Graph
//
typedef double w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    struct Node {
        double d;  // distance
        int u, v;  // current and previous vertices
        int s;     // first vertex visited to form the polygon
        Node(double D, int U, int V, int S) :
            d(D), u(U), v(V), s(S) {}

        bool operator<(const Node &x) const {
            if (d != x.d) return d < x.d;
            if (s != x.s) return s < x.s;
            if (u != x.u) return u < x.u;
            return v < x.v;
        }
    };

    double dijkstra(int src) {
        set<Node> q;

        BVV flg(np, BV(np));

        cFor (EL, e, adj[src])
            q.insert(Node(e->w, src, e->v, e->v));

        while (! q.empty()) {
            Node nd = *(q.begin());
            q.erase(q.begin());

            int u = nd.u, v = nd.v, s = nd.s;
            double d = nd.d;

            if (flg[u][v]) continue;
            flg[u][v] = true;

            Vector v1(pts[v] - pts[u]);

            if (v == src) {
                Vector v2(pts[s] - pts[v]);
                if (v1.cross(v2) > 0) return d * 2.0;
                else continue;
            }

            cFor (EL, e, adj[v]) {
                Vector v2(pts[e->v] - pts[v]);
                if (v1.cross(v2) < 0) continue;
                q.insert(Node(d + e->w, v, e->v, s));
            }
        }

        return -1.0;
    }
};


int n, x, y;

Point bull;

IIIM ids;


double solve(Graph &g)
{
    bool found = false;
    double best = INF;

    for (int i = 0; i < np; ++i) {
        double ans = g.dijkstra(i);

        if (ans < 0.0) continue;

        if (! found) found = true;
        if (ans < best) best = ans;
    }

    return found ? best : -1.0;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &n, &x, &y);

        bull = Point(x, y);

        np = 0;
        ids = IIIM();

        Graph g(2*n);

        for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

            if (ids.find(II(x1, y1)) == ids.end()) {
                ids[II(x1, y1)] = np;
                pts[np++] = Point(x1, y1);
            }
            if (ids.find(II(x2, y2)) == ids.end()) {
                ids[II(x2, y2)] = np;
                pts[np++] = Point(x2, y2);
            }

            int id1 = ids[II(x1, y1)];
            int id2 = ids[II(x2, y2)];

            Vector v1(pts[id1] - bull);
            Vector v2(pts[id2] - bull);

            double dist = pts[id1].distance(pts[id2]);

            if (v1.cross(v2) > 0)
                g.add(id1, id2, dist);
            else
                g.add(id2, id1, dist);
        }

        printf("Case %d: %.8lf\n", ++ncase, solve(g));
    }

    return 0;
}
