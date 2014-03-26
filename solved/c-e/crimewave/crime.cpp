#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXS 50
#define MAXA 50
#define INF 0x3f3f3f3f

const int MAX_VERT = MAXS * MAXA * 2 + 2;
const int MAX_EDGES = MAX_VERT * 5 * 2;


#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


// for max-flow models
struct Edge {
	int v;
	int c, f;  // capacity, flow
	int r;     // reverse edge
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
	// Dinitz Algorithm
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


int s, a;
int src, snk;
int banks;

Graph g;

bool vis[MAXS + 1][MAXA + 1];

const int moves[4][2] = {
	{ -1,  0 },
	{  1,  0 },
	{  0,  1 },
	{  0, -1 }
};


#define In(i,j)  (2 * ((i)*a + (j)))
#define Out(i,j) (In(i,j)+1)

bool is_valid(int r, int c)
{
	return 0 <= r && r < s && 0 <= c && c < a;
}

void init_graph()
{
	src = s * a * 2;
	snk = s * a * 2 + 1;

	g.init(s*a*2 + 2);

	for (int i = 0; i < s; ++i)
		for (int j = 0; j < a; ++j) {
			g.add_pair(In(i, j), Out(i, j), 1);

			for (int k = 0; k < 4; ++k) {
				int i2 = i + moves[k][0];
				int j2 = j + moves[k][1];
				if (is_valid(i2, j2))
					g.add_pair(Out(i, j), In(i2, j2), 1);
			}

			if (i == 0 || i == s -1 || j == 0 || j == a - 1)
				g.add_pair(Out(i, j), snk, 1);
		}
}

bool solve()
{
	return g.max_flow(src, snk) == banks;
}

int main()
{
	int p;
	scanf("%d", &p);

	while (p--) {
		int b;
		scanf("%d%d%d", &s, &a, &b);
		init_graph();
		Clr(vis);
		banks = 0;

		bool bleh = false;
		while (b--) {
			int x, y;
			scanf("%d%d", &x, &y);
			if (vis[x][y]) { bleh = true; continue; }

			vis[x][y] = true;
			++banks;
			g.add_pair(src, In(x-1, y-1), 1);
		}

		if (! bleh && solve())
			puts("possible");
		else
			puts("not possible");
	}

	return 0;
}

