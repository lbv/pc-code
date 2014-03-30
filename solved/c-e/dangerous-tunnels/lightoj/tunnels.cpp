#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define MAXN 100
#define INF 0x3f3f3f3f

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))
#define Inf(m) memset(m, 0x3f, sizeof(m))

const int MAX_VERT = 2*MAXN + 3;
const int MAX_EDGES = 2 * MAX_VERT * (MAX_VERT - 1);


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
	int cap[MAX_VERT][MAX_VERT];
	int flow[MAX_VERT][MAX_VERT];
	int from[MAX_VERT];
	bool vis[MAX_VERT];

	void init_cap(int N) { n = N, m = 0; Neg(adj); Clr(cost); Clr(cap); }
	void add_cap(int u, int v, GraphT w, int c) {
		cost[u][v] = w;  // set cost[v][u] also for bidirectional
		cap[u][v] = c;   // same for cap[v][u]
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

				if (flow[v][u] && dist[u] < dist[v]) {
					dist[v] = dist[u], from[v] = u;
					pq.push(DNode(v, dist[u]));
				}
				if (flow[u][v] < cap[u][v]) {
					GraphT distp = max(dist[u], cost[u][v]);
					if (distp < dist[v]) {
						dist[v] = distp, from[v] = u;
						pq.push(DNode(v, distp));
					}
				}
			}
		}

		return vis[snk];
	}
	int mincost_maxflow(int s, int t, GraphT &fcost) {
		src = s, snk = t;
		Clr(flow);

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
					flow[v][u] -= df;
				else
					flow[u][v] += df, fcost = max(fcost, cost[u][v] * df);
			}
			mflow += df;
		}
		return mflow;
	}
};


#define In(v)  (2*(v)-1)
#define Out(v) (2*(v))


Graph g;
int n, t, k;
int src, snk;


void init_graph()
{
	src = 0;
	snk = Out(n+1);
	g.init_cap(2*n + 3);

	for (int i = 1; i <= n; ++i)
		g.add_cap(In(i), Out(i), 0, 1);
}

void solve()
{
	int cost;
	int flow = g.mincost_maxflow(src, snk, cost);

	if (flow != k)
		puts("no solution");
	else
		printf("%d\n", cost);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &n, &t);
		init_graph();

		while (t--) {
			int p, q, d;
			scanf("%d%d%d", &p, &q, &d);

			if (p > q) swap(p, q);
			g.add_cap(Out(p), In(q), d, 1);
		}
		scanf("%d", &k);

		g.add_cap(In(n + 1), snk, 0, k);

		printf("Case %d: ", ++ncase);
		solve();
	}

	return 0;
}
