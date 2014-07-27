#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXM 100
#define MAXW 3000

#define INF 0x3f3f3f3f

#define NegN(m,n,t) memset(m, -1, sizeof(t)*(n))

const int MAX_EDGES = 2 * (2 * MAXW + MAXM + 2);
const int MAX_VERT  = 2 * MAXM + 2;


// for max-flow models -- capacity, flow (starts at zero), reverse edge
struct Edge { int v, c, f, r; };

template <typename ET>
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; NegN(adj, n, int); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	//
	// Dinitz Algorithm (Max Flow)
	//
	void add_pair(int u, int v, int c) {
		add(u, (Edge) { v, c, 0, m + 1 });
		add(v, (Edge) { u, 0, 0, m - 1 }); // { u,c,0,m-1 } for bi-directional
	}
	int src, snk;
	int ptr[MAX_VERT];
	int dist[MAX_VERT];
	int q[MAX_VERT];

	bool bfs() {
		int qb = 0, qf = 0;
		NegN(dist, n, int);
		dist[src] = 0;
		q[qb++] = src;
		while (qf < qb) {
			int u = q[qf++];
			for (int i = adj[u]; i >= 0; i = next[i]) {
				Edge &e = edges[i];
				if (e.f >= e.c || dist[e.v] >= 0) continue;
				dist[e.v] = dist[u] + 1, q[qb++] = e.v;
			}
		}
		return dist[snk] >= 0;
	}
	int dfs(int u, int fl) {
		if (u == snk) return fl;
		for (int &i = ptr[u]; i >= 0; i = next[i]) {
			Edge &e = edges[i]; int df;
			if (e.f >= e.c || dist[e.v] != dist[u] + 1) continue;
			if ((df = dfs(e.v, min(e.c - e.f, fl))) == 0) continue;
			e.f += df, edges[e.r].f -= df;
			return df;
		}
		return 0;
	}
	int max_flow(int s, int t) {
		src = s, snk = t;
		int ans = 0, df;
		while (bfs()) {
			for (int i = 0; i < n; ++i) ptr[i] = adj[i];
			while (true) {
				if ((df = dfs(src, INF)) == 0) break;
				ans += df;
			}
		}
		return ans;
	}
};


int M, W;

Graph<Edge> g;


#define In(x)  (2*(x))
#define Out(x) (2*(x)+1)


int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &M, &W);
        g.init(2 * M + 2);

		int src = 2*M, snk = 2*M+1;

        g.add_pair(src, In(0), INF);
        g.add_pair(Out(M-1), snk, INF);

        g.add_pair(In(0), Out(0), INF);
        g.add_pair(In(M-1), Out(M-1), INF);

        for (int i = 1, I = M - 1; i < I; ++i) {
            int cost;
            scanf("%d", &cost);
            g.add_pair(In(i), Out(i), cost);
        }

        while (W--) {
            int i, j, c;
            scanf("%d%d%d", &i, &j, &c);
            --i, --j;

            g.add_pair(Out(i), In(j), c);
            g.add_pair(Out(j), In(i), c);
        }

        printf("Case %d: %d\n", ++ncase, g.max_flow(src, snk));
    }

    return 0;
}
