#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100
#define MAXM 10000

#define INF 0x3f3f3f3f

#define Inf(m) memset(m, 0x3f, sizeof(m))


typedef int GraphT;

struct Set {
	int s[MAXN];
	Set() {}
	void init(int n) { for (int i=0; i < n; ++i) s[i] = i; }
	int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
	void merge(int i, int j) { s[find(i)] = find(j); }
};

struct Edge {
	int u, v; GraphT w;

	bool operator<(const Edge &e) const { return w < e.w; }
};


int gmst[MAXN][MAXN];


const int MAX_VERT = MAXN;
const int MAX_EDGES = MAXM;
struct Graph {
	Edge edges[MAX_EDGES];
	int n, m;

	void init(int N) { n = N, m = 0; }

	void add_und(const Edge &e) { edges[m++] = e; }

	//
	// Kruskal
	//
	Set uf;

	// Modified to store a matrix adjacency graph
	void kruskal_mst(int &ans) {
		sort(edges, edges + m);
		uf.init(n);
		int nedges = 0;
		ans = 0;
		for (int i = 0; i < m; ++i) {
			Edge &e = edges[i];
			if (uf.find(e.u) == uf.find(e.v)) continue;
			uf.merge(e.u, e.v);
			gmst[e.u][e.v] = gmst[e.v][e.u] = e.w;
			ans += e.w;
			if (++nedges == n - 1) break;
		}
	}

	// Modified to use the previous adjacency graph, and find the second
	// cheapest MST
	void kruskal_mst2(int &ans) {
		uf.init(n);
		ans = 0;

		int mindiff = INF;
		for (int i = 0; i < m; ++i) {
			Edge &e = edges[i];
			if (uf.find(e.u) == uf.find(e.v)) {
				mindiff = min(mindiff, e.w - gmst[e.u][e.v]);
				continue;
			}

			uf.merge(e.u, e.v);
			ans += e.w;
		}

		ans += mindiff;
	}
};


Graph g;
int N, M;


int mst1, mst2;


void floyd_warshall()
{
	for (int k = 0; k < N; ++k)
		for(int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				gmst[i][j] = min(gmst[i][j], max(gmst[i][k], gmst[k][j]));
}

void solve()
{
	Inf(gmst);
	g.kruskal_mst(mst1);
	floyd_warshall();
	g.kruskal_mst2(mst2);
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d%d", &N, &M);

		g.init(N);
		while (M--) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);

			if (u != v)
				g.add_und((Edge) { u-1, v-1, w });
		}

		solve();
		printf("%d %d\n", mst1, mst2);
	}

	return 0;
}
