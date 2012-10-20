#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


typedef long long    i64;
typedef unsigned int u32;

typedef vector<int> IV;


#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

struct Set {
    IV s;
    Set(int n) { for (int i=0; i < n; ++i) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};

typedef int w_t;
struct Graph {
    struct Edge {
        int u, v; w_t w;
        Edge(int U, int V, w_t W) : u(U), v(V), w(W) {}
        bool operator<(const Edge &e) const { return w < e.w; }
    };
    typedef vector<Edge> EV;
    EV edges;
    void add(int u, int v, w_t w) { edges.push_back(Edge(u, v, w)); }

    i64 kruskal_mst(int n) {
        sort(edges.begin(), edges.end());
        Set uf(n);
        int nedges = 0;
        i64 ans = 0;
        For (EV, e, edges) {
            if (uf.find(e->u) == uf.find(e->v)) continue;
            uf.merge(e->u, e->v);
            ans += e->w;
            if (++nedges == n - 1) break;
        }
        return ans;
    }
};


int m, n;


int main()
{
    Reader rr;
    while (true) {
        m = rr.next_u32();
        n = rr.next_u32();
        if (m == 0 && n == 0) break;

        Graph g;

        i64 total = 0;
        while (n--) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            int w = rr.next_u32();

            g.add(u, v, w);
            total += w;
        }

        i64 mst = g.kruskal_mst(m);
        printf("%lld\n", total - mst);
    }

    return 0;
}
