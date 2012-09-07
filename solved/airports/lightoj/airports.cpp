#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef vector<int> IV;

#define cIter(t)  t::const_iterator
#define cFor(t,v,c)  for(cIter(t) v=c.begin(); v != c.end(); v++)

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 nextU32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

// Union-Find disjoint set
struct Set {
    IV s;
    Set(int n) { for (int i = 0; i <= n; i++) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};

// Graphs
namespace Graph {
    struct FullEdge { int u, v, w;
        FullEdge(int U, int V, int W) : u(U), v(V), w(W) {} };
    typedef vector<FullEdge> FV;
    void init(FV &g, int m) { g.clear(); g.reserve(m); }
    void add(FV &g, int u, int v, int w) { g.push_back(FullEdge(u, v, w)); }
    bool cmpFE(const FullEdge &a, const FullEdge &b) { return a.w < b.w; }

    // Modified Kruskal algorithm, to calculate Y and Z
    void kruskalMST(FV &g, int n, int A, u32 &Y, u32 &Z) {
        sort(g.begin(), g.end(), cmpFE);
        Set set(n);
        int nedges = 0;
        Y = 0;
        cFor (FV, e, g) {
            if (e->w >= A) break;
            if (set.find(e->u) == set.find(e->v)) continue;
            set.merge(e->u, e->v);
            Y += e->w;
            if (++nedges == n - 1) break;
        }
        Z = 0;
        for (int i = 1; i <= n; i++)
            if (set.find(i) == i) {
                Y += A;
                Z++;
            }
    }
}

typedef Graph::FV GT;

GT g;

int main()
{
    Reader rr;
    u32 T = rr.nextU32();

    int ncase = 1;
    while (T--) {
        u32 N = rr.nextU32();
        u32 M = rr.nextU32();
        u32 A = rr.nextU32();

        Graph::init(g, M);
        while (M--) {
            u32 X = rr.nextU32();
            u32 Y = rr.nextU32();
            u32 C = rr.nextU32();
            Graph::add(g, X, Y, C);
        }

        u32 Y, Z;
        Graph::kruskalMST(g, N, A, Y, Z);

        printf("Case %d: %u %u\n", ncase++, Y, Z);
    }

    return 0;
}
