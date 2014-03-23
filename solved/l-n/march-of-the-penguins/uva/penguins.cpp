#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;


#define MAXN 100
#define EPS  (1e-8)

#define Neg(v)  memset((v), -1, sizeof(v))

const int MAX_V = 2 * MAXN + 1;
const int MAX_E = MAX_V * (MAX_V - 1);
const int INF   = 10 * MAXN + 100;


template <typename T>
struct Point {
    T x, y;
    Point() { x=y=0; }
    Point(T X, T Y) : x(X), y(Y) {}
    T distance(const Point &p) const {
        T dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }
};

struct Edge {
    int v, c, f, o;
    Edge() {}
    Edge(int V, int C, int O) : v(V), c(C), f(0), o(O) {}
};

template <typename ET>
struct Graph {
    ET edges[MAX_E];
    int next[MAX_E], adj[MAX_V];
    int n, m;
    void init(int N) { n=N; m=0; Neg(adj); }
    void add(int u, ET e) { next[m] = adj[u], edges[m] = e, adj[u] = m++; }
    void bi_add(int u, int v, int c) {
        add(u, Edge(v, c, m + 1));
        add(v, Edge(u, 0, m - 1));
    }

    // Ford-Fulkerson
    int dist[MAX_V], q[MAX_V], src, snk;
    bool find_aug_paths() {
        Neg(dist);
        int qfront = -1, qback = 0;
        q[++qfront] = src;
        dist[src] = 0;
        while (qback <= qfront) {
            int u = q[qback++];
            if (u == snk) return true;
            for (int i = adj[u]; i >= 0; i = next[i]) {
                Edge &e = edges[i];
                if (dist[e.v] >= 0 || e.f >= e.c) continue;
                q[++qfront] = e.v;
                dist[e.v] = dist[u] + 1;
            }
        }
        return false;
    }
    int dfs(int u, int f, int d) {
        if (u == snk) return f;
        int ans = 0;
        for (int i = adj[u]; f > 0 && i >= 0; i = next[i]) {
            Edge &e = edges[i];
            if (e.f >= e.c || dist[e.v] != d + 1) continue;
            int r = dfs(e.v, min(f, e.c - e.f), d + 1);
            if (r > 0) e.f += r, edges[e.o].f -= r, ans += r, f -= r;
        }
        return ans;
    }
    int mod_paths() {
        int ans = 0;
        for (int f = dfs(src, INF, 0); f > 0; f = dfs(src,INF, 0))
            ans += f;
        return ans;
    }
    int max_flow(int a, int b) {
        src = a, snk = b;
        int total = 0;
        while (find_aug_paths()) total += mod_paths();
        return total;
    }
    void clear_flows() {
        for (int i = 0; i < m; ++i)
            edges[i].f = 0;
    }
};


bool eps_leq(double a, double b) { return b - a >= EPS; }


int    N;
double D;
int    p[MAXN];  // number of penguins on each floe
int    r[MAXN];  // number of jumps each floe resist
int    total;    // number of penguins

Point<double> floes[MAXN];
Graph<Edge>   g;


void solve()
{
    g.init(2*N + 1);
    int src = 2*N;

    for (int i = 0; i < N; ++i) {
        g.bi_add(src, 2*i, p[i]);
        g.bi_add(2*i, 2*i + 1, r[i]);
    }

    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            if (eps_leq(floes[i].distance(floes[j]), D)) {
                g.bi_add(2*i + 1, 2*j, INF);
                g.bi_add(2*j + 1, 2*i, INF);
            }

    bool found = false;
    for (int i = 0; i < N; ++i) {
        g.clear_flows();
        if (g.max_flow(src, 2*i) == total) {
            if (found) putchar(' ');
            else found = true;

            printf("%d", i);
        }
    }

    if (! found)
        puts("-1");
    else
        putchar('\n');
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%lf", &N, &D);

        total = 0;
        for (int i = 0; i < N; ++i) {
            double x, y;
            scanf("%lf%lf%d%d", &x, &y, &p[i], &r[i]);
            floes[i] = Point<double>(x, y);
            total += p[i];
        }
        solve();
    }

    return 0;
}
