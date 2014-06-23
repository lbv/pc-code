#include <cstdio>
#include <cstring>
using namespace std;


#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };

const int MAX_VERT = 26;
const int MAX_EDGES = MAX_VERT * MAX_VERT;
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
};


Graph g;
char inp[64];
bool used[26];
int vis[26], cvis;
int trees, acorns;



int dfs(int u)
{
	vis[u] = cvis;
	int cnt = 1;

	for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
		int v = g.edges[i].v;
		if (vis[v] != cvis) cnt += dfs(v);
	}
	return cnt;
}

void solve()
{
	trees = acorns = 0;

	++cvis;
	for (int i = 0; i < 26; ++i)
		if (used[i] && vis[i] != cvis) {
			int sz = dfs(i);
			if (sz == 1) ++acorns;
			else ++trees;
		}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		g.init(26);

		while (true) {
			scanf("%s", inp);
			if (inp[0] == '*') break;

			int u = inp[1] - 'A';
			int v = inp[3] - 'A';
			g.add(u, Edge(v));
			g.add(v, Edge(u));
		}

		Clr(used);
		scanf("%s", inp);
		for (int i = 0, n = strlen(inp); i < n; ++i)
			if ('A' <= inp[i] && inp[i] <= 'Z')
				used[inp[i] - 'A'] = true;

		solve();
		printf("There are %d tree(s) and %d acorn(s).\n", trees, acorns);
	}

	return 0;
}
