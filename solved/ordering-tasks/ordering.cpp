#include <cstdio>
#include <list>
#include <queue>
#include <vector>
using namespace std;


#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef queue<int>  IQ;
typedef vector<int> IV;


struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    void init(int N) { n=N; adj.clear(); adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }

    void topo_sort(IV &in, IV &order) {
        IQ q;
        for (int i = 0; i < n; ++i) if (in[i] == 0) q.push(i);
        order.clear();
        while (! q.empty()) {
            int v = q.front(); q.pop();
            order.push_back(v);
            cFor (EL, e, adj[v])
                if (--in[e->v] == 0) q.push(e->v);
        }
    }
};


int n, m;
Graph g;

int main()
{
    while (true) {
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0) break;

        g.init(n);
        IV in(n);

        int i, j;
        while (m--) {
            scanf("%d%d", &i, &j);
            --i; --j;
            ++in[j];
            g.add(i, j);
        }

        IV order;
        g.topo_sort(in, order);

        printf("%d", order[0] + 1);

        for (int i = 1; i < n; ++i)
            printf(" %d", order[i] + 1);
        putchar('\n');
    }

    return 0;
}
