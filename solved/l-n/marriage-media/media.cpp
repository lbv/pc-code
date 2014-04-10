#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;


#define MAXM 50
#define INF 0x3f3f3f3f

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))

const int MAX_VERT  = 2 * MAXM + 2;
const int MAX_EDGES = MAXM*MAXM;


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	int x, src, snk;
	void init_bipart(int X) {
		x = X;
		n = 2*x + 2, src = 0, snk = 2*x + 1, m = 0;
		Neg(adj);
	}


	//
	// Hopcroft-Karp for bipartite matching.
	//
	void add_bipart(int v1, int v2) {
		int u = 1 + v1;
		int v = x + 1 + v2;
		add(u, Edge(v));
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
		Clr(match);
		while (bfs())
			for (int i = 1; i <= x; ++i)
				if (match[i] == 0 && dfs(i)) ++m;
		return m;
	}
};

struct Person {
	int h, a, d;  // height, age, divorced
	Person() {}
	Person(int H, int A, int D): h(H), a(A), d(D) {}

	bool can_match_with(const Person &p) const {
		return abs(h - p.h) <= 12 && abs(a - p.a) <= 5 && d == p.d;
	}
};


int m, n;
Graph g;

Person men[MAXM];
Person women[MAXM];


int solve()
{
	g.init_bipart(max(m, n));

	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			if (men[i].can_match_with(women[j]))
				g.add_bipart(i, j);

	return g.max_matching();
}

void read_person(Person &p)
{
	int h, a, d;
	scanf("%d%d%d", &h, &a, &d);
	p = Person(h, a, d);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &m, &n);
		for (int i = 0; i < m; ++i) read_person(men[i]);
		for (int i = 0; i < n; ++i) read_person(women[i]);

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
