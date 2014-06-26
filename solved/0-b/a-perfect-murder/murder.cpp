#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 1000

#define Neg(m) memset(m, -1, sizeof(m))


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };

const int MAX_VERT = MAXN;
const int MAX_EDGES = 2*(MAXN - 1);
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
};


int N, M;
int vis[MAXN], cvis;
Graph g;

// dp[u][x]: Maximum # of mosquitos that can be killed from node u, depending
// on whether u is killed or not (x=0: u is not killed, x=1: u is killed)
int dp[MAXN][2];


void dfs(int u)
{
	vis[u] = cvis;

	dp[u][0] = 0;
	dp[u][1] = 1;

	for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
		int v = g.edges[i].v;

		if (vis[v] != cvis) {
			dfs(v);
			dp[u][0] += max(dp[v][0], dp[v][1]);
			dp[u][1] += dp[v][0];
		}
	}
}

int solve()
{
	int ans = 0;

	++cvis;
	for (int i = 0; i < N; ++i)
		if (vis[i] != cvis) {
			dfs(i);
			ans += max(dp[i][0], dp[i][1]);
		}

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &N, &M);
		g.init(N);

		while (M--) {
			int u, v;
			scanf("%d%d", &u, &v);
			g.add(u-1, Edge(v-1));
			g.add(v-1, Edge(u-1));
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
