#include <cstdio>
#include <cstdlib>
#include <cstring>


#define MAXM 500
#define INF 0x3f3f3f3f


struct Edge { int v; };

const int MAX_VERT = MAXM*2 + 2;
const int MAX_EDGES = MAX_VERT*(MAX_VERT-1) / 2;
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
		memset(adj, -1, sizeof(int) * n);
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
		memset(match, 0, sizeof(int)*n);
		while (bfs())
			for (int i = 1; i <= x; ++i)
				if (match[i] == 0 && dfs(i)) ++m;
		return m;
	}
};


int dist(int x1, int y1, int x2, int y2)
{
	return abs(x1-x2) + abs(y1-y2);
}

struct Request {
	int t, a, b, c, d;

	bool can_connect(const Request &r) const {
		return t + dist(a, b, c, d) + dist(c, d, r.a, r.b) < r.t;
	}
};


int M;
Request rs[MAXM];
Graph g;


int solve()
{
	g.init_bipart_basic(M);

	for (int i = 0; i < M; ++i)
		for (int j = i + 1; j < M; ++j)
			if (rs[i].can_connect(rs[j]))
				g.add_bipart(i, j);

	return M - g.max_matching();
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &M);

		for (int i = 0; i < M; ++i) {
			int h, m, a, b, c, d;
			scanf("%d:%d%d%d%d%d", &h, &m, &a, &b, &c, &d);

			rs[i] = (Request) { h*60 + m, a, b, c, d };
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
