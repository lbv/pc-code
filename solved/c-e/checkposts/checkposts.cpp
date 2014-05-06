#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100000
#define MAXM 300000

#define MOD 1000000007
#define INF 0x3f3f3f3f

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


typedef long long i64;


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
};


int n, m;
int costs[MAXN];

i64 mincost;
int nways;

Graph g;


void solve()
{
	g.tarjan_scc();

	nways = 1;
	mincost = 0;

	for (int i = 0; i < g.nscc; ++i) {
		int scc_cost = INF;
		i64 cnt = 0;

		for (int j = g.scc_first[i]; j >= 0; j = g.scc_next[j]) {
			int v = g.scc[j];

			if (costs[v] < scc_cost)
				scc_cost = costs[v], cnt = 1;
			else if (costs[v] == scc_cost)
				++cnt;
		}

		nways = (nways * cnt) % MOD;
		mincost += scc_cost;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &costs[i]);

	g.init(n);

	scanf("%d", &m);
	while (m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.add(u-1, Edge(v-1));
	}

	solve();
	printf("%lld %d\n", mincost, nways);

	return 0;
}
