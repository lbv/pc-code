#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXM 20
#define MAXN 20
#define INF  0x3f3f3f3f

const int MAX_VERT = MAXM * MAXN * 2;
const int MAX_EDGES = MAX_VERT * 4;

#define Neg(m) memset(m, -1, sizeof(m))
#define Clr(m) memset(m, 0, sizeof(m))


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };

struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}
	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	int x, src, snk;
	void init_bipart(int X) {
		x = X;
		n = 2*x + 2, src = 0, snk = 2*x + 1, m = 0;
		Neg(adj);
	}

	void add_bipart(int v1, int v2) {
		int u = 1 + v1;
		int v = x + 1 + v2;
		add(u, Edge(v));
	}

	//
	// Hopcroft-Karp for bipartite matching.
	//
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

int m, n;
char grid[MAXM][MAXN + 1];
int idx[MAXM][MAXN];

Graph g;

const int moves[4][2] = {
	{ -1,  0 },
	{  1,  0 },
	{  0,  1 },
	{  0, -1 }
};

bool is_valid(int r, int c)
{
	return 0 <= r && r < m && 0 <= c && c < n;
}

int solve()
{
	int x = 0, y = 0;

	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j) {
			if (grid[i][j] != '*') continue;

			if ((i+j) % 2 == 0) idx[i][j] = x++;
			else idx[i][j] = y++;
		}

	g.init_bipart(max(x, y));

	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j) {
			if (grid[i][j] != '*' || (i+j) % 2 != 0) continue;

			for (int k = 0; k < 4; ++k) {
				int r = i + moves[k][0];
				int c = j + moves[k][1];
				if (is_valid(r, c) && grid[r][c] == '*')
					g.add_bipart(idx[i][j], idx[r][c]);
			}
		}

	return x + y - g.max_matching();
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &m, &n);
		for (int i = 0; i < m; ++i) scanf("%s", grid[i]);
		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
