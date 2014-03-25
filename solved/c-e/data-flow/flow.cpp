#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define MAX_VERT 101
const int MAX_EDGES = 2*5001;
#define INF 0x3f3f3f3f3f3f3f3fLL

#define Clr(m) memset(m, 0, sizeof(m))
#define Inf(m) memset(m, 0x3f, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


typedef long long i64;
typedef i64 GraphT;


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };

struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	struct DNode {
		int v; GraphT d;
		DNode() {}
		DNode(int V, GraphT D): v(V), d(D) {}
		bool operator<(const DNode &n) const { return d > n.d; }
	};
	int src, snk;
	GraphT cost[MAX_VERT][MAX_VERT];
	GraphT cap[MAX_VERT][MAX_VERT];
	GraphT flow[MAX_VERT][MAX_VERT];
	GraphT dist[MAX_VERT];
	GraphT price[MAX_VERT];
	int from[MAX_VERT];
	bool vis[MAX_VERT];

	void init_cap(int N) { n = N, m = 0; Neg(adj); Clr(cost); Clr(cap); }
	void add_cap(int u, int v, GraphT w, GraphT c) {
		cost[u][v] = cost[v][u] = w;
		cap[u][v] = cap[v][u] = c;
		add(u, Edge(v));
		add(v, Edge(u));
	}
	bool find_spath() {
		Inf(dist); Neg(from); Clr(vis);
		dist[src] = 0;

		priority_queue<DNode> pq;
		pq.push(DNode(src, 0));

		while (! pq.empty()) {
			int u = pq.top().v; pq.pop();
			if (vis[u]) continue;
			vis[u] = true;
			for (int i = adj[u]; i >= 0; i = next[i]) {
				int v = edges[i].v;

				GraphT distp = dist[u] + price[u] - cost[v][u] - price[v];
				if (flow[v][u] && distp < dist[v]) {
					dist[v] = distp, from[v] = u;
					pq.push(DNode(v, distp));
				}
				distp = dist[u] + price[u] + cost[u][v] - price[v];
				if (flow[u][v] < cap[u][v] && distp < dist[v]) {
					dist[v] = distp, from[v] = u;
					pq.push(DNode(v, distp));
				}
			}
		}

		for (int i = 0; i < n; ++i) if (vis[i]) price[i] += dist[i];

		return vis[snk];
	}
	GraphT mincost_maxflow(int s, int t, GraphT &fcost) {
		src = s, snk = t;
		Clr(flow); Clr(price);

		GraphT mflow = fcost = 0;
		while (find_spath()) {
			GraphT df = INF;
			for (int v = snk, u = from[v]; v != src; u = from[v=u]) {
				GraphT f = flow[v][u] ? flow[v][u] : (cap[u][v] - flow[u][v]);
				df = min(df, f);
			}

			for (int v = snk, u = from[v]; v != src; u = from[v=u]) {
				if (flow[v][u])
					flow[v][u] -= df, fcost -= df * cost[v][u];
				else
					flow[u][v] += df, fcost += df * cost[u][v];
			}
			mflow += df;
		}

		return mflow;
	}
};


int N, M;
i64 D, K;
Graph g;


void solve()
{
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			if (g.cap[i][j] == -1) g.cap[i][j] = K;

	g.add_cap(N, 0, 0, D);
	i64 cost;
	i64 flow = g.mincost_maxflow(1, 0, cost);
	if (flow == D)
		printf("%lld\n", cost);
	else
		puts("Impossible.");
}

int main()
{
	while (true) {
		if (scanf("%d%d", &N, &M) != 2) break;
		g.init_cap(N + 1);

		while (M--) {
			int u, v;
			i64 w;
			scanf("%d%d%lld", &u, &v, &w);
			g.add_cap(u, v, w, -1);
		}

		scanf("%lld%lld", &D, &K);
		solve();
	}

	return 0;
}
