#include <algorithm>
#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
using namespace std;


#define MAXK 30
#define MAXN 10

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)
#define Zero(v) memset((v), 0, sizeof(v))


typedef vector<int> IV;


struct Box {
    int n, i;
    int A[MAXN];
    Box() {}
    Box (int N, int I) : n(N), i(I) {}
    void sort() { std::sort(A, A + n); }
    bool nested_in(const Box &x) const {
        for (int j = 0; j < n; ++j)
            if (A[j] >= x.A[j]) return false;
        return true;
    }
    void print() {
        printf(" (%2d)", i);
        for (int i = 0; i < n; ++i)
            printf(" %3d", A[i]);
        puts("");
    }
};

typedef vector<Box>  BV;

//
// Graphs
//
struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }
};


int k, n;

BV boxes;

int root;
int nans;
IV ans;

bool vis[MAXK];
int lpath[MAXK];  // lpath[i]: size of longest path from node i


void dfs(Graph &g, int v)
{
    vis[v] = true;

    lpath[v] = 0;
    cFor (Graph::EL, e, g.adj[v]) {
        if (! vis[e->v])
            dfs(g, e->v);

        if (lpath[e->v] > lpath[v]) lpath[v] = lpath[e->v];
    }
    ++lpath[v];

    if (lpath[v] > nans) {
        nans = lpath[v];
        root = v;
    }
}

void dfs_print(Graph &g, int v)
{
    if (g.adj[v].size() == 0) {
        printf("%d", boxes[v].i);
        return;
    }

    int child, hi;
    hi = 0;
    cFor (Graph::EL, e, g.adj[v])
        if (lpath[e->v] > hi) {
            hi = lpath[e->v];
            child = e->v;
        }

    dfs_print(g, child);
    printf(" %d", boxes[v].i);
}

int main()
{
    while (true) {
        if (scanf("%d%d", &k, &n) != 2) break;

        boxes = BV();

        for (int i = 1; i <= k; ++i) {
            Box b(n, i);
            for (int j = 0; j < n; ++j)
                scanf("%d", &b.A[j]);
            b.sort();
            boxes.push_back(b);
        }

        Zero(vis);
        Graph g(k);

        for (int i = 0; i < k; ++i)
            for (int j = i + 1; j < k; ++j)
                if (boxes[i].nested_in(boxes[j]))
                    g.add(j, i);
                else if (boxes[j].nested_in(boxes[i]))
                    g.add(i, j);

        nans = 0;

        for (int i = 0; i < k; ++i)
            if (! vis[i])
                dfs(g, i);

        printf("%d\n", nans);
        dfs_print(g, root);
        putchar('\n');
    }

    return 0;
}
