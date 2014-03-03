#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 50000
#define MAXM 100000

#define LOGN 17
#define MAX_EDGES (MAXM*2)

#define Memset(m,v) memset(m, v, sizeof(m))
#define Clr(m) Memset(m,0)
#define Neg(m) Memset(m,-1)


typedef unsigned int u32;

typedef int EdgeT;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};


struct Edge {
    int u, v;
    EdgeT w;
    Edge() {}
    Edge(int U, int V, EdgeT W): u(U), v(V), w(W) {}
    bool operator<(const Edge &e) const { return w < e.w; }
};

// Union-Find disjoint set
struct Set {
    int s[MAXN];
    Set() {}
    void init(int n) { for (int i=0; i < n; ++i) s[i] = i; }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};

struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAXN];
	int n, m;
	Graph() {}
	void init(int N) { n=N; m=0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
	void add_dir(int u, int i) { next[i]=adj[u], adj[u]=i; }
	void add_und(const Edge &e) { edges[m++] = e; }

	Set uf;
	void kruskal_mst() {
		sort(edges, edges + m);
		uf.init(n);
		int nedges = 0;
		for (int i = 0, I = m; i < I; ++i) {
			Edge &e = edges[i];
			if (uf.find(e.u) == uf.find(e.v)) continue;
			uf.merge(e.u, e.v);
			add_dir(e.u, i);
			add(e.v, Edge(e.v, e.u, e.w));
			if (++nedges == n - 1) break;
		}
	}
};

struct LCA {
	int L[MAXN];        // L[i]: level of node i
	int A[MAXN][LOGN];  // A[i][j]: 2^j'th ancestor of i
	int M[MAXN][LOGN];  // M[i][j] Max edge from i, and 2^j edges upwards
	int n, h, lh;       // n, height, log(h)
	LCA() {}

	void init(int N, int H) { n=N, h=H; Neg(A); lh = log2(h); }
	void process() {
		// precond: A[i][0] is set for all i
		for (int j = 1, p = 2; p < h; ++j, p <<= 1)
			for (int i = 0; i < n; ++i)
				if (A[i][j-1] != -1) {
					A[i][j] = A[ A[i][j-1] ][j-1];
					M[i][j] = max(M[i][j-1], M[ A[i][j-1] ][j-1]);
				}
	}

	int query(int a, int b) {
		if (L[a] < L[b]) swap(a, b);

		int ans = 0;
		for (int i = lh, p = 1 << lh; i >= 0; --i, p >>= 1)
			if (L[a] - p >= L[b]) {
				ans = max(ans, M[a][i]);
				a = A[a][i];
			}

		if (a == b) return ans;

		for (int i = lh; i >= 0; --i)
			if (A[a][i] != -1 && A[a][i] != A[b][i]) {
				ans = max(ans, max(M[a][i], M[b][i]));
				a = A[a][i], b = A[b][i];
			}

		return max(ans, max(M[a][0], M[b][0]));
	}
};


int N, M;
Graph g;
LCA lca;

bool vis[MAXN];


void dfs(int v, int u, int l, int c)
{
	vis[v] = true;
	lca.L[v] = l;
	lca.A[v][0] = u;
	lca.M[v][0] = c;

	for (int i = g.adj[v]; i >= 0; i = g.next[i]) {
		Edge &e = g.edges[i];
		if (vis[e.v]) continue;

		dfs(e.v, v, l + 1, e.w);
	}
}

void process()
{
	g.kruskal_mst();

	Clr(vis);
	lca.init(N, N);

	dfs(0, -1, 0, 0);
	lca.process();
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
		for (int i = 0; i < M; ++i) {
			int x = rr.next_u32();
			int y = rr.next_u32();
			int d = rr.next_u32();

			g.add_und(Edge(x-1, y-1, d));
		}

		process();

		printf("Case %d:\n", ++ncase);
		int q = rr.next_u32();

		while (q--) {
			int s = rr.next_u32();
			int t = rr.next_u32();

			printf("%d\n", lca.query(s-1, t-1));
		}
	}

	return 0;
}
