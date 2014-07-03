#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXV 500

#define INF 0x3f3f3f3f


struct Edge { int v; };

const int MAX_VERT = MAXV * 2 + 2;
const int MAX_EDGES = MAXV * MAXV;
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

struct Vote {
	int x, y;
};


int m, f, v;
Graph g;

Vote mv[MAXV];  // male voters
Vote fv[MAXV];  // female voters
int nmv, nfv;


int solve()
{
	g.init_bipart_basic(max(nmv, nfv));

	for (int i = 0; i < nmv; ++i)
		for (int j = 0; j < nfv; ++j)
			if (mv[i].x == fv[j].y || mv[i].y == fv[j].x)
				g.add_bipart(i, j);

	return v - g.max_matching();
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &m, &f, &v);

		nmv = nfv = 0;

		for (int i = 0; i < v; ++i) {
			char t;
			int n1, n2;
			scanf(" %c%d %*c%d", &t, &n1, &n2);

			if (t == 'M')
				mv[nmv++] = (Vote) { n1-1, n2-1 };
			else
				fv[nfv++] = (Vote) { n1-1, n2-1 };
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
