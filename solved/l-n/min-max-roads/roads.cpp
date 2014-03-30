#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100001
#define LOGN 18
#define INF 0x3f3f3f3f

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


const int MAX_VERT = MAXN;
const int MAX_EDGES = MAXN * 2;


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
};

//
// Lowest Common Ancestor
//
struct LCA {
	int L[MAXN];         // L[i]: level of node i
	int A[MAXN][LOGN];   // A[i][j]: 2^j'th ancestor of i
	int MI[MAXN][LOGN];  // min roads
	int MA[MAXN][LOGN];  // max roads
	int n, h, lh;        // n, height, log(h)
	LCA() {}

	void init(int N, int H) { n=N, h=H; Neg(A); lh = log2(h); }
	void process() {
		// precond: A[i][0] is set for all i
		for (int j = 1, p = 2; p < h; ++j, p <<= 1)
			for (int i = 0; i < n; ++i)
				if (A[i][j-1] != -1) {
					A[i][j] = A[ A[i][j-1] ][j-1];
					MI[i][j] = min(MI[i][j-1], MI[ A[i][j-1] ][j-1]);
					MA[i][j] = max(MA[i][j-1], MA[ A[i][j-1] ][j-1]);
				}
	}
	void query(int a, int b, int &lo, int &hi) {
		if (L[a] < L[b]) swap(a, b);

		lo = INF;
		hi = 0;

		for (int i = lh, p = 1 << lh; i >= 0; --i, p >>= 1)
			if (L[a] - p >= L[b]) {
				lo = min(lo, MI[a][i]);
				hi = max(hi, MA[a][i]);
				a = A[a][i];
			}
		if (a == b) return;

		for (int i = lh; i >= 0; --i)
			if (A[a][i] != -1 && A[a][i] != A[b][i]) {
				lo = min(lo, min(MI[a][i], MI[b][i]));
				hi = max(hi, max(MA[a][i], MA[b][i]));
				a = A[a][i], b = A[b][i];
			}
		lo = min(lo, min(MI[a][0], MI[b][0]));
		hi = max(hi, max(MA[a][0], MA[b][0]));
	}
};

int n, q;
Graph g;
LCA lca;

bool vis[MAXN];


// u: node
// p: parent
// w: weight of road
// l: level
void dfs(int u, int p, int w, int l)
{
	lca.L[u] = l;
	lca.A[u][0] = p;
	lca.MI[u][0] = lca.MA[u][0] = w;

	vis[u] = true;

	for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
		Edge &e = g.edges[i];

		if (! vis[e.v]) dfs(e.v, u, e.w, l + 1);
	}
}

void build_lca()
{
	// just for fun.. choose the root at random
	int root = rand() % n + 1;

	Clr(vis);
	dfs(root, -1, 0, 0);

	lca.process();
}

int main()
{
	Reader rr;

	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		n = rr.next_u32();

		g.init(n + 1);
		lca.init(n + 1, n + 1);

		for (int i = 1; i < n; ++i) {
			int u = rr.next_u32();
			int v = rr.next_u32();
			int w = rr.next_u32();

			g.add(u, Edge(v, w));
			g.add(v, Edge(u, w));
		}

		build_lca();

		printf("Case %d:\n", ++ncase);
		q = rr.next_u32();
		while (q--) {
			int x = rr.next_u32();
			int y = rr.next_u32();
			int lo, hi;
			lca.query(x, y, lo, hi);
			printf("%d %d\n", lo, hi);
		}
	}

	return 0;
}
