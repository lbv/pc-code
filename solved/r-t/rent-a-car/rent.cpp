#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define MAXN 50
#define MAXC 50
#define MAXR 50
#define MAXD 100

#define INF 0x3f3f3f3f

#define Clr(m) memset(m, 0, sizeof(m))
#define Inf(m) memset(m, 0x3f, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


typedef int GraphT;


const int MAX_VERT = 2 + 2*MAXN + MAXC;
const int MAX_EDGES = (MAXC*2 + MAXN*2 + MAXN + MAXN*MAXN) * 2;
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


int N, C, R;
int rs[MAXN];
int cs[MAXC];
int ps[MAXC];
int ds[MAXR];
int ss[MAXR];

Graph g;

int days[MAXN];
int services[MAXN];
int companies[MAXC];

int best_service[MAXD + 1];

int solve()
{
	R = 0;
	for (int i = 1; i <= MAXD; ++i)
		if (best_service[i] >= 0) {
			ds[R] = i;
			ss[R++] = best_service[i];
		}

	int idx = 0;
	int src = idx++;
	int snk = idx++;

	for (int i = 0; i < N; ++i) days[i] = idx++;
	for (int i = 0; i < N; ++i) services[i] = idx++;
	for (int i = 0; i < C; ++i) companies[i] = idx++;

	g.init_cap(N*2 + C + 2);

	int total = 0;
	for (int i = 0; i < N; ++i) {
		total += rs[i];
		g.add_cap(days[i], snk, 0, rs[i]);
	}
	for (int i = 1; i < N; ++i)
		g.add_cap(days[i-1], days[i], 0, INF);

	for (int i = 0; i < C; ++i) {
		g.add_cap(src, companies[i], ps[i], cs[i]);
		g.add_cap(companies[i], days[0], 0, INF);
	}

	for (int i = 0; i < N; ++i) {
		g.add_cap(src, services[i], 0, rs[i]);

		for (int j = 0; j < R; ++j)
			if (i + ds[j] + 1 < N)
				g.add_cap(services[i], days[i + ds[j] + 1], ss[j], INF);
	}

	int cost;
	int flow = g.mincost_maxflow(src, snk, cost);

	if (flow != total) return -1;
	return cost;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &N, &C, &R);

		for (int i = 0; i < N; ++i) scanf("%d", &rs[i]);
		for (int i = 0; i < C; ++i) scanf("%d%d", &cs[i], &ps[i]);

		Neg(best_service);
		while (R--) {
			int d, s;
			scanf("%d%d", &d, &s);

			if (best_service[d] < 0 || s < best_service[d])
				best_service[d] = s;
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
