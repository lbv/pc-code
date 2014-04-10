#include <cstdio>
#include <cstring>


typedef int GraphT;


#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))

const int MAX_VERT = 1000;
const int MAX_EDGES = 2000;


struct Edge {
	int u, v; GraphT w;
	Edge() {}
	Edge(int U, int V, GraphT W) : u(U), v(V), w(W) {}
	bool operator<(const Edge &e) const { return w < e.w; }
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
	// Bellman-Ford variation, to run a DFS from nodes involved in a
	// negative cycle
	//
	GraphT dis[MAX_VERT];
	void bellman_ford() {
		Clr(dis);
		Clr(vis);
		for (int i = 1; i < n; i++)
			for (int j = 0; j < m; ++j) {
				Edge &e = edges[j];
				if(dis[e.u] + e.w < dis[e.v])
					dis[e.v] = dis[e.u] + e.w;
			}
		for (int j = 0; j < m; ++j) {
			Edge &e = edges[j];
			if (!vis[e.u] && dis[e.u] + e.w < dis[e.v])
				dfs(e.u);
		}
	}
	bool vis[MAX_VERT];
	void dfs(int u) {
		vis[u] = true;
		for (int i = adj[u]; i >= 0; i = next[i]) {
			int v = edges[i].v;
			if (! vis[v]) dfs(v);
		}
	}
};


int n, m;
Graph rg;  // reverse graph


void solve()
{
	rg.bellman_ford();
	bool possible = false;

	for (int i = 0; i < n; ++i)
		if (rg.vis[i]) {
			printf(" %d", i);
			possible = true;
		}

	if (possible)
		putchar('\n');
	else
		puts(" impossible");
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &n, &m);
		rg.init(n);

		while (m--) {
			int x, y, t;
			scanf("%d%d%d", &x, &y, &t);
			rg.add(y, Edge(y, x, t));
		}

		printf("Case %d:", ++ncase);
		solve();
	}

	return 0;
}
