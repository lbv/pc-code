#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define MAXN 50
#define MAXP 1000

#define ClrN(m,n,t) memset(m, 0, sizeof(t)*(n))
#define NegN(m,n,t) memset(m, -1, sizeof(t)*(n))
#define InfN(m,n,t) memset(m, 0x3f, sizeof(t)*(n))


struct Edge { int u, v, w, r; };

const int MAX_VERT = 2*MAXN + 2;
const int MAX_EDGES = 2 * (MAXN*MAXN + 2*MAXN);
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; NegN(adj, n, int); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	/////////////////////////////////////////////
	////////// Bi-Partite Graphs ////////////////
	/////////////////////////////////////////////
	int x, src, snk;
	void init_bipart_basic(int X) {
		x = X, n = 2*x + 2, src = 0, snk = 2*x + 1, m = 0;
		NegN(adj, n, int);
	}

	//
	// Min-cost matching.
	//
	int price[MAX_VERT];
	int dist[MAX_VERT];
	int from[MAX_VERT];
	bool vis[MAX_VERT];
	bool use_edge[MAX_EDGES];
	struct DNode {
		int v, d;
		DNode() {}
		DNode(int V, int D): v(V), d(D) {}
		bool operator<(const DNode &n) const { return d > n.d; }
	};

	void init_bipart(int X) {
		init_bipart_basic(X);
		ClrN(price, n, int);
		InfN(price + x + 1, x, int);
	}
	void add_bipart(int v1, int v2, int w) {
		int u = 1 + v1;
		int v = x + 1 + v2;
		add_pair(u, v, w);
		price[v] = min(price[v], w);
	}
	void add_pair(int u, int v, int c) {
		use_edge[m] = true;
		add(u, (Edge) { u, v, c, m + 1 });
		use_edge[m] = false;
		add(v, (Edge) { v, u, -c, m - 1 });
	}

	void dijkstra_paths() {
		InfN(dist, n, int);
		NegN(from, n, int);
		ClrN(vis, n, bool);
		priority_queue<DNode> pq;
		pq.push(DNode(src, 0));
		dist[src] = 0;

		while (! pq.empty()) {
			DNode cur = pq.top(); pq.pop();
			if (vis[cur.v]) continue;
			vis[cur.v] = true;
			for (int i = adj[cur.v]; i >= 0; i = next[i]) {
				if (! use_edge[i]) continue;
				Edge &e = edges[i];

				int distp = dist[cur.v] + price[cur.v] + e.w - price[e.v];
				if (distp >= dist[e.v]) continue;

				dist[e.v] = distp;
				from[e.v] = i;
				pq.push(DNode(e.v, distp));
			}
		}
	}
	void augment_spath() {
		for (int i = from[snk]; i >= 0; ) {
			Edge &e = edges[i];
			use_edge[i] = false;
			use_edge[e.r] = true;
			i = from[e.u];
		}
	}
	void reduce_prices() {
		for (int i = 1, I = 2*x; i <= I; ++i) price[i] += dist[i];
	}
	void connect_src_snk() {
		for (int i = 1; i <= x; ++i) add_pair(src, i, 0);
		for (int i = x + 1, I = 2*x; i <= I; ++i) add_pair(i, snk, 0);
	}
	bool mincost_match(int &cost) {
		connect_src_snk();

		for (int i = 1; i <= x; ++i) {
			dijkstra_paths();
			if (from[snk] < 0) return false;
			augment_spath();
			reduce_prices();
		}

		cost = 0;
		for (int i = x + 1, I = 2*x; i <= I; ++i)
			for (int j = adj[i]; j >= 0; j = next[j]) {
				if (! use_edge[j]) continue;
				Edge &e = edges[j];
				cost += -e.w;
			}

		return true;
	}
};


int n;
Graph g;


int solve()
{
	int cost;
	g.mincost_match(cost);
	return n*MAXP - cost;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &n);
		g.init_bipart(n);

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) {
				int p;
				scanf("%d", &p);
				g.add_bipart(i, j, MAXP - p);
			}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
