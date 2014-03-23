#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100
#define MAXM 100

#define INF 1000000

const int MAX_VERT  = MAXN + MAXM + 2;
const int MAX_EDGES = 2 * (MAXN * MAXM + MAXN + MAXM);

#define Memset(m,v) memset(m, v, sizeof(m))
#define Neg(m) Memset(m,-1)


// for max-flow models
template <typename T>
struct _Edge {
	int v, o;
	T c, f;
	_Edge() {}
	_Edge(int V, T C, int O) : v(V), o(O), c(C), f(0) {}
};
typedef _Edge<int> Edge;

struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}
	void init(int N) { n=N; m=0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
	void bi_add(int u, int v, int c) {
		add(u, Edge(v, c, m + 1));
		add(v, Edge(u, 0, m - 1));
	}

	// Ford-Fulkerson
	int dist[MAX_VERT], q[MAX_VERT], src, snk;
	bool find_aug_paths() {
		Neg(dist);
		int qfront = -1, qback = 0;
		q[++qfront] = src;
		dist[src] = 0;
		while (qback <= qfront) {
			int u = q[qback++];
			if (u == snk) return true;
			for (int i = adj[u]; i >= 0; i = next[i]) {
				Edge &e = edges[i];
				if (dist[e.v] >= 0 || e.f >= e.c) continue;
				q[++qfront] = e.v;
				dist[e.v] = dist[u] + 1;
			}
		}
		return false;
	}
	int dfs(int u, int f, int d) {
		if (u == snk) return f;
		int ans = 0;
		for (int i = adj[u]; f > 0 && i >= 0; i = next[i]) {
			Edge &e = edges[i];
			if (e.f >= e.c || dist[e.v] != d + 1) continue;
			int r = dfs(e.v, min(f, e.c - e.f), d + 1);
			if (r > 0) e.f += r, edges[e.o].f -= r, ans += r, f -= r;
		}
		return ans;
	}
	int mod_paths() {
		int ans = 0;
		for (int f = dfs(src, INF, 0); f > 0; f = dfs(src,INF, 0))
			ans += f;
		return ans;
	}
	int max_flow(int a, int b) {
		src = a, snk = b;
		int total = 0;
		while (find_aug_paths()) total += mod_paths();
		return total;
	}
};


Graph g;
int A[MAXN];
int B[MAXM];
int n, m;


int solve()
{
	g.init(n + m + 2);
	int src = n + m;
	int snk = n + m + 1;

	for (int i = 0; i < n; ++i)
		g.bi_add(src, i, 1);
	for (int i = 0; i < m; ++i)
		g.bi_add(n + i, snk, 1);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			if ((A[i] == 0 && B[j] == 0) || (A[i] != 0 && B[j] % A[i] == 0))
				g.bi_add(i, n + j, 1);
	}

	return g.max_flow(src, snk);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%d", &A[i]);
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) scanf("%d", &B[i]);

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
