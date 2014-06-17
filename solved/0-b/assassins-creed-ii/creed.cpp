#include <cstdio>
#include <cstring>


#define MAXN 1000
#define MAXM 10000
#define INF 0x3f3f3f3f

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


typedef unsigned int u32;


struct Reader {
	int b; Reader() { read(); }
	void read() { b = getchar_unlocked(); }
	void skip() { while (0 <= b && b <= 32) read(); }

	u32 next_u32() {
		u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
};

struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };
#define MAX_VERT (MAXN)
#define MAX_EDGES (MAXM)
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
	int scc_head[MAX_VERT];
	int scc_next[MAX_VERT];
	void init_scc() { nscc = nm = 0; Neg(scc_head); }
	void add_scc_element(int v) {
		scc_next[nm] = scc_head[nscc];
		scc_head[nscc] = nm;
		scc[nm++] = v;
	}

	int vcomp[MAX_VERT];
	void scc_to_dag(Graph &dag) {
		for (int i = 0; i < nscc; ++i)
			for (int j = scc_head[i]; j >= 0; j = scc_next[j])
				vcomp[scc[j]] = i;
		dag.init(nscc);
		for (int u = 0; u < n; u++)
			for (int i = adj[u]; i >= 0; i = next[i]) {
				int v = edges[i].v;
				if (vcomp[u] != vcomp[v])
					dag.add(vcomp[u], Edge(vcomp[v]));
			}
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

#undef MAX_VERT
#undef MAX_EDGES
#define MAX_VERT (2*MAXN + 2)
#define MAX_EDGES (MAX_VERT*(MAX_VERT - 1)/2)
struct BGraph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	/////////////////////////////////////////////
	////////// Bi-Partite Graphs ////////////////
	/////////////////////////////////////////////
	int x, src, snk;
	void init_bipart_basic(int X) {
		x = X;
		n = 2*x + 2, src = 0, snk = 2*x + 1, m = 0;
		Neg(adj);
	}


	//
	// Hopcroft-Karp for bipartite matching.
	//
	void add_bipart(int v1, int v2) {
		int u = 1 + v1;
		int v = x + 1 + v2;
		add(u, Edge(v));
	}

	int match[MAX_VERT];
	int dist[MAX_VERT];
	int q[MAX_VERT];

	bool bfs() {
		int qf = 0, qb = 0;
		for (int i = 1; i <= x; ++i)
			if (match[i] == 0)
				dist[i] = 0, q[qb++] = i;
			else
				dist[i] = INF;
		dist[0] = INF;
		while (qf < qb) {
			int v = q[qf++];
			for (int i = adj[v]; i >= 0; i = next[i]) {
				Edge &e = edges[i];
				int p = match[e.v];
				if (dist[p] != INF) continue;
				dist[p] = dist[v] + 1;
				q[qb++] = p;
			}
		}
		return dist[0] != INF;
	}
	bool dfs(int u) {
		if (u == 0) return true;
		for (int i = adj[u]; i >= 0; i = next[i]) {
			Edge &e = edges[i];
			int p = match[e.v];
			if (dist[p] == dist[u] + 1 && dfs(p)) {
				match[e.v] = u;
				match[u] = e.v;
				return true;
			}
		}
		dist[u] = INF;
		return false;
	}
	int max_matching() {
		int m = 0;
		Clr(match);
		while (bfs())
			for (int i = 1; i <= x; ++i)
				if (match[i] == 0 && dfs(i)) ++m;
		return m;
	}
};


int N, M;
Graph g, dag;
BGraph bg;
bool adjm[MAXN][MAXN];


void dfs(int u, int v)
{
	adjm[u][v] = true;

	for (int i = dag.adj[v]; i >= 0; i = dag.next[i]) {
		int w = dag.edges[i].v;
		if (! adjm[u][w]) dfs(u, w);
	}
}

int solve()
{
	g.kosaraju();
	g.scc_to_dag(dag);
	Clr(adjm);

	for (int u = dag.n - 1; u >= 0; --u)
		for (int i = dag.adj[u]; i >= 0; i = dag.next[i]) {
			int v = dag.edges[i].v;
			if (! adjm[u][v]) dfs(u, v);
		}

	bg.init_bipart_basic(dag.n);
	for (int i = 0; i < dag.n; ++i)
		for (int j = 0; j < dag.n; ++j)
			if (adjm[i][j]) bg.add_bipart(i, j);

	int match = bg.max_matching();
	return dag.n - match;
}

int main()
{
	Reader rr;
	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		N = rr.next_u32();
		M = rr.next_u32();

		g.init(N);

		while (M--) {
			int u = rr.next_u32();
			int v = rr.next_u32();
			g.add(u-1, Edge(v-1));
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
