#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100

#define INF 0x3f3f3f3f

#define ClrN(m,n,t) memset(m, 0, sizeof(t)*(n))
#define NegN(m,n,t) memset(m, -1, sizeof(t)*(n))


struct Edge { int v; };

const int MAX_VERT = 2*MAXN + 2;
const int MAX_EDGES = MAXN * (MAXN-1) / 2;
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	/////////////////////////////////////////////
	////////// Bi-Partite Graphs ////////////////
	/////////////////////////////////////////////
	int x, src, snk;
	void init_bipart_basic(int X) {
		x = X, n = 2*x + 2, src = 0, snk = 2*x + 1, m = 0;
		NegN(adj, n, int);
	}


	//
	// Hopcroft-Karp for bipartite matching.
	//
	void add_bipart(int v1, int v2) {
		int u = 1 + v1;
		int v = x + 1 + v2;
		add(u, (Edge) { v });
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
		ClrN(match, n, int);
		while (bfs())
			for (int i = 1; i <= x; ++i) if (match[i] == 0 && dfs(i)) ++m;
		return m;
	}
};


int n;
int ns[MAXN];

int sol[MAXN];
int nsol;

Graph g;

bool chained[MAXN];


bool check(int x)
{
	int a = ns[ sol[x] ];

	for (int i = 0; i < nsol; ++i) {
		if (i == x) continue;

		int b = ns[ sol[i] ];
		if (a <= b && b % a == 0) return false;
	}

	return true;
}

void solve()
{
	sort(ns, ns + n);
	g.init_bipart_basic(n);

	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (ns[j] % ns[i] == 0)
				g.add_bipart(i, j);

	g.max_matching();

	ClrN(chained, n, bool);
	nsol = 0;

	for (int i = 0; i < n; ++i)
		if (! chained[i]) {
			sol[nsol++] = i;

			for (int x = i; x >= 0; x = g.match[x+1]-n-1)
				chained[x] = true;
		}

	int good = 0, cur = 0;
	while (good < nsol) {
		if (check(cur)) {
			++good;
			cur = cur + 1 >= nsol ? 0 : cur + 1;
		}
		else {
			good = 0;
			sol[cur] = g.match[ sol[cur]+1 ] - n - 1;
		}
	}

	sort(sol, sol + nsol);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%d", &ns[i]);

		printf("Case %d:", ++ncase);
		solve();
		for (int i = 0; i < nsol; ++i) printf(" %d", ns[ sol[i] ]);
		putchar('\n');
	}

	return 0;
}
