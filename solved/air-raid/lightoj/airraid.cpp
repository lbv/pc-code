#include <cstdio>
#include <cstring>
#include <list>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 1000
#define INF  1001

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef unsigned int u32;

typedef queue<int>  IQ;
typedef vector<int> IV;

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

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
    Reader rr;

    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        m = rr.next_u32();

        Zero(src);
        g.init(n + 1);

        IV g1;

        while (m--) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            g.add(u, v);

            if (! src[u]) {
                src[u] = true;
                g1.push_back(u);
            }
        }

        int match = g.hopcroft(g1);

        printf("Case %d: %d\n", ++ncase, n - match);
    }

    return 0;
}
