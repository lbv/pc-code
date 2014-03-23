#include <algorithm>
#include <cstdio>
#include <cstring>
#include <list>
#include <set>
#include <vector>
using namespace std;


#define MAXLEN 50
#define INF    (2000 * 50 + 10)

#define Zero(v) memset((v), 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef unsigned int  u32;
typedef unsigned char uch;


//
// Hash Map
//
#define HASHB 4096
struct HM {
    struct Datum {
        char s[MAXLEN + 1];
        int l, id;
        Datum(const char *S, int Id) : id(Id) {
            l = strlen(S);
            strncpy(s, S, l);
        }
        bool operator==(const Datum &x) const {
            return l == x.l && strncmp(s, x.s, l) == 0;
        }
    };
    typedef vector<Datum> DV; DV b[HASHB];
    u32 fnv_hash(const char *k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<char*>(k));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U ) ^ p[i];
        return h;
    }
    int add(const Datum &k) {
        int i = fnv_hash(k.s, k.l * sizeof(char)) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j] == k) { return b[i][j].id; }
        b[i].push_back(k);
        return k.id;
    }
};

//
// Graphs
//
struct w_t {
    int w;
    int c;
    w_t(int W, int C) : w(W), c(C) {}
};
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    struct Node {
        int d, c, v;
        Node(int D, int C, int V) : d(D), c(C), v(V) {}
        bool operator<(const Node &x) const {
            if (d != x.d) return d < x.d;
            if (c != x.c) return c < x.c;
            return v < x.v;
        }
    };
    int dijkstra(int src, int dst) {
        set<Node> q;
        int dis[n][27];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 27; ++j)
                dis[i][j] = i == src ? 0 : INF;
        bool vis[n][27];
        Zero(vis);

        q.insert(Node(0, 26, src));
        while (! q.empty()) {
            int v = q.begin()->v;
            int c = q.begin()->c;
            if (v == dst) return q.begin()->d;

            q.erase(q.begin());

            if (vis[v][c]) continue;
            vis[v][c] = true;
            cFor (EL, e, adj[v]) {
                if (e->w.c == c) continue;
                int d = dis[v][c] + e->w.w;

                if (! vis[e->v][e->w.c] && d < dis[e->v][e->w.c]) {
                    dis[e->v][e->w.c] = d;
                    q.insert(Node(d, e->w.c, e->v));
                }
            }
        }

        return -1;
    }
};


char a[MAXLEN + 1];
char b[MAXLEN + 1];
char c[MAXLEN + 1];
int len;
int M;

int main()
{
    while (true) {
        scanf("%d", &M);
        if (M == 0) break;

        Graph g(M * 2 + 2);
        int n = 0;

        HM hm;

        scanf("%s%s", a, b);
        int orig = hm.add(HM::Datum(a, n));
        if (orig == n) ++n;

        int dest = hm.add(HM::Datum(b, n));
        if (dest == n) ++n;

        while (M--) {
            scanf("%s%s%s", a, b, c);

            int u = hm.add(HM::Datum(a, n));
            if (u == n) ++n;

            int v = hm.add(HM::Datum(b, n));
            if (v == n) ++n;

            int w = strlen(c);
            g.add(u, v, w_t(w, c[0] - 'a'));
            g.add(v, u, w_t(w, c[0] - 'a'));
        }

        int ans = g.dijkstra(orig, dest);
        if (ans < 0)
            puts("impossivel");
        else
            printf("%d\n", ans);
    }

    return 0;
}
