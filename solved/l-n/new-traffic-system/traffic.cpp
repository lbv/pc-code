#include <cstdio>
#include <list>
#include <set>
#include <vector>
using namespace std;


#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

const int INF = (20000 + 10) * 1000 + 10;


typedef unsigned int u32;

typedef vector<int>  IV;
typedef vector<IV>   IVV;


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

struct w_t {
    int d, t;
    w_t (int D, int T) : d(D), t(T) {}
};
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    struct Node {
        int d, v, k;
        Node (int D, int V, int K) : d(D), v(V), k(K) {}
        bool operator<(const Node &x) const { return d < x.d; }
    };

    int dijkstra(int maxk) {
        multiset<Node> q;

        IVV dis(n, IV(maxk + 1, INF));
        vector<u32> vis(n);

        dis[0][0] = 0;
        q.insert(Node(0, 0, 0));

        while (! q.empty()) {
            Node nd = *(q.begin());
            q.erase(q.begin());

            int d = nd.d, v = nd.v, k = nd.k;

            if (vis[v] & ((1 << (k + 1)) - 1)) continue;
            vis[v] |= 1 << k;

            cFor (EL, e, adj[v]) {
                int d2 = d + e->w.d;
                int k2 = e->w.t == 0 ? k : k + 1;
                if (k2 > maxk) continue;

                if (d2 < dis[e->v][k2]) {
                    dis[e->v][k2] = d2;
                    q.insert(Node(d2, e->v, k2));
                }
            }
        }

        int best = INF;
        for (int i = 0; i <= maxk; ++i)
            if (dis[n - 1][i] < best)
                best = dis[n - 1][i];

        return best == INF ? -1 : best;
    }
};


int n, m, k, d;


int main()
{
    Reader rr;

    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        m = rr.next_u32();
        k = rr.next_u32();
        d = rr.next_u32();

        Graph g(n);

        while (m--) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            int w = rr.next_u32();

            g.add(u, v, w_t(w, 0));
        }

        while (k--) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            int w = rr.next_u32();

            g.add(u, v, w_t(w, 1));
        }

        int ans = g.dijkstra(d);

        printf("Case %d: ", ++ncase);
        if (ans >= 0)
            printf("%d\n", ans);
        else
            puts("Impossible");
    }

    return 0;
}
