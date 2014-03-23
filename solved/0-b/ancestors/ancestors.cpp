#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXN 100000

#define Neg(v)  memset((v), -1, sizeof(v))

const int MAX_V = MAXN;
const int MAX_E = MAXN;
const int MINF  = MAXN * (-100) - 100;


typedef unsigned int u32;

typedef vector<int> IV;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};

struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };
template <typename ET>
struct Graph {
    ET edges[MAX_E];
    int next[MAX_E], adj[MAX_V];
    int n, m;
    void init(int N) { n=N; m=0; Neg(adj); }
    void add(int u, ET e) { next[m] = adj[u], edges[m] = e, adj[u] = m++; }
};


int N, K;
int val[MAXN];

Graph<Edge> g;

IV memo[MAXN];

void dfs(int u, IV &kaa)
{
    memo[u] = IV(K + 1);
    memo[u][0] = MINF;

    for (int i = 1; i <= K; ++i) {
        int best = max(kaa[i-1] + val[u], kaa[i]);
        best = max(best, val[u]);
        memo[u][i] = best;
    }

    for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
        Edge &e = g.edges[i];
        dfs(e.v, kaa);
    }

    for (int i = 1; i <= K; ++i)
        kaa[i] = max(kaa[i], memo[u][i]);
}

int main()
{
    Reader rr;
    while (true) {
        N = rr.next_u32();
        K = rr.next_u32();
        if (N == 0) break;

        g.init(N);
        for (int i = 0; i < N; ++i)
            val[i] = rr.next_int();

        for (int v = 1; v < N; ++v) {
            int u = rr.next_u32();
            g.add(u, Edge(v));
        }

        IV kaa(K + 1, MINF);
        dfs(0, kaa);
        printf("%d\n", kaa[K]);
    }

    return 0;
}
