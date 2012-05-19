#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef vector<int> IV;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    // Optional methods
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

struct Graph {
    struct Edge {
        int u, v, w;
        Edge(int U, int V, int W) : u(U), v(V), w(W) {}
        bool operator<(const Edge &e) const { return w < e.w; }
    };
    typedef vector<Edge> EV;
    EV edges;
    void init(size_t m=16) { edges.clear(); edges.reserve(m); }
    void add(int u, int v, int w) { edges.push_back(Edge(u, v, w)); }

    // Bellman-Ford
    bool bellman_ford_neg_cycle(int n) {
        IV dis(n);
        for (int i = 0; i < n-1; i++)
            cFor (EV, e, edges)
                if(dis[e->u] + e->w < dis[e->v])
                    dis[e->v] = dis[e->u] + e->w;
        cFor (EV, e, edges)
            if (dis[e->u] + e->w < dis[e->v])
                return true;
        return false;
    }
};

Graph g;

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        int N = rr.next_u32();
        int R = rr.next_u32();
        int P = rr.next_u32();

        g.init(R);

        int A, B, I, E;
        while (R--) {
            A = rr.next_u32();
            B = rr.next_u32();
            I = rr.next_u32();
            E = rr.next_u32();

            g.add(A, B, E*P - I);
        }

        printf("Case %d: %s\n", ++ncase,
               g.bellman_ford_neg_cycle(N) ? "YES" : "NO");
    }

    return 0;
}
