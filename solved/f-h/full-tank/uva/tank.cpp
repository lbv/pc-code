#include <cstdio>
#include <list>
#include <set>
#include <vector>
using namespace std;


#define MAXN 1000
const int INF = 1000 * 100 * 100 + 10;

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef vector<int> IV;
typedef vector<IV>  IVV;


int fuel[MAXN];


typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    struct Node {
        int d, v, f;  // distance, vertex, fuel
        Node (int D, int V, int F) : d(D), v(V), f(F) {}
        bool operator<(const Node &x) const { return d < x.d; }
    };
    int dijkstra(int c, int s, int t) {
        multiset<Node> q;
        IVV dis(n, IV(c + 1, INF));
        IV vis(n, -1);

        q.insert(Node(0, s, 0));
        dis[s][0] = 0;

        while (! q.empty()) {
            Node nd = *(q.begin()); q.erase(q.begin());

            int d = nd.d, v = nd.v, f = nd.f;
            if (v == t) return d;

            if (vis[v] >= f) continue;
            vis[v] = f;

            if (f < c && d + fuel[v] < dis[v][f + 1]) {
                dis[v][f + 1] = d + fuel[v];
                q.insert(Node(d + fuel[v], v, f + 1));
            }

            For (EL, e, adj[v]) {
                if (e->w > f) continue;

                int left = f - e->w;
                if (d < dis[e->v][left]) {
                    dis[e->v][left] = d;
                    q.insert(Node(d, e->v, left));
                }
            }
        }
        return -1;
    }
};


int n, m, q;


int main()
{
    while (true) {
        if (scanf("%d%d", &n, &m) != 2) break;
        for (int i = 0; i < n; ++i) scanf("%d", &fuel[i]);

        Graph g(n);
        while (m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);

            g.add(u, v, w);
            g.add(v, u, w);
        }

        scanf("%d", &q);
        while (q--) {
            int c, s, t;
            scanf("%d%d%d", &c, &s, &t);

            int ans = g.dijkstra(c, s, t);
            if (ans < 0)
                puts("impossible");
            else
                printf("%d\n", ans);
        }
    }

    return 0;
}
