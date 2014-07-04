#include <cstdio>
#include <cstring>


#define MAXN 20000
#define MAXM 50000

#define NegN(m,n,t) memset(m, -1, sizeof(t)*(n))
#define ClrN(m,n,t) memset(m, 0, sizeof(t)*(n))


typedef unsigned int u32;


struct Reader {
	int b; Reader() { read(); }
	void read() { b = getchar_unlocked(); }
	void skip() { while (0 <= b && b <= 32) read(); }

	u32 next_u32() {
		u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
};

struct Edge { int v; };

const int MAX_VERT = MAXN;
const int MAX_EDGES = MAXM;
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; NegN(adj, n, int); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	//
	// Strongly Connected Components
	//
	int nscc, nm;
	int scc[MAX_VERT];
	int scc_head[MAX_VERT];
	int scc_next[MAX_VERT];
	void init_scc() { nscc = nm = 0; NegN(scc_head, n, int); }
	void add_scc_element(int v) {
		scc_next[nm] = scc_head[nscc];
		scc_head[nscc] = nm;
		scc[nm++] = v;
	}

	int vcomp[MAX_VERT];
	void count_in_out(int *in, int *out) {
		ClrN(in, nscc, int);
		ClrN(out, nscc, int);
		for (int i = 0; i < nscc; ++i)
			for (int j = scc_head[i]; j >= 0; j = scc_next[j])
				vcomp[scc[j]] = i;
		for (int u = 0; u < n; u++)
			for (int i = adj[u]; i >= 0; i = next[i]) {
				int v = edges[i].v;
				if (vcomp[u] != vcomp[v]) {
					++out[ vcomp[u] ];
					++in[ vcomp[v] ];
				}
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
			radd(u, (Edge) { v });
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
		NegN(radj, n, int);
		ClrN(vis, n, bool);
		for (int v = 0; v < n; ++v) if (! vis[v]) dfs(v);
		ClrN(vis, n, bool);
		while (stk_top > 0) {
			int v = stk[--stk_top];
			if (! vis[v]) { dfs2(v); ++nscc; }
		}
	}
};


int n, m;
Graph g, dag;

int in[MAXN], out[MAXN];


int solve()
{
	g.kosaraju();
	if (g.nscc == 1) return 0;

	g.count_in_out(in, out);

	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < g.nscc; ++i) {
		if (in[i] == 0) ++cnt1;
		if (out[i] == 0) ++cnt2;
	}

	return cnt1 > cnt2 ? cnt1 : cnt2;
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

			g.add(u-1, (Edge) { v-1 });
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
