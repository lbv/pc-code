#include <cstdio>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;


#define MAXLEN 1023

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef vector<int> IV;
typedef queue<int>  IQ;
typedef map<string, int> SIM;
typedef SIM::iterator    SIMi;
typedef vector<SIMi>     SIMiV;


struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
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



int S;
char s[MAXLEN + 1];
char t[MAXLEN + 1];


int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &S);

        Graph g(S);
        SIM m;
        SIMi it;
        SIMiV ind(S);

        IV in(S);

        int cnt = 0;

        for (int i = 1; i < S; ++i) {
            scanf("%s%s", s, t);

            string a(s);
            string b(t);
            if (m.find(a) == m.end()) m[a] = cnt++;
            if (m.find(b) == m.end()) m[b] = cnt++;

            it = m.find(a);
            int u = it->second;
            ind[u] = it;

            it = m.find(b);
            int v = it->second;
            ind[v] = it;

            ++in[v];
            g.add(u, v);
        }

        IV order;
        g.topo_sort(in, order);

        printf("Case %d:\n", ++ncase);
        cFor (IV, v, order)
            printf("%s\n", ind[*v]->first.c_str());
        putchar('\n');
    }

    return 0;
}
