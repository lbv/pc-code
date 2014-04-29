#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 10
#define MAXM 25
#define INF 0x3f3f3f3f

const int MAX_VERT = MAXM + MAXN + 1;
const int MAX_EDGES = 2 * (MAXM * MAXN + MAXM);

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


// for max-flow models
struct Edge {
	int v, c, f, r;  // capacity, flow, reverse edge
	Edge() {}
	Edge(int V, int C, int R) : v(V), c(C), f(0), r(R) {}
};
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}
	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
	//
	// Dinitz Algorithm (Max Flow)
	//
	void add_pair(int u, int v, int c) {
		add(u, Edge(v, c, m + 1));
		add(v, Edge(u, 0, m - 1)); // or Edge(u,c,m-1) for bi-directional
	}
	int src, snk;
	int ptr[MAX_VERT];
	int dist[MAX_VERT];
	int q[MAX_VERT];

	bool bfs() {
		int qb = 0, qf = 0;
		Neg(dist);
		dist[src] = 0;
		q[qb++] = src;
		while (qf < qb) {
			int u = q[qf++];
			for (int i = adj[u]; i >= 0; i = next[i]) {
				Edge &e = edges[i];
				if (e.f >= e.c || dist[e.v] >= 0) continue;
				dist[e.v] = dist[u] + 1, q[qb++] = e.v;
			}
		}
		return dist[snk] >= 0;
	}
	int dfs(int u, int fl) {
		if (u == snk) return fl;
		for (int &i = ptr[u]; i >= 0; i = next[i]) {
			Edge &e = edges[i]; int df;
			if (e.f >= e.c || dist[e.v] != dist[u] + 1) continue;
			if ((df = dfs(e.v, min(e.c - e.f, fl))) == 0) continue;
			e.f += df, edges[e.r].f -= df;
			return df;
		}
		return 0;
	}
	int max_flow(int s, int t) {
		src = s, snk = t;
		int ans = 0, df;
		while (bfs()) {
			for (int i = 0; i < n; ++i) ptr[i] = adj[i];
			while (true) {
				if ((df = dfs(src, INF)) == 0) break;
				ans += df;
			}
		}
		return ans;
	}
};


int n, m;
int stk[MAXM + 1];  // count of stickers for a person
Graph g;


void read_stickers(int p)
{
	int k;
	scanf("%d", &k);

	Clr(stk);
	for (int i = 0; i < k; ++i) {
		int s;
		scanf("%d", &s);
		++stk[s];
	}

	if (p == 0) {
		for (int i = 1; i <= m; ++i)
			if (stk[i] > 0)
				g.add_pair(0, i, stk[i]);
	}
	else {
		int u = m + p;
		for (int i = 1; i <= m; ++i)
			if (stk[i] > 1)
				g.add_pair(u, i, stk[i] - 1);
			else if (stk[i] == 0)
				g.add_pair(i, u, 1);
	}

}

int solve()
{
	int snk = m + n;

	for (int i = 1; i <= m; ++i)
		g.add_pair(i, snk, 1);

	return g.max_flow(0, snk);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &n, &m);

		g.init(n + m + 1);
		for (int i = 0; i < n; ++i) read_stickers(i);

		printf("Case #%d: %d\n", ++ncase, solve());
	}

	return 0;
}
