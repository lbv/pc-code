#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define MAXN 25
#define MAX_PART 50

const int MAX_VERT = MAX_PART * 2 + 2;
const int MAX_EDGES = MAX_PART * MAX_PART;

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


template <typename T>
struct _Edge {
	int v; T w;
	_Edge() {}
	_Edge(int V, T W) : v(V), w(W) {}
};
typedef _Edge<int> Edge;

struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	int x, src, snk;
	void init_bipart(int X) {
		x = X;
		n = 2*x + 2, src = 0, snk = 2*x + 1, m = 0;
		Neg(adj);
	}
	int graphc[MAX_VERT][MAX_VERT];

	void add_bipart(int v1, int v2, int w) {
		int u = 1 + v1;
		int v = x + 1 + v2;
		add(u, Edge(v, w));
		graphc[u][v] = w;
	}

	struct DNode {
		int v, u, c;
		DNode() {}
		DNode(int V, int U, int C): v(V), u(U), c(C) {}
		bool operator<(const DNode &n) const { return c > n.c; }
	};
	int match[MAX_VERT];
	int from[MAX_VERT];
	bool vis[MAX_VERT];

	bool find_path(int src, int &cost) {
		Clr(vis);
		Neg(from);
		priority_queue<DNode> pq;
		pq.push(DNode(src, -1, 0));

		while (! pq.empty()) {
			DNode cur = pq.top(); pq.pop();
			if (vis[cur.v]) continue;
			vis[cur.v] = true;
			from[cur.v] = cur.u;
			if (cur.v <= x)
				for (int i = adj[cur.v]; i >= 0; i = next[i]) {
					Edge &e = edges[i];
					if (match[cur.v] == e.v) continue;
					pq.push(DNode(e.v, cur.v, max(cur.c, e.w)));
				}
			else {
				if (match[cur.v] < 0) {
					from[snk] = cur.v;
					cost = max(cost, cur.c);
					break;
				}
				int vp = match[cur.v];
				int cp = max(cur.c, graphc[vp][cur.v]);
				pq.push(DNode(vp, cur.v, cp));
			}
		}

		int v = from[snk];
		if (v < 0) return false;

		while (from[v] >= 0) {
			int u = from[v];
			if (v > x) {
				match[u] = v;
				match[v] = u;
			}
			v = u;
		}
		return true;
	}
	bool mincost_match(int &cost) {
		cost = 0;
		Neg(match);

		for (int src = 1; src <= x; ++src)
			if (! find_path(src, cost)) return false;

		return true;
	}
};

struct MazeNode {
	int r, c;  // row, column
	int d;     // distance from source

	MazeNode() {}
	MazeNode(int R, int C, int D): r(R), c(C), d(D) {}
};


char maze[MAXN][MAXN + 1];
int  idx[MAXN][MAXN];
bool vis[MAXN][MAXN];
MazeNode q[MAXN*MAXN];

int n;
int ng, nh;  // number of ghosts, humans

const int moves[4][2] = {
	{ -1,  0 },
	{  0,  1 },
	{  1,  0 },
	{  0, -1 }
};


Graph g;


bool is_valid(int r, int c)
{
	return 0 <= r && r < n && 0 <= c && c < n;
}

void bfs(int r, int c)
{
	Clr(vis);
	int qb = 0, qf = 0, u = idx[r][c];
	q[qb++] = MazeNode(r, c, 0);
	vis[r][c] = true;

	while (qf < qb) {
		MazeNode &nd = q[qf++];
		if (maze[nd.r][nd.c] == 'H')
			g.add_bipart(u, idx[nd.r][nd.c], 2*nd.d + 2);

		for (int i = 0; i < 4; ++i) {
			int rp = nd.r + moves[i][0];
			int cp = nd.c + moves[i][1];

			if ((! is_valid(rp, cp)) || vis[rp][cp] ||
				maze[rp][cp] == '#') continue;

			q[qb++] = MazeNode(rp, cp, nd.d + 1);
			vis[rp][cp] = true;
		}
	}
}

void build_graph()
{
	ng = nh = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (maze[i][j] == 'H')
				idx[i][j] = nh++;
			else if (maze[i][j] == 'G')
				idx[i][j] = ng++;

	g.init_bipart(ng);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (maze[i][j] == 'G')
				bfs(i, j);

	int excess = ng - nh;
	if (excess == 0) return;

	for (int i = 0; i < ng; ++i)
		for (int j = 0; j < excess; ++j)
			g.add_bipart(i, nh + j, 0);
}

int solve()
{
	build_graph();

	int cost;
	if (g.mincost_match(cost)) return cost;

	return -1;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%s", maze[i]);

		printf("Case %d: ", ++ncase);
		int ans = solve();
		if (ans < 0)
			puts("Vuter Dol Kupokat");
		else
			printf("%d\n", ans);
	}

	return 0;
}
