#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 1000

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


const int MAX_VERT = MAXN;
const int MAX_EDGES = 2*MAXN;
struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
};

struct State {
	int p;  // number of lampposts
	int q;  // number of roads receiving light from two lampposts

	State() {}
	State(int P, int Q): p(P), q(Q) {}

	bool operator<(const State &x) const {
		if (p != x.p) return p < x.p;
		return q > x.q;
	}

	State &operator+=(const State &x) {
		p += x.p;
		q += x.q;
		return *this;
	}
};


int N, M;
Graph g;

bool vis[MAXN];
State dp[MAXN][2];


void dfs(int u)
{
	vis[u] = true;

	dp[u][0] = State(0, 0);
	dp[u][1] = State(1, 0);

	for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
		int v = g.edges[i].v;
		if (vis[v]) continue;

		dfs(v);
		dp[u][0] += dp[v][1];

		if (dp[v][0] < dp[v][1])
			dp[u][1] += dp[v][0];
		else {
			dp[u][1] += dp[v][1];
			++dp[u][1].q;
		}
	}
}

State solve()
{
	Clr(vis);
	State ans(0, 0);

	for (int i = 0; i < N; ++i)
		if (! vis[i]) {
			dfs(i);
			ans += min(dp[i][0], dp[i][1]);
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

		for (int i = 0; i < M; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			g.add(u, Edge(v));
			g.add(v, Edge(u));
		}

		printf("Case %d: ", ++ncase);
		State sol = solve();
		printf("%d %d %d\n", sol.p, sol.q, M - sol.q);
	}

	return 0;
}
