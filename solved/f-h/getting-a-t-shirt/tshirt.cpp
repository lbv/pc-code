#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXM 50
#define INF 0x3f3f3f3f

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


const int MAX_VERT = MAXM + 8;
const int MAX_EDGES = 2 * (MAXM + MAXM*2 + 6);

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


int N, M;
Graph g;
int src, snk;

char shirt[4];


void init_graph()
{
	g.init(M + 8);
	src = 0;
	snk = M + 7;

	for (int i = 1; i <= M; ++i)
		g.add_pair(src, i, 1);

	for (int i = 1; i <= 6; ++i)
		g.add_pair(M + i, snk, N);
}

bool solve()
{
	int flow = g.max_flow(src, snk);
	return flow == M;
}

int read_shirt()
{
	scanf("%s", shirt);

	if (shirt[0] == 'L') return M + 1;
	if (shirt[0] == 'M') return M + 2;
	if (shirt[0] == 'S') return M + 3;

	if (shirt[1] == 'X') return M + 4;
	if (shirt[1] == 'L') return M + 5;
	return M + 6;
}

void read_shirt_options(int &op1, int &op2)
{
	op1 = read_shirt();
	op2 = read_shirt();
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &N, &M);
		init_graph();

		for (int i = 1; i <= M; ++i) {
			int s1, s2;
			read_shirt_options(s1, s2);
			g.add_pair(i, s1, 1);
			g.add_pair(i, s2, 1);
		}

		printf("Case %d: ", ++ncase);

		if (solve())
			puts("YES");
		else
			puts("NO");
	}

	return 0;
}
