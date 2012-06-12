#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <stack>
#include <vector>
using namespace std;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef stack<int>  IK;

typedef vector<bool> BV;
typedef vector<int>  IV;
typedef vector<IV>   IVV;

struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    void init(int N) { n=N; adj.clear(); adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }
    // Kosaraju's algorithm
    struct Kos {
        IVV sccs; IV scc; IK vs; BV vis; ELV radj;
        Kos(int n) { vis = BV(n); radj.resize(n); }
    };
    void kosaraju_scc(IVV &sccs) {
        Kos k(n);
        for (int v=0; v<n; ++v) if (! k.vis[v]) kosaraju_dfs(v, k);
        k.vis = BV(n);
        while (! k.vs.empty()) {
            int v = k.vs.top(); k.vs.pop();
            if (k.vis[v]) continue;
            k.scc = IV();
            kosaraju_dfs2(v, k);
            k.sccs.push_back(k.scc);
        }
        sccs = k.sccs;
    }
    void kosaraju_dfs(int v, Kos &k) {
        k.vis[v] = true;
        cFor (EL, ep, adj[v]) {
            Edge e = *ep;
            int u = e.v; e.v = v;
            k.radj[u].push_back(e);
            if (! k.vis[u]) kosaraju_dfs(u, k);
        }
        k.vs.push(v);
    }
    void kosaraju_dfs2(int v, Kos &k) {
        k.vis[v] = true;
        k.scc.push_back(v);
        cFor (EL, e, k.radj[v])
            if (! k.vis[e->v]) kosaraju_dfs2(e->v, k);
    }
};

struct TwoSat {
    Graph g;
    int n;
    TwoSat(int N) : n(N) { g.init(2*N); }
    void add_cons(int a, bool ta, int b, bool tb) {
        int p = val(a, ta), q = val(b, tb);
        g.add(neg(p), q); g.add(neg(q), p);
    }
    int val(int v, bool t) { return 2*v + (t ? 0 : 1); }
    int neg(int p) { return p ^ 1; }
    bool solve(IV &sol) {
        IVV sccs;
        g.kosaraju_scc(sccs);
        IV vscc(n);
        sol.clear();
        for (int i = 0, I = sccs.size(); i < I; ++i) {
            for (int j=0, J=sccs[i].size(); j < J; ++j) {
                int p = sccs[i][j];
                int v = p/2;
                if (vscc[v] == i+1) return false;
                if (vscc[v] != 0) break;
                vscc[v] = i+1;
                if (p & 1) sol.push_back(v);
            }
        }
        return true;
    }
};

int n, m;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &m);

        TwoSat tsat(m);
        int a, b, i, j;
        bool ta, tb;
        while (n--) {
            scanf("%d%d", &i, &j);
            a = abs(i) - 1;
            b = abs(j) - 1;
            ta = i > 0;
            tb = j > 0;
            tsat.add_cons(a, ta, b, tb);
        }

        IV sol;
        if (tsat.solve(sol)) {
            printf("Case %d: Yes\n", ++ncase);

            sort(sol.begin(), sol.end());
            printf("%d", sol.size());
            for (int i = 0, I = sol.size(); i < I; ++i)
                printf(" %d", sol[i] + 1);
            putchar('\n');
        }
        else
            printf("Case %d: No\n", ++ncase);
    }

    return 0;
}
