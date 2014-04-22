#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define MAXN 50
#define INF  0x3f3f3f3f

#define Clr(m) memset(m, 0, sizeof(m))
#define Inf(m) memset(m, 0x3f, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))

const int MAX_VERT = MAXN + 1;
const int MAX_EDGES = 2 * (MAXN * (MAXN - 1) / 2 + 1);


typedef int GraphT;


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	//
	// Min-cost max-flow
	//
	struct DNode {
		int v; GraphT d;
		DNode() {}
		DNode(int V, GraphT D): v(V), d(D) {}
		bool operator<(const DNode &n) const { return d > n.d; }
	};
	int src, snk;
	GraphT cost[MAX_VERT][MAX_VERT];
	GraphT dist[MAX_VERT];
	GraphT price[MAX_VERT];
	int cap[MAX_VERT][MAX_VERT];
	int flow[MAX_VERT][MAX_VERT];
	int from[MAX_VERT];
	bool vis[MAX_VERT];

	void init_cap(int N) { n = N, m = 0; Neg(adj); Clr(cost); Clr(cap); }
	void add_cap(int u, int v, GraphT w, int c) {
		cost[u][v] = cost[v][u] = w;  // set cost[v][u] also for bidirectional
		cap[u][v] = cap[v][u] = c;    // same for cap[v][u]
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
	int mincost_maxflow(int s, int t, GraphT &fcost) {
		src = s, snk = t;
		Clr(flow); Clr(price);

		fcost = 0;
		int mflow = 0;
		while (find_spath()) {
			int df = INF;
			for (int v = snk, u = from[v]; v != src; u = from[v=u]) {
				int f = flow[v][u] ? flow[v][u] : (cap[u][v] - flow[u][v]);
				df = min(df, f);
			}

			for (int v = snk, u = from[v]; v != src; u = from[v=u]) {
				if (flow[v][u])
					flow[v][u] -= df, fcost -= cost[v][u] * df;
				else
					flow[u][v] += df, fcost += cost[u][v] * df;
			}
			mflow += df;
		}
		return mflow;
	}
};


int N, M, P;
Graph g;


int solve()
{
	g.add_cap(0, 1, 0, P);
	int cost;
	int flow = g.mincost_maxflow(0, N, cost);

	if (flow != P) return -1;
	return cost;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &N, &M, &P);
		g.init_cap(N + 1);

		while (M--) {
			int u, v, w, c;
			scanf("%d%d%d%d", &u, &v, &w, &c);
			g.add_cap(u, v, c, w);
		}

		printf("Case %d: ", ++ncase);

		int ans = solve();
		if (ans < 0)
			puts("impossible");
		else
			printf("%d\n", ans);
	}

	return 0;
}
