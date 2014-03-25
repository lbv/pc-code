#include <cctype>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define MAXN 30
#define MAXM 100
#define MAXK 26
#define INF  0x3f3f3f3f

const int MAX_VERT = MAXM + MAXN + 2;
const int MAX_EDGES = 2 * (MAXK * MAXM + MAXK + MAXM);

#define Clr(m) memset(m, 0, sizeof(m))
#define Inf(m) memset(m, 0x3f, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


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
		int v, d;
		DNode() {}
		DNode(int V, int D): v(V), d(D) {}
		bool operator<(const DNode &n) const { return d > n.d; }
	};
	int src, snk;
	int cost[MAX_VERT][MAX_VERT];
	int cap[MAX_VERT][MAX_VERT];
	int flow[MAX_VERT][MAX_VERT];
	int from[MAX_VERT];
	int dist[MAX_VERT];
	int price[MAX_VERT];
	bool vis[MAX_VERT];

	void init_cap(int N) { n = N, m = 0; Neg(adj); Clr(cost); Clr(cap); }
	void add_cap(int u, int v, int w, int c) {
		cost[u][v] = w;
		cap[u][v] = c;
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

				int distp = dist[u] + price[u] - cost[v][u] - price[v];
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
	int mincost_maxflow(int s, int t, int &fcost) {
		src = s, snk = t;
		Clr(flow); Clr(price);

		int mflow = fcost = 0;
		while (find_spath()) {
			int df = INF;
			for (int v = snk, u = from[v]; v != src; u = from[v=u]) {
				int f = flow[v][u] ? flow[v][u] : (cap[u][v] - flow[u][v]);
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

struct BFSNode {
	int r, c, d;
	BFSNode() {}
	BFSNode(int R, int C, int D): r(R), c(C), d(D) {}
};


int n, k, m;
char maze[MAXN][MAXN + 1];
int idx[MAXN][MAXN];
int mills[MAXK];

BFSNode q[MAXN * MAXN];
bool vis[MAXN][MAXN];

const int moves[4][2] = {
	{ -1,  0 },
	{  1,  0 },
	{  0,  1 },
	{  0, -1 }
};

Graph g;


void bfs(int r, int c)
{
	int qb = 0, qf = 0;
	q[qb++] = BFSNode(r, c, 0);

	Clr(vis);
	vis[r][c] = true;

	int u = maze[r][c] - 'A' + 1;

	while (qf < qb) {
		BFSNode &cur = q[qf++];

		if (maze[cur.r][cur.c] == 'm')
			g.add_cap(u, idx[cur.r][cur.c], cur.d, 1);

		for (int i = 0; i < 4; ++i) {
			int rp = cur.r + moves[i][0];
			int cp = cur.c + moves[i][1];

			if (maze[rp][cp] == '#' || vis[rp][cp]) continue;
			q[qb++] = BFSNode(rp, cp, cur.d + 1);
			vis[rp][cp] = true;
		}
	}
}

int solve()
{
	int mcnt = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (isupper(maze[i][j]))
				idx[i][j] = maze[i][j] - 'A' + 1;
			else if(maze[i][j] == 'm')
				idx[i][j] = k + 1 + mcnt++;

	g.init_cap(k + m + 2);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (isupper(maze[i][j]))
				bfs(i, j);

	int src = 0, snk = k + m + 1;

	for (int i = 0; i < k; ++i)
		g.add_cap(src, 1 + i, 0, mills[i]);

	for (int i = 0; i < m; ++i)
		g.add_cap(k + 1 + i, snk, 0, 1);

	int cost;
	g.mincost_maxflow(src, snk, cost);
	return cost;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &n, &k, &m);
		for (int i = 0; i < n; ++i) scanf("%s", maze[i]);
		for (int i = 0; i < k; ++i) scanf("%d", &mills[i]);

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
