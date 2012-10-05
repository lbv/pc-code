#include <cstdio>
#include <list>
#include <set>
#include <vector>
using namespace std;


const int INF = 10000 * 100000 + 100;

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef unsigned int u32;

typedef pair<int, int> II;
typedef vector<int>    IV;
typedef vector<bool>   BV;


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    void dijkstra(int src, IV &dis) {
        set<II> q;
        dis = IV(n, INF);
        BV flg(n);
        q.insert(II(0, src));
        dis[src] = 0;
        while (! q.empty()) {
            II p = *(q.begin()); q.erase(q.begin());
            int d = p.first, v = p.second;
            if (flg[v]) continue;
            flg[v] = true;
            For (EL, e, adj[v]) {
                int d2 = d + e->w;
                if (d2 < dis[e->v]) {
                    dis[e->v] = d2;
                    q.insert(II(d2, e->v));
                }
            }
        }
    }
};

struct FullEdge {
    int u, v, w;
    FullEdge(int U, int V, int W) : u(U), v(V), w(W) {}
};
typedef vector<FullEdge> FV;


int N, M, s, t, p;


int solve(Graph &fg, Graph &rg, FV &edges)
{
    IV dist_orig;
    IV dist_dest;

    fg.dijkstra(s, dist_orig);
    rg.dijkstra(t, dist_dest);

    int ans = -1;

    For (FV, e, edges) {
        int d1 = dist_orig[e->u];
        int d2 = dist_dest[e->v];
        if (d1 == INF || d2 == INF) continue;

        if (d1 + e->w + d2 <= p && e->w > ans)
            ans = e->w;
    }

    return ans;
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    while (T--) {
        N = rr.next_u32();
        M = rr.next_u32();
        s = rr.next_u32();
        t = rr.next_u32();
        p = rr.next_u32();
        --s; --t;

        Graph fg(N);  // forward graph
        Graph rg(N);  // reverse graph
        FV edges;

        while (M--) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            int w = rr.next_u32();

            --u; --v;

            fg.add(u, v, w);
            rg.add(v, u, w);
            edges.push_back(FullEdge(u, v, w));
        }

        printf("%d\n", solve(fg, rg, edges));
    }

    return 0;
}
