#include <cstdio>
#include <cstring>
#include <list>
#include <set>
#include <vector>
using namespace std;

// 10^9
#define INF 1000000000
#define MAXN 5000

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef vector<int> IV;

struct Node {
    int t;  // type of distance (1=best, 2=second best)
    int d;  // distance
    int v;  // vertex
    Node (int T, int D, int V) : t(T), d(D), v(V) {}
    bool operator<(const Node &x) const {
        if (t < x.t) return true;
        if (t > x.t) return false;
        if (d < x.d) return true;
        if (d > x.d) return false;
        return v < x.v;
    }
};

typedef set<Node> NS;

bool vis[3][MAXN];

// Graphs
typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    void init(int N) { n=N; adj.clear(); adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    int dijkstra(int src) {
        NS q;

        IV dis(n, INF);
        IV dis2(n, INF);  // 2nd best distances

        dis[src] = 0;
        q.insert(Node(1, 0, src));

        Zero(vis);

        int v, t, d;
        while (! q.empty()) {
            v = q.begin()->v;
            t = q.begin()->t;
            q.erase(q.begin());

            if (t == 2 && v == n - 1) return dis2[v];

            if (vis[t][v]) continue;
            vis[t][v] = true;

            cFor (EL, e, adj[v]) {
                d = (t == 1 ? dis[v] : dis2[v]) + e->w;
                if (d < dis[e->v]) {
                    dis2[e->v] = dis[e->v];
                    q.insert(Node(2, dis2[e->v], e->v));
                    dis[e->v] = d;
                    q.insert(Node(1, dis[e->v], e->v));
                }
                else if (d > dis[e->v] && d < dis2[e->v]) {
                    dis2[e->v] = d;
                    q.insert(Node(2, dis2[e->v], e->v));
                }
            }
        }
        return -1;
    }
};

int N, R;
Graph g;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &N, &R);
        g.init(N);

        for (int i = 0; i < R; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            --u; --v;
            g.add(u, v, w);
            g.add(v, u, w);
        }

        printf("Case %d: %d\n", ++ncase, g.dijkstra(0));
    }

    return 0;
}
