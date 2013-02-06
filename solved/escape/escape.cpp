#include <cstdio>
#include <cstring>


#define MAXN 100
#define MAXM 10000

#define Neg(v)  memset((v), -1, sizeof(v))
#define Zero(v) memset((v), 0, sizeof(v))

const int MAX_EDGES = 2 * MAXM;


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };

template <typename ET>
struct Graph {
    ET edges[MAX_EDGES];
    int next[MAX_EDGES], adj[MAXN];
    int n, m;
    void init(int N) { n=N; m=0; Neg(adj); }
    void add(int u, ET e) { next[m] = adj[u], edges[m] = e, adj[u] = m++; }
};

int n, m;

Graph<Edge> g;

bool odd[MAXN];
bool even[MAXN];
int  q[2 * MAXN];


void bfs() {
    int front = -1, back = 0;

    q[++front] = 0;

    while (back <= front) {
        int u = q[back++];

        for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
            Edge &e = g.edges[i];

            bool add = false;

            if (! odd[e.v] && (u == 0 || even[u])) odd[e.v] = add = true;
            if (! even[e.v] && odd[u]) even[e.v] = add = true;

            if (add) q[++front] = e.v;
        }
    }
}

int solve()
{
    Zero(odd);
    Zero(even);

    bfs();

    int ans = 0;
    for (int i = 0; i < n; ++i)
        if (even[i]) ++ans;

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &m);
        g.init(n);

        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            --a, --b;
            g.add(a, Edge(b));
            g.add(b, Edge(a));
        }

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
