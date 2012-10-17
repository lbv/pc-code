#include <cstdio>
#include <cstring>
#include <list>
#include <queue>
#include <vector>
using namespace std;


#define MAXT 1000

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)
#define Zero(v) memset((v), 0, sizeof(v))


typedef pair<int, int> II;


struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N=0) : n(N) { adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }
};


int s, t;
Graph g(MAXT + 1);
bool is_comp[MAXT + 1];
bool vis[MAXT + 1];


void prepare()
{
    for (int j = 4; j <= MAXT; j += 2) {
        is_comp[j] = true;
        if (j + 2 <= MAXT)
            g.add(j, j + 2);
    }

    for (int i = 3, I = MAXT / 2; i <= I; i += 2) {
        if (is_comp[i]) continue;
        for (int j = 2*i; j <= MAXT; j += i) {
            is_comp[j] = true;
            if (j + i <= MAXT)
                g.add(j, j + i);
        }
    }
}

int solve()
{
    queue<II> q;
    q.push(II(s, 0));

    Zero(vis);
    vis[s] = true;

    while (! q.empty()) {
        int n = q.front().first, d = q.front().second;
        q.pop();

        if (n == t) return d;

        For (Graph::EL, e, g.adj[n]) {
            if (e->v <= t && ! vis[e->v]) {
                q.push(II(e->v, d + 1));
                vis[e->v] = true;
            }
        }
    }

    return -1;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &s, &t);
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
