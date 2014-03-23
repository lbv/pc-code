#include <cstdio>
#include <cstring>
#include <list>
#include <set>
#include <vector>
using namespace std;

#define MAXN 10000

const int INF = 600 * 100000 + 10;

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef vector<int> IV;
typedef vector<IV>  IVV;

// Graphs
typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    void init(int N) { n=N; adj.clear(); adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    struct Node {
        int s;  // number of hotel stops made
        int t;  // accumulated travel time from last stop
        int v;  // city
        Node(int S, int T, int V) : s(S), t(T), v(V) {}
        bool operator<(const Node &x) const {
            if (s != x.s) return s < x.s;
            if (t != x.t) return t < x.t;
            return v < x.v;
        }
    };
    typedef set<Node>    NS;

    int dijkstra(bool hs[], int H) {
        NS q;

        // dis[v][s] is the best known distance to reach v after s stops
        IVV dis = IVV(n, IV(H + 1, INF));
        dis[0][0] = 0;

        q.insert(Node(0, 0, 0));

        while (! q.empty()) {
            Node nd = *(q.begin());
            q.erase(q.begin());

            if (nd.v == n - 1)
                return nd.s;

            if (dis[nd.v][nd.s] < nd.t) continue;

            cFor (EL, e, adj[nd.v]) {
                int d = nd.t + e->w;
                if (d <= 600 && d < dis[e->v][nd.s]) {
                    dis[e->v][nd.s] = d;
                    q.insert(Node(nd.s, d, e->v));
                }

                if (! hs[nd.v] || nd.s == H) continue;

                d = e->w;
                if (d <= 600 && d < dis[e->v][nd.s + 1]) {
                    dis[e->v][nd.s + 1] = d;
                    q.insert(Node(nd.s + 1, d, e->v));
                }
            }
        }
        return -1;
    }

};

int n, h, m;
bool hotels[MAXN];
Graph g;

int main()
{
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        Zero(hotels);
        scanf("%d", &h);
        for (int i = 0; i < h; ++i) {
            int c;
            scanf("%d", &c);
            hotels[c - 1] = true;
        }

        g.init(n);
        scanf("%d", &m);
        while (m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            --u, --v;
            g.add(u, v, w);
            g.add(v, u, w);
        }

        printf("%d\n", g.dijkstra(hotels, h));
    }

    return 0;
}
