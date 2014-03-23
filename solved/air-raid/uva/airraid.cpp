#include <cstdio>
#include <cstring>
#include <list>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 120
#define INF  121

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef queue<int>  IQ;
typedef vector<int> IV;

// Graphs
struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    void init(int N) { n=N; adj.clear(); adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }

    // Hopcroft-Karp for bipartite matching. Receives the vertices in G1,
    // and depends on vertex #0 being reserved as the NIL vertex
    struct HK {
        IV pair_g1, pair_g2, dist;
        Graph &g;
        IV &g1;
        HK(Graph &G, IV &G1) : g(G), g1(G1) {
            pair_g1 = IV(g.n); pair_g2 = IV(g.n); dist = IV(g.n); }
        bool bfs() {
            IQ q;
            cFor (IV, v, g1) {
                if (pair_g1[*v] == 0) {
                    dist[*v] = 0;
                    q.push(*v);
                }
                else
                    dist[*v] = INF;
            }
            dist[0] = INF;
            while (! q.empty()) {
                int v = q.front(); q.pop();
                cFor (EL, e, g.adj[v]) {
                    int p = pair_g2[e->v];
                    if (dist[p] != INF) continue;
                    dist[p] = dist[v] + 1;
                    q.push(p);
                }
            }
            return dist[0] != INF;
        }
        bool dfs(int v) {
            if (v == 0) return true;
            cFor (EL, e, g.adj[v]) {
                int p = pair_g2[e->v];
                if (dist[p] == dist[v] + 1 && dfs(p)) {
                    pair_g2[e->v] = v;
                    pair_g1[v] = e->v;
                    return true;
                }
            }
            dist[v] = INF;
            return false;
        }
    };
    int hopcroft(IV &g1) {
        HK hk(*this, g1);
        int m = 0;
        while (hk.bfs())
            cFor (IV, v, g1)
                if (hk.pair_g1[*v] == 0 && hk.dfs(*v))
                    ++m;
        return m;
    }
};

int n, m;
bool src[MAXN + 1];
Graph g;

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &n, &m);

        Zero(src);
        g.init(n + 1);

        IV g1;

        while (m--) {
            int u, v;
            scanf("%d%d", &u, &v);
            g.add(u, v);

            if (! src[u]) {
                src[u] = true;
                g1.push_back(u);
            }
        }

        int match = g.hopcroft(g1);

        printf("%d\n", n - match);
    }

    return 0;
}
