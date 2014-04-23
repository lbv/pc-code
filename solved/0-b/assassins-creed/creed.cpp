#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 15
#define MAXM 50

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


const int MAX_VERT = MAXN;
const int MAX_EDGES = MAXM;


typedef unsigned int u32;


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}
	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
};


int n, m;
Graph g;

bool vis[MAXN][1 << MAXN];
bool covered[1 << MAXN];

u32 paths[1 << MAXN];
int npaths;

int memo[1 << MAXN];


void dfs(int u, u32 b)
{
	vis[u][b] = true;

	b |= 1 << u;

	if (! covered[b]) {
		covered[b] = true;
		paths[npaths++] = b;
	}

	for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
		int v = g.edges[i].v;
		if (! vis[v][b]) dfs(v, b);
	}
}

int dp(u32 b)
{
	if (memo[b] >= 0) return memo[b];
	int &ans = memo[b];

	if (covered[b]) return ans = 1;

	ans = n;

	for (int i = 0; i < npaths; ++i)
		if ((paths[i] & b) == paths[i])
			ans = min(ans, 1 + dp(b & ~paths[i]));

	return ans;
}

int solve()
{
	Clr(vis);
	Clr(covered);
	npaths = 0;
	for (int i = 0; i < n; ++i) dfs(i, 0);

	Neg(memo);

	return dp((1 << n) - 1);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &n, &m);
		g.init(n);

		while (m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			g.add(u - 1, Edge(v - 1));
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
