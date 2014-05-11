#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100000

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


const int MAX_VERT = MAXN + 1;
const int MAX_EDGES = 2*(MAXN + 1);
struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
};


int n, cnt;
Graph g;

int init[MAXN + 1];
int goal[MAXN + 1];
int sol[MAXN];

bool vis[MAXN + 1];


void dfs(int u, int level, int flips_even, int flips_odd)
{
	vis[u] = true;

	int val = init[u];
	if (level % 2 == 0) {
		val = (val + flips_even) % 2;
		if (val != goal[u])
			++flips_even, sol[cnt++] = u;
	}
	else {
		val = (val + flips_odd) % 2;
		if (val != goal[u])
			++flips_odd, sol[cnt++] = u;
	}

	for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
		int v = g.edges[i].v;

		if (! vis[v]) dfs(v, level + 1, flips_even, flips_odd);
	}
}

int main()
{
	scanf("%d", &n);
	g.init(n + 1);

	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.add(u, Edge(v));
		g.add(v, Edge(u));
	}

	for (int i = 1; i <= n; ++i) scanf("%d", &init[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &goal[i]);

	dfs(1, 0, 0, 0);

	printf("%d\n", cnt);
	sort(sol, sol + cnt);
	for (int i = 0; i < cnt; ++i) printf("%d\n", sol[i]);

	return 0;
}
