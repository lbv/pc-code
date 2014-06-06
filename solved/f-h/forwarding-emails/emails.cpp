#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 50000

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


const int MAX_VERT = MAXN + 1;
const int MAX_EDGES = MAXN;
struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };
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
	int scc_size[MAX_VERT];
	void init_scc() { nscc = nm = 0; Clr(scc_size); Neg(scc_first); }
	void add_scc_element(int v) {
		scc_next[nm] = scc_first[nscc];
		scc_first[nscc] = nm;
		scc[nm++] = v;
		++scc_size[nscc];
	}
	//
	// Tarjan for Strongly Connected Components
	//
	bool flg[MAX_VERT];
	int low[MAX_VERT];
	int idx[MAX_VERT];
	int stk[MAX_VERT];
	int s_top;
	int cnt;

	void visit(int v) {
		idx[v] = low[v] = cnt++;
		stk[s_top++] = v;
		flg[v] = true;
		for (int i = adj[v]; i >= 0; i = next[i]) {
			int vp = edges[i].v;
			if (low[vp] == 0) {
				visit(vp);
				low[v] = min(low[v], low[vp]);
			}
			else if (flg[vp])
				low[v] = min(low[v], idx[vp]);
		}
		if (low[v] != idx[v]) return;
		for (int u = -1; u != v;) {
			u = stk[--s_top];
			flg[u] = false;
			add_scc_element(u);
		}
		++nscc;
	}
	void tarjan_scc() {
		cnt = 1, s_top = 0;
		init_scc(); Clr(flg); Clr(low);
		for (int i = 0; i < n; ++i) if (low[i] == 0) visit(i);
	}

	int vcomp[MAX_VERT];
	void scc_vcomp() {
		for (int i = 0; i < nscc; ++i)
			for (int j = scc_first[i]; j >= 0; j = scc_next[j])
				vcomp[scc[j]] = i;
	}
};


int N;
Graph g;
int vis[MAX_VERT];
int gvis;
int reach[MAX_VERT];


void dfs(int u)
{
	vis[u] = gvis;

	reach[u] = g.scc_size[ g.vcomp[u] ];
	for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
		int v = g.edges[i].v;

		if (vis[v] != gvis) dfs(v);
		if (g.vcomp[v] != g.vcomp[u]) reach[u] += reach[v];
	}
}

int solve()
{
	g.tarjan_scc();
	g.scc_vcomp();
	++gvis;

	int nodes = 0, idx = 0;
	for (int i = 1; i <= N; ++i) {
		if (vis[i] == gvis) continue;
		dfs(i);
		int cur = reach[i];
		if (cur > nodes) nodes = cur, idx = i;
	}
	return idx;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);
		g.init(N + 1);

		for (int i = 0; i < N; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			g.add(u, Edge(v));
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
