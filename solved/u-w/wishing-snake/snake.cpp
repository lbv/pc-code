#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAX_VERT 1000

const int MAX_EDGES = MAX_VERT * (MAX_VERT-1);

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };

struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}
	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }


	//
	// Tarjan for Strongly Connected Components
	//
	bool flg[MAX_VERT];
	int low[MAX_VERT];
	int idx[MAX_VERT];
	int stk[MAX_VERT];
	int s_top;
	int cnt;
	int nscc, nm;
	int scc[MAX_VERT];
	int scc_first[MAX_VERT];
	int scc_next[MAX_VERT];
	int scc_size[MAX_VERT];

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
			scc_next[nm] = scc_first[nscc];
			scc_first[nscc] = nm;
			++scc_size[nscc];
			scc[nm++] = u;
		}
		++nscc;
	}
	void tarjan_scc() {
		cnt = 1, nscc = nm = s_top = 0;
		Neg(scc_first); Clr(scc_size); Clr(flg); Clr(low);
		for (int i = 0; i < n; ++i) if (low[i] == 0) visit(i);
	}
	int vcomp[MAX_VERT];
	void scc_to_dag(Graph &dag) {
		for (int i = 0; i < nscc; ++i)
			for (int j = scc_first[i]; j >= 0; j = scc_next[j])
				vcomp[scc[j]] = i;
		dag.init(nscc);
		for (int u = 0; u < n; u++)
			for (int i = adj[u]; i >= 0; i = next[i]) {
				int v = edges[i].v;
				if (vcomp[u] != vcomp[v])
					dag.add(vcomp[u], Edge(vcomp[v]));
			}
	}
};


Graph g, dag;

bool used[MAX_VERT];
int nvert;


// Get the SCC where vertex zero is
int initial_scc()
{
	for (int i = 0; i < g.nscc; ++i)
		for (int j = g.scc_first[i]; j >= 0; j = g.scc_next[j])
			if (g.scc[j] == 0) return i;
	return -1;
}

bool solve()
{
	g.tarjan_scc();

	int v = initial_scc();
	g.scc_to_dag(dag);

	int vertices = 0;
	while (true) {
		vertices += g.scc_size[v];

		if (dag.adj[v] < 0) break;
		if (dag.next[ dag.adj[v] ] >= 0) return false;
		v = dag.edges[dag.adj[v]].v;
	}
	return vertices == nvert;
}

void mark(int u)
{
	if (! used[u])
		++nvert, used[u] = true;
}

int main()
{
	int T;
	scanf("%d", &T);

	int n;
	int ncase = 0;
	while (T--) {
		scanf("%d", &n);
		g.init(1000);
		nvert = 0;
		Clr(used);

		while (n--) {
			int k;
			scanf("%d", &k);

			while (k--) {
				int u, v;
				scanf("%d%d", &u, &v);
				g.add(u, Edge(v));

				mark(u);
				mark(v);
			}
		}

		printf("Case %d: ", ++ncase);
		if (solve()) puts("YES");
		else puts("NO");
	}

	return 0;
}
