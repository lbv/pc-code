#include <algorithm>
#include <cstdio>
#include <list>
#include <vector>
using namespace std;


#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef vector<int>  IV;


struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }

    struct Euler {
        ELV adj; IV t;
        Euler(Graph &g) : adj(g.adj) {}

        void build(int u, int v) {
            EL &a = adj[v];
            For (EL, e, a)
                if (e->v == u) {
                    a.erase(e);
                    break;
                }

            while(! a.empty()) {
                int dest = a.front().v;
                a.erase(a.begin());
                build(v, dest);
            }

            t.push_back(v + 1);
        }
    };
    void eulerian_trail(IV &trail) {
        Euler e(*this);
        e.build(-1, 0);
        reverse(e.t.begin(), e.t.end());
        trail = e.t;
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
        int profit = 0;

        for (int i = 0; i < n; ++i) {
            int w;
            scanf("%d", &w);
            profit += w - (i + 1);
        }
        profit -= m;

        Graph g(n);

        while (m--) {
            int u, v;
            scanf("%d%d", &u, &v);
            --u, --v;

            g.add(u, v);
            g.add(v, u);
        }

        IV trail;
        g.eulerian_trail(trail);

        printf("Case %d: %d\n", ++ncase, profit);

        printf("%d", trail[0]);
        for (int i = 1, I = trail.size(); i < I; ++i)
            printf(" %d", trail[i]);
        putchar('\n');
    }

    return 0;
}
