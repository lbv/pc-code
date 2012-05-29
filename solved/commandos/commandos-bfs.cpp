#include <algorithm>
#include <cstdio>
#include <list>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef vector<bool>   BV;
typedef pair<int, int> II;
typedef vector<int>    IV;
typedef queue<II>      IIQ;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Graphs
namespace Graph {
    struct Edge { int v, w; Edge(int V, int W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    void init(ELV &g, int n) { g.clear(); g.resize(n); }
    void add(ELV &g, int u, int v, int w) { g[u].push_back(Edge(v, w)); }
}

typedef Graph::ELV GT;
GT g;
int N;

void bfs(int src, IV &dist)
{
    BV flg(N);
    IIQ q;
    flg[src] = true;
    q.push(II(src, 0));
    while (! q.empty()) {
        int v = q.front().first;
        int d = q.front().second;
        q.pop();

        dist[v] = d;

        cFor (Graph::EL, e, g[v]) {
            if (!flg[e->v]) {
                q.push(II(e->v, d+1));
                flg[e->v] = true;
            }
        }
    }
}

int mintime(int s, int d)
{
    IV fromS(N);
    IV toD(N);

    bfs(s, fromS);
    bfs(d, toD);

    int time = 0;
    for (int i = 0; i < N; i++) {
        int t = fromS[i] + toD[i];
        if (t > time) time = t;
    }
    return time;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int R;
        scanf("%d%d", &N, &R);

        Graph::init(g, N);

        while (R--) {
            int u, v;
            scanf("%d%d", &u, &v);
            Graph::add(g, u, v, 0);
            Graph::add(g, v, u, 0);
        }

        int s, d;
        scanf("%d%d", &s, &d);

        printf("Case %d: %d\n", ncase++, mintime(s, d));
    }

    return 0;
}
