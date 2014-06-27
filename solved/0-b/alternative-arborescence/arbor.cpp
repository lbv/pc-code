#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 10000
#define INF 0x3f3f3f3f

// maximum number of colors to use, 13 chosen arbitrarily
const int MAXK = 13;


typedef unsigned int u32;


struct LineReader {
	char b; LineReader() { read(); }
	void read() { b = getchar_unlocked(); }
	void skip() { while (0 <= b && b <= 32 && b != 10) read(); }
	void skip_line() { skip(); if (b == 10) { read(); skip(); } }
	bool has_next() { skip(); return b > 0 && b != 10; }

	u32 next_u32() {
		u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
	char next_char() { skip(); char c = b; read(); return c; }
};

struct Edge { int v; };
const int MAX_VERT = MAXN;
const int MAX_EDGES = (MAXN-1)*2;
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; memset(adj, -1, sizeof(int)*n); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
};
Graph g;


int n;

// dp[u][i]: minimum sum for the subtree rooted at u, depending on whether
// the root is colored with number i
int dp[MAXN][MAXK + 1];

int vis[MAXN], cvis;


void dfs(int u)
{
	vis[u] = cvis;

	for (int i = 1; i <= MAXK; ++i) dp[u][i] = i;

	for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
		int v = g.edges[i].v;

		if (vis[v] != cvis) {
			dfs(v);

			int aux = INF;
			for (int i = 1; i <= MAXK; ++i) {
				swap(aux, dp[v][i]);
				dp[u][i] += *min_element(dp[v] + 1, dp[v] + MAXK + 1);
				swap(aux, dp[v][i]);
			}
		}
	}
}

int solve()
{
	++cvis;
	dfs(0);
	return *min_element(dp[0] + 1, dp[0] + MAXK + 1);
}

int main()
{
	LineReader lr;

	while (true) {
		n = lr.next_u32();
		if (n == 0) break;
		lr.skip_line();

		g.init(n);
		for (int i = 0; i < n; ++i) {
			int u = lr.next_u32();
			lr.next_char();

			while (lr.has_next()) {
				int v = lr.next_u32();
				g.add(u, (Edge) { v });
				g.add(v, (Edge) { u });
			}
			lr.skip_line();
		}
		lr.skip_line();

		printf("%d\n", solve());
	}

	return 0;
}
