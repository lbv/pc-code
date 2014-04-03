#include <cstdio>
#include <list>
#include <set>
#include <vector>
using namespace std;


const int INF = 20000 * 1000 + 100;

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef vector<bool> BV;
typedef vector<int>  IV;


// Weighted adjacency lists
typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    struct Node {
        int u, v, d;
        Node (int U, int V, int D) : u(U), v(V), d(D) {}

        bool operator<(const Node &x) const { return d < x.d; }
    };

    int dijkstra(int s, int t) {
        multiset<Node> q;
        IV dis(n, INF);
        IV ways(n);
        BV vis(n);
        ways[s] = 1;

        q.insert(Node(s, s, 0));
        dis[s] = 0;

        while (! q.empty()) {
            Node nd = *(q.begin()); q.erase(q.begin());

            int u = nd.u, v = nd.v, d = nd.d;

            if (v == t && d > dis[v]) break;

            if (u != v && d == dis[v])
                ways[v] += ways[u];

            if (vis[v]) continue;
            vis[v] = true;

            For (EL, e, adj[v]) {
                int d2 = d + e->w;
                if (d2 <= dis[e->v]) {
                    dis[e->v] = d2;
                    q.insert(Node(v, e->v, d2));
                }
            }
        }

        /*
        for (int i = 0; i < n; ++i)
            printf("   ways(%d): %d\n", i, ways[i]);
            */
        return ways[t];
    }
};


int P, M, N, R;


int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d%d", &P, &M, &N, &R);

        Graph g(N);
        while (R--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g.add(u, v, w);
            g.add(v, u, w);
        }

        printf("Case %d: %d\n", ++ncase, g.dijkstra(P, M));
    }

    return 0;
}
