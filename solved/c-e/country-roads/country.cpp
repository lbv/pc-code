#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define INF 0x3f3f3f3f


#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))
#define Inf(m) memset(m, 0x3f, sizeof(m))

const int MAX_VERT = 500;
const int MAX_EDGES = 16000 * 2;


typedef unsigned int u32;
typedef int GraphT;


struct Reader {
	int b; Reader() { read(); }
	void read() { b = getchar_unlocked(); }
	void skip() { while (b >= 0 && b <= 32) read(); }

	u32 next_u32() {
		u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};

struct Edge {
	int v; GraphT w;
	Edge() {}
	Edge(int V, GraphT W) : v(V), w(W) {}
};

struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}
	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	//
	// Dijkstra's Single Source Shortest Paths
	//
	struct Node {
		GraphT d;
		int v;
		Node() {}
		Node(GraphT D, int V): d(D), v(V) {}

		bool operator<(const Node &n) const { return d > n.d; }
	};
	GraphT dis[MAX_VERT];
	bool vis[MAX_VERT];

	void dijkstra(int src) {
		Inf(dis); Clr(vis);
		priority_queue<Node> q;
		q.push(Node(0, src));
		dis[src] = 0;
		while (! q.empty()) {
			Node cur = q.top(); q.pop();
			if (vis[cur.v]) continue;
			vis[cur.v] = true;

			for (int i = adj[cur.v]; i >= 0; i = next[i]) {
				Edge &e = edges[i];
				// Minimax variation
				GraphT d2 = max(cur.d, e.w);
				if (d2 >= dis[e.v]) continue;
				dis[e.v] = d2;
				q.push(Node(d2, e.v));
			}
		}
	}
};


int n, m, t;
Graph g;


void solve()
{
	g.dijkstra(t);

	for (int i = 0; i < n; i++) {
		if (g.dis[i] >= INF)
			puts("Impossible");
		else
			printf("%d\n", g.dis[i]);
	}
}

int main()
{
	Reader rr;
	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		n = rr.next_u32();
		m = rr.next_u32();

		g.init(n);

		while (m--) {
			int u = rr.next_u32();
			int v = rr.next_u32();
			int w = rr.next_u32();

			g.add(u, Edge(v, w));
			g.add(v, Edge(u, w));
		}

		t = rr.next_u32();

		printf("Case %d:\n", ++ncase);
		solve();
	}

	return 0;
}
