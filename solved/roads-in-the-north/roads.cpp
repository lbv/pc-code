#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
using namespace std;


#define MAXLINE 128
#define MAXN    10000

#define Zero(v) memset((v), 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef long long i64;


typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }
};


char line[MAXLINE];
Graph g(0);
bool vis[MAXN + 1];
int node;
i64 cost;

void dfs(int v, i64 c)
{
    vis[v] = true;
    if (c > cost) {
        node = v;
        cost = c;
    }

    cFor (Graph::EL, e, g.adj[v]) {
        if (vis[e->v]) continue;
        dfs(e->v, c + e->w);
    }
}

void solve(int root)
{
    Zero(vis);
    cost = 0;
    node = root;
    dfs(root, 0);

    Zero(vis);
    cost = 0;
    dfs(node, 0);
}

int main()
{
    while (true) {
        if (gets(line) == NULL) break;

        g = Graph(MAXN + 1);

        int u, v, w;

        int root = 0;

        while (true) {
            if (sscanf(line, "%d%d%d", &u, &v, &w) != 3) break;
            g.add(u, v, w);
            g.add(v, u, w);
            if (root == 0) root = u;
            if (gets(line) == NULL) break;
        }

        if (root == 0) puts("0");
        else {
            solve(root);
            printf("%lld\n", cost);
        }
    }

    return 0;
}
