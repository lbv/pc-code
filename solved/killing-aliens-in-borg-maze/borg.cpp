#include <cstdio>
#include <cstring>
#include <list>
#include <queue>
#include <set>
#include <vector>
using namespace std;


#define MAXX 50
#define MAXY 50
#define MAXA 100
#define INF  2510

#define Zero(v) memset((v), 0, sizeof(v))
#define Neg(v)  memset((v), -1, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef pair<int, int> II;
typedef set<II>        IIS;
typedef vector<int>    IV;
typedef vector<bool>   BV;


//
// Graphs
//
typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    int prim_mst(int src) {
        IIS q;
        IV dis(n, INF);
        BV flg(n);
        dis[src] = 0;
        q.insert(II(0, src));
        int mst = 0;
        while (! q.empty()) {
            int d = q.begin()->first;
            int v = q.begin()->second;
            q.erase(q.begin());
            if (flg[v]) continue;
            flg[v] = true;
            mst += d;
            cFor (EL, e, adj[v])
                if (!flg[e->v] && e->w < dis[e->v]) {
                    dis[e->v] = e->w;
                    q.insert(II(dis[e->v], e->v));
                }
        }
        return mst;
    }
};


struct Node {
    int r, c, s;
    Node(int R, int C, int S) : r(R), c(C), s(S) {}
};
typedef queue<Node> NQ;


char maze[MAXY][MAXX + 1];
int x, y;

int n;                // number of vertices (aliens plus starting point=
int pv[MAXA + 1][2];  // positions of vertices

int  vertices[MAXY][MAXX];
bool vis[MAXY][MAXX];

const int delta[4][2] = {
    {  0,  1 },
    {  0, -1 },
    {  1,  0 },
    { -1,  0 }
};


bool free_pos(int r, int c)
{
    return r >= 0 && r < y && c >= 0 && c < x && maze[r][c] != '#';
}

void bfs(int v, Graph &g)
{
    int r = pv[v][0];
    int c = pv[v][1];

    NQ q;
    q.push(Node(r, c, 0));

    Zero(vis);
    vis[r][c] = true;

    int reached = 0;

    while (! q.empty()) {
        Node nd = q.front(); q.pop();

        r = nd.r, c = nd.c;
        if (vertices[r][c] >= 0) {
            ++reached;
            if (vertices[r][c] != v)
                g.add(v, vertices[r][c], nd.s);
        }

        if (reached == n) break;

        for (int i = 0; i < 4; ++i) {
            r = nd.r + delta[i][0];
            c = nd.c + delta[i][1];

            if (! free_pos(r, c) || vis[r][c]) continue;
            q.push(Node(r, c, nd.s + 1));
            vis[r][c] = true;
        }
    }
}

int solve()
{
    n = 0;
    Neg(vertices);
    for (int i = 0; i < y; ++i)
        for (int j = 0; j < x; ++j)
            if (maze[i][j] == 'A' || maze[i][j] == 'S') {
                pv[n][0] = i;
                pv[n][1] = j;
                vertices[i][j] = n++;
            }

    Graph g(n);

    for (int i = 0; i < n; ++i)
        bfs(i, g);

    return g.prim_mst(0);
}

int main()
{
    int N;
    scanf("%d", &N);

    while (N--) {
        scanf("%d%d", &x, &y);
        gets(maze[0]);

        for (int i = 0; i < y; ++i)
            gets(maze[i]);

        printf("%d\n", solve());
    }

    return 0;
}
