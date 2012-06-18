#include <algorithm>
#include <cstdio>
#include <list>
#include <stack>
#include <vector>
using namespace std;

#define MAXK 5

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef vector<bool> BV;
typedef vector<int>  IV;
typedef vector<IV>   IVV;

typedef stack<int> IK;

// Graphs
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


// 2-SAT
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

    Graph backup;

    void save() {
        backup = g;
    }

    void restore() {
        g = backup;
    }
};

int n, m, k;
int council[MAXK][4];

IV sol;

bool dfs(TwoSat &tsat, int idx, IV pre)
{
    int v;
    bool t, res;

    for (int i = 1; i <= 3; ++i) {
        tsat.restore();
        for (int j = 0; j < idx; ++j) {
            v = council[j][pre[j]];
            t = council[j][0] == 1;

            tsat.add_cons(v, t, v, t);
        }

        v = council[idx][i];
        t = council[idx][0] == 1;
        tsat.add_cons(v, t, v, t);

        res = tsat.solve(sol);
        if (idx == k - 1) {
            if (res) return true;
        }
        else {
            if (! res) continue;

            pre.push_back(i);
            if (dfs(tsat, idx + 1, pre)) return true;
            pre.pop_back();
        }
    }
    return false;
}

bool solve(TwoSat &tsat)
{
    if (k == 0)
        return tsat.solve(sol);

    if (! tsat.solve(sol)) return false;

    tsat.save();

    return dfs(tsat, 0, IV());
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);

        TwoSat tsat(n);

        while (m--) {
            int type, x, y;
            scanf("%d%d%d", &type, &x, &y);
            --x; --y;

            switch (type) {
            case 1:
                tsat.add_cons(x, true, y, true);
                break;

            case 2:
                tsat.add_cons(x, true, y, false);
                break;

            case 3:
                tsat.add_cons(x, false, y, false);
                break;

            case 4:
                tsat.add_cons(x, true, y, true);
                tsat.add_cons(x, false, y, false);
                break;
            }
        }

        for (int i = 0; i < k; ++i) {
            scanf("%d%d%d%d", &council[i][0], &council[i][1],
                  &council[i][2], &council[i][3]);
            --council[i][1];
            --council[i][2];
            --council[i][3];
        }

        if (solve(tsat)) {
            sort(sol.begin(), sol.end());

            printf("Case %d: Possible %d", ++ncase, sol.size());
            cFor (IV, i, sol)
                printf(" %d", *i + 1);
            puts(".");
        }
        else
            printf("Case %d: Impossible.\n", ++ncase);
    }

    return 0;
}
