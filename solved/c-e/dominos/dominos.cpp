#include <cstdio>
#include <cstring>
#include <list>
#include <stack>
#include <vector>
using namespace std;


#define MAXN 100000

#define Zero(v) memset((v), 0, sizeof(v))
#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef stack<int> IK;

typedef vector<bool> BV;
typedef vector<int>  IV;
typedef vector<IV>   IVV;


// Adjacency lists
struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }

    // Kosaraju's algorithm
    struct Kos {
        Graph &g; IVV sccs; IV scc; IK vs; BV vis; ELV radj;
        Kos(Graph &G) : g(G) { vis = BV(g.n); radj.resize(g.n); }
        void dfs(int v) {
            vis[v] = true;
            For (EL, ep, g.adj[v]) {
                Edge e = *ep;
                int u = e.v; e.v = v;
                radj[u].push_back(e);
                if (! vis[u]) dfs(u);
            }
            vs.push(v);
        }
        void dfs2(int v) {
            vis[v] = true;
            scc.push_back(v);
            For (EL, e, radj[v]) if (! vis[e->v]) dfs2(e->v);
        }
    };
    void kosaraju_scc(IVV &sccs) {
        Kos k(*this);
        for (int v=0; v<n; ++v) if (! k.vis[v]) k.dfs(v);
        k.vis = BV(n);
        while (! k.vs.empty()) {
            int v = k.vs.top(); k.vs.pop();
            if (k.vis[v]) continue;
            k.scc = IV();
            k.dfs2(v);
            k.sccs.push_back(k.scc);
        }
        sccs = k.sccs;
    }
};


int n, m;
bool vis[MAXN];


void dfs(int v, Graph &g)
{
    vis[v] = true;

    For (Graph::EL, e, g.adj[v])
        if (! vis[e->v]) dfs(e->v, g);
}

int solve(Graph &g)
{
    IVV sccs;
    g.kosaraju_scc(sccs);

    Zero(vis);
    int ans = 0;
    For (IVV, scc, sccs) {
        int v = (*scc)[0];

        if (! vis[v]) {
            ++ans;
            dfs(v, g);
        }
    }

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &n, &m);

        Graph g(n);
        while (m--) {
            int x, y;
            scanf("%d%d", &x, &y);
            --x; --y;
            g.add(x, y);
        }

        printf("%d\n", solve(g));
    }

    return 0;
}
