#include <cstdio>
#include <cstring>


#define MAXN 10000
#define MAXM 100000

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };

const int MAX_VERT = MAXN;
const int MAX_EDGES = MAXM;
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	//
	// Strongly Connected Components
	//
	int nscc, nm;
	int scc[MAX_VERT];
	int scc_first[MAX_VERT];
	int scc_next[MAX_VERT];
	// int scc_size[MAX_VERT];
	void init_scc() { nscc = nm = 0; Neg(scc_first); }
	void add_scc_element(int v) {
		scc_next[nm] = scc_first[nscc];
		scc_first[nscc] = nm;
		scc[nm++] = v;
		// ++scc_size[nscc];
	}

	//
	// Kosaraju's SCC algorithm
	//
	int stk[MAX_VERT];
	int stk_top;
	bool vis[MAX_VERT];

	Edge redges[MAX_EDGES];
	int rnext[MAX_EDGES];
	int radj[MAX_VERT];
	int rm;
	void radd(int u, const Edge &e) {
		rnext[rm]=radj[u], radj[u]=rm, redges[rm++]=e; }
	void dfs(int v) {
		vis[v] = true;
		for (int i = adj[v]; i >= 0; i = next[i]) {
			int u = edges[i].v;
			radd(u, Edge(v));
			if (! vis[u]) dfs(u);
		}
		stk[stk_top++] = v;
	}
	void dfs2(int v) {
		vis[v] = true;
		add_scc_element(v);
		for (int i = radj[v]; i >= 0; i = rnext[i]) {
			int ev = redges[i].v;
			if (! vis[ev]) dfs2(ev);
		}
	}
	void kosaraju() {
		rm = stk_top = 0;
		init_scc();
		Neg(radj);
		Clr(vis);
		for (int v = 0; v < n; ++v) if (! vis[v]) dfs(v);
		Clr(vis);
		while (stk_top > 0) {
			int v = stk[--stk_top];
			if (! vis[v]) { dfs2(v); ++nscc; }
		}
	}
};


int N, M;
Graph g;

bool vis[MAX_VERT];


void dfs(int u)
{
	vis[u] = true;

	for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
		int v = g.edges[i].v;

		if (! vis[v]) dfs(v);
	}
}

int solve()
{
	int ans = 0;
	g.kosaraju();

	Clr(vis);
	for (int i = 0; i < g.nscc; ++i) {
		int v = g.scc[ g.scc_first[i] ];

		if (! vis[v]) {
			dfs(v);
			++ans;
		}
	}

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &N, &M);
		g.init(N);

		while (M--) {
			int u, v;
			scanf("%d%d", &u, &v);
			g.add(u-1, Edge(v-1));
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
