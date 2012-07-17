#include <cstdio>
#include <cstring>
#include <list>
#include <map>
#include <queue>
#include <vector>
using namespace std;


#define MAXNODES 30

#define Zero(v) memset((v), 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef map<int, int> IIM;


struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    void init(int N) { n=N; adj.clear(); adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }
};

struct Node {
    int v;  // node index
    int t;  // TTL
    Node(int V, int T) : v(V), t(T) {}
};
typedef queue<Node> NQ;

int NC;
int N;   // number of nodes

IIM nodes;
Graph g;

bool vis[MAXNODES];

int node_idx(int node)
{
    if (nodes.find(node) == nodes.end())
        nodes[node] = N++;

    return nodes[node];
}

int bfs(int strt, int ttl)
{
    NQ q;

    int reach = 0;
    Zero(vis);
    vis[strt] = true;

    q.push(Node(strt, ttl));

    while (! q.empty()) {
        Node nd = q.front(); q.pop();
        ++reach;

        if (nd.t == 0) continue;

        cFor (Graph::EL, e, g.adj[nd.v]) {
            if (! vis[e->v]) {
                vis[e->v] = true;
                q.push(Node(e->v, nd.t - 1));
            }
        }
    }

    return N - reach;
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d", &NC);
        if (NC == 0) break;

        g.init(MAXNODES);
        N = 0;
        nodes.clear();

        while (NC--) {
            int x, y;
            scanf("%d%d", &x, &y);

            int u = node_idx(x);
            int v = node_idx(y);

            g.add(u, v);
            g.add(v, u);
        }

        while (true) {
            int node, ttl;
            scanf("%d%d", &node, &ttl);
            if (node == 0 && ttl == 0) break;

            printf("Case %d: %d nodes not reachable from node %d "
                   "with TTL = %d.\n", ++ncase, bfs(node_idx(node), ttl),
                   node, ttl);
        }
    }

    return 0;
}
