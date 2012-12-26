#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
using namespace std;


#define MAXN 100000

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)
#define Zero(v) memset((v), 0, sizeof(v))


typedef long long    i64;
typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};

// Adjacency lists
struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }
};


int N;
i64 pairs;
int children[MAXN];


void dfs(int u, Graph &g)
{
    i64 c = 0;
    For (Graph::EL, e, g.adj[u]) {
        dfs(e->v, g);

        if (c != 0)
            pairs += c * (children[e->v] + 1);

        c += children[e->v] + 1;
    }
    children[u] = c;
}

void solve(Graph &g)
{
    pairs = 0;
    Zero(children);

    dfs(0, g);
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        N = rr.next_u32();
        Graph g(N);

        for (int i = 1; i < N; ++i) {
            int u = rr.next_u32();
            int v = rr.next_u32();
            g.add(u - 1, v - 1);
        }

        solve(g);
        printf("Case %d: %d %lld\n", ++ncase, N - 1, pairs);
    }

    return 0;
}
