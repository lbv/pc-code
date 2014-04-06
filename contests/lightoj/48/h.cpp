/**
 * LightOJ Contest #48: IIUPC - 2011
 *
 * Problem H: Tracking Community
 *
 * Keywords:
 *   - minimum spanning tree
 */

#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 10000
#define MAXM 100000

const int MAX_VERT = MAXN;
const int MAX_EDGES = MAXM;

typedef long long i64;
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
	Edge() {}
	Edge(int U, int V, GraphT W) : u(U), v(V), w(W) {}
	bool operator<(const Edge &e) const { return w < e.w; }
};

struct Graph {
	Edge edges[MAX_EDGES];
	int n, m;
	Graph() {}
	void init(int N) { n = N, m = 0; }

	void add_und(const Edge &e) { edges[m++] = e; }

	Set uf;
	int kruskal_variant(int K) {
		sort(edges, edges + m);
		uf.init(n);
		int nedges = 0;
		i64 sum = 0;
		for (int i = 0; i < m; ++i) {
			Edge &e = edges[i];
			if (sum + e.w > K) break;
			if (uf.find(e.u) == uf.find(e.v)) continue;
			uf.merge(e.u, e.v);
			sum += e.w;
			if (++nedges == n - 1) break;
		}
		return nedges;
	}
};


int N, M, K;

Graph g;


int solve()
{
	return N - g.kruskal_variant(K);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &N, &M, &K);
		g.init(N);

		int X, Y, C;
		while (M--) {
			scanf("%d%d%d", &X, &Y, &C);
			g.add_und(Edge(X-1, Y-1, C));
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
