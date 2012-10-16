#include <cstdio>
#include <list>
#include <set>
#include <vector>
using namespace std;


#define MAXS 15

const int INF = 10000 * 100 * 15 + 10;

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef pair<int, int> II;

typedef vector<int>  IV;
typedef vector<IV>   IVV;
typedef vector<bool> BV;
typedef vector<BV>   BVV;


// Weighted adjacency lists
typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    void dijkstra(int src, IV &dis) {
        set<II> q;
        dis = IV(n, INF);
        BV vis(n);
        q.insert(II(0, src));
        dis[src] = 0;
        while (! q.empty()) {
            II p = *(q.begin()); q.erase(q.begin());
            int d = p.first, v = p.second;
            if (vis[v]) continue;
            vis[v] = true;
            For (EL, e, adj[v]) {
                int d2 = d + e->w;
                if (d2 < dis[e->v]) {
                    dis[e->v] = d2;
                    q.insert(II(d2, e->v));
                }
            }
        }
    }

    struct Node {
        int s, t, v, b;
        Node(int S, int T, int V, int B) : s(S), t(T), v(V), b(B) {}
        bool operator<(const Node &x) const { return t < x.t; }
    };

    void dijkstra2(int &anss, int &anst) {
        multiset<Node> q;

        int S = n - 2;

        IVV dis(n, IV(1 << S, INF));
        BVV vis(n, BV(1 << S));

        q.insert(Node(0, 0, 0, 0));
        dis[0][0] = 0;
        anss = -1;

        while (! q.empty()) {
            Node p = *(q.begin()); q.erase(q.begin());
            int s = p.s, t = p.t, v = p.v, b = p.b;

            if (vis[v][b]) continue;
            vis[v][b] = true;

            if (v == n - 1 && s > anss) anss = s, anst = t;

            For (EL, e, adj[v]) {
                int t2 = t + e->w;
                int b2 = b;
                if (e->v >= 1 && e->v <= S) b2 |= 1 << (e->v - 1);

                if (t2 < dis[e->v][b2]) {
                    dis[e->v][b2] = t2;
                    int s2 = s;
                    if (b2 != b)
                        ++s2;
                    q.insert(Node(s2, t2, e->v, b2));
                }
            }
        }
    }
};


int N, M, S;
int shops[MAXS + 1];


bool solve(int &s, int &t, Graph &g)
{
    Graph sg(S + 2);  // simplified graph
    IV dis;
    g.dijkstra(0, dis);
    if (dis[N - 1] == INF) return false;

    if (dis[N - 1] != INF) sg.add(0, S + 1, dis[N - 1]);
    for (int i = 1; i <= S; ++i)
        if (dis[shops[i]] != INF)
            sg.add(0, i, dis[shops[i]]);

    for (int i = 1; i <= S; ++i) {
        g.dijkstra(shops[i], dis);

        if (dis[0] != INF) sg.add(i, 0, dis[0]);
        if (dis[N - 1] != INF) sg.add(i, S + 1, dis[N - 1]);
        for (int j = 1; j <= S; ++j)
            if (i != j && dis[shops[j]] != INF)
                sg.add(i, j, dis[shops[j]]);
    }

    sg.dijkstra2(s, t);

    return true;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &N, &M, &S);

        for (int i = 1; i <= S; ++i)
            scanf("%d", &shops[i]);

        Graph g(N);

        while (M--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g.add(u, v, w);
        }

        printf("Case %d: ", ++ncase);

        int s, t;
        if (solve(s, t, g))
            printf("%d %d\n", s, t);
        else
            puts("Impossible");
    }

    return 0;
}
