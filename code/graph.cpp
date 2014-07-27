//
// Union-Find disjoint set
//
struct Set {
	int s[MAXN];
	Set() {}
	void init(int n) { for (int i=0; i < n; ++i) s[i] = i; }
	int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
	void merge(int i, int j) { s[find(i)] = find(j); }
};

struct Edge { int v; };
struct Edge { int v; GraphT w; };
struct Edge {
	int u, v; GraphT w;

	bool operator<(const Edge &e) const { return w < e.w; }
};

// for max-flow models -- capacity, flow (starts at zero), reverse edge
struct Edge { int v, c, f, r; };
// for min-cost bipartite matching
struct Edge { int u, v, w, r; };

const int MAX_VERT = MAXN;
const int MAX_EDGES = MAXM;
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;

	void init(int N) { n = N, m = 0; NegN(adj, n, int); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
	void add_dir(int u, int i) { next[i]=adj[u], adj[u]=i; }
	void add_und(const Edge &e) { edges[m++] = e; }


	//
	// Kruskal
	//
	Set uf;
	void kruskal_mst(int &ans) {
		sort(edges, edges + m);
		uf.init(n);
		int nedges = 0;
		ans = 0;
		for (int i = 0; i < m; ++i) {
			Edge &e = edges[i];
			if (uf.find(e.u) == uf.find(e.v)) continue;
			uf.merge(e.u, e.v);
			ans += e.w;
			if (++nedges == n - 1) break;
		}
	}


	//
	// Dijkstra's Single Source Shortest Paths
	//
	struct Node {
		GraphT d;
		int v;
		Node() {}
		Node(GraphT D, int V): d(D), v(V) {}

		bool operator<(const Node &n) const { return d > n.d; }
	};
	GraphT dis[MAX_VERT];
	bool vis[MAX_VERT];

	void dijkstra(int src) {
		Inf(dis); Clr(vis);
		priority_queue<Node> q;
		q.push(Node(0, src));
		dis[src] = 0;
		while (! q.empty()) {
			Node cur = q.top(); q.pop();
			if (vis[cur.v]) continue;
			vis[cur.v] = true;

			for (int i = adj[cur.v]; i >= 0; i = next[i]) {
				Edge &e = edges[i];
				GraphT d2 = cur.d + e.w;
				if (d2 >= dis[e.v]) continue;
				dis[e.v] = d2;
				q.push(Node(d2, e.v));
			}
		}
	}


	//
	// Bellman-Ford to detect negative cycles
	//
	GraphT dis[MAX_VERT];
	bool bellman_ford() {
		Clr(dis);
		for (int i = 1; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				Edge &e = edges[j];
				if(dis[e.u] + e.w < dis[e.v])
					dis[e.v] = dis[e.u] + e.w;
			}
		for (int j = 0; j < m; ++j) {
			Edge &e = edges[j];
			if (dis[e.u] + e.w < dis[e.v])
				return true;
		}
		return false;
	}


	//
	// Strongly Connected Components
	//
	int nscc, nm;
	int scc[MAX_VERT];
	int scc_head[MAX_VERT];
	int scc_next[MAX_VERT];
	// int scc_size[MAX_VERT];
	void init_scc() { nscc = nm = 0; NegN(scc_head, n, int); }
	/* Clr(scc_size); */
	void add_scc_element(int v) {
		scc_next[nm] = scc_head[nscc];
		scc_head[nscc] = nm;
		scc[nm++] = v;
		// ++scc_size[nscc];
	}

	int vcomp[MAX_VERT];
	void scc_to_dag(Graph &dag) {
		for (int i = 0; i < nscc; ++i)
			for (int j = scc_head[i]; j >= 0; j = scc_next[j])
				vcomp[scc[j]] = i;
		dag.init(nscc);
		for (int u = 0; u < n; u++)
			for (int i = adj[u]; i >= 0; i = next[i]) {
				int v = edges[i].v;
				if (vcomp[u] != vcomp[v])
					dag.add(vcomp[u], Edge(vcomp[v]));
			}
	}

	//
	// Kosaraju's SCC algorithm
	//
	int stk[MAX_VERT];
	int stk_top;
	bool vis[MAX_VERT];

	Edge redges[MAX_EDGES];
	int rnext[MAX_EDGES];
	int radj[MAX_VERT];
	int rm;
	void radd(int u, const Edge &e) {
		rnext[rm]=radj[u], radj[u]=rm, redges[rm++]=e; }
	void dfs(int v) {
		vis[v] = true;
		for (int i = adj[v]; i >= 0; i = next[i]) {
			int u = edges[i].v;
			radd(u, (Edge) { v });
			if (! vis[u]) dfs(u);
		}
		stk[stk_top++] = v;
	}
	void dfs2(int v) {
		vis[v] = true;
		add_scc_element(v);
		for (int i = radj[v]; i >= 0; i = rnext[i]) {
			int ev = redges[i].v;
			if (! vis[ev]) dfs2(ev);
		}
	}
	void kosaraju() {
		rm = stk_top = 0;
		init_scc();
		NegN(radj, n, int);
		ClrN(vis, n, bool);
		for (int v = 0; v < n; ++v) if (! vis[v]) dfs(v);
		ClrN(vis, n, bool);
		while (stk_top > 0) {
			int v = stk[--stk_top];
			if (! vis[v]) { dfs2(v); ++nscc; }
		}
	}

	//
	// Tarjan for Strongly Connected Components
	//
	bool flg[MAX_VERT];
	int low[MAX_VERT];
	int idx[MAX_VERT];
	int stk[MAX_VERT];
	int s_top;
	int cnt;

	void visit(int v) {
		idx[v] = low[v] = cnt++;
		stk[s_top++] = v;
		flg[v] = true;
		for (int i = adj[v]; i >= 0; i = next[i]) {
			int vp = edges[i].v;
			if (low[vp] == 0) {
				visit(vp);
				low[v] = min(low[v], low[vp]);
			}
			else if (flg[vp])
				low[v] = min(low[v], idx[vp]);
		}
		if (low[v] != idx[v]) return;
		for (int u = -1; u != v;) {
			u = stk[--s_top];
			flg[u] = false;
			add_scc_element(u);
		}
		++nscc;
	}
	void tarjan_scc() {
		cnt = 1, s_top = 0;
		init_scc(); Clr(flg); Clr(low);
		for (int i = 0; i < n; ++i) if (low[i] == 0) visit(i);
	}


	//
	// Ford-Fulkerson Max Flow
	//
	void add_pair(int u, int v, int c) {
		add(u, Edge(v, c, m + 1));
		add(v, Edge(u, 0, m - 1));
	}
	int dist[MAX_VERT], q[MAX_VERT], src, snk;
	bool find_aug_paths() {
		Neg(dist);
		int qf = 0, qb = 0;
		q[qb++] = src;
		dist[src] = 0;
		while (qf < qb) {
			int u = q[qf++];
			if (u == snk) return true;
			for (int i = adj[u]; i >= 0; i = next[i]) {
				Edge &e = edges[i];
				if (dist[e.v] >= 0 || e.f >= e.c) continue;
				q[qb++] = e.v;
				dist[e.v] = dist[u] + 1;
			}
		}
		return false;
	}
	int dfs(int u, int f, int d) {
		if (u == snk) return f;
		int ans = 0;
		for (int i = adj[u]; f > 0 && i >= 0; i = next[i]) {
			Edge &e = edges[i];
			if (e.f >= e.c || dist[e.v] != d + 1) continue;
			int r = dfs(e.v, min(f, e.c - e.f), d + 1);
			if (r > 0) e.f += r, edges[e.r].f -= r, ans += r, f -= r;
		}
		return ans;
	}
	int mod_paths() {
		int ans = 0;
		for (int f = dfs(src, INF, 0); f > 0; f = dfs(src, INF, 0))
			ans += f;
		return ans;
	}
	int max_flow(int a, int b) {
		src = a, snk = b;
		int total = 0;
		while (find_aug_paths()) total += mod_paths();
		return total;
	}
	void clear_flows() { for (int i = 0; i < m; ++i) edges[i].f = 0; }


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


	/////////////////////////////////////////////
	////////// Bi-Partite Graphs ////////////////
	/////////////////////////////////////////////
	int x, src, snk;
	void init_bipart_basic(int X) {
		x = X, n = 2*x + 2, src = 0, snk = 2*x + 1, m = 0;
		NegN(adj, n, int);
	}


	//
	// Hopcroft-Karp for bipartite matching.
	//
	void add_bipart(int v1, int v2) {
		int u = 1 + v1;
		int v = x + 1 + v2;
		add(u, (Edge) { v });
	}

	int match[MAX_VERT];
	int dist[MAX_VERT];
	int q[MAX_VERT];

	bool bfs() {
		int qf = 0, qb = 0;
		for (int i = 1; i <= x; ++i)
			if (match[i] == 0)
				dist[i] = 0, q[qb++] = i;
			else
				dist[i] = INF;
		dist[0] = INF;
		while (qf < qb) {
			int v = q[qf++];
			for (int i = adj[v]; i >= 0; i = next[i]) {
				Edge &e = edges[i];
				int p = match[e.v];
				if (dist[p] != INF) continue;
				dist[p] = dist[v] + 1;
				q[qb++] = p;
			}
		}
		return dist[0] != INF;
	}
	bool dfs(int u) {
		if (u == 0) return true;
		for (int i = adj[u]; i >= 0; i = next[i]) {
			Edge &e = edges[i];
			int p = match[e.v];
			if (dist[p] == dist[u] + 1 && dfs(p)) {
				match[e.v] = u;
				match[u] = e.v;
				return true;
			}
		}
		dist[u] = INF;
		return false;
	}
	int max_matching() {
		int m = 0;
		ClrN(match, n, int);
		while (bfs())
			for (int i = 1; i <= x; ++i) if (match[i] == 0 && dfs(i)) ++m;
		return m;
	}


	//
	// Min-cost matching. Total cost is the cost of the heaviest edge.
	// Doesnt need to connect source and sink to X and Y.
	//
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


	// --------------------------------------------

	int prim_mst(int src) {
		IIS q;
		IV dis(n, INF);
		BV flg(n);
		dis[src] = 0;
		q.insert(II(0, src));
		int mst = 0;
		while (! q.empty()) {
			int d = q.begin()->first;
			int v = q.begin()->second;
			q.erase(q.begin());
			if (flg[v]) continue;
			flg[v] = true;
			mst += d;
			For (EL, e, adj[v])
				if (!flg[e->v] && e->w < dis[e->v]) {
					dis[e->v] = e->w;
					q.insert(II(dis[e->v], e->v));
				}
		}
		return mst;
	}
	void topo_sort(IV &in, IV &order) {
		IQ q;
		for (int i = 0; i < n; ++i) if (in[i] == 0) q.push(i);
		order.clear();
		while (! q.empty()) {
			int v = q.front(); q.pop();
			order.push_back(v);
			For (EL, e, adj[v])
				if (--in[e->v] == 0) q.push(e->v);
		}
	}


	// Articulations/bridges
	int low[MAX_V], idx[MAX_V], cnt;
	bool is_artic[MAX_V];
	bool is_bridge[MAX_E];

	void dfs(int u, int v) {
		int children = 0;
		low[v] = idx[v] = cnt++;
		for (int i = adj[v]; i >= 0; i = next[i]) {
			Edge &e = edges[i];
			if (idx[e.v] == 0) {
				++children;
				dfs(v, e.v);
				low[v] = min(low[v], low[e.v]);
				if (low[e.v] >= idx[v] && u != v)
					is_artic[v] = true;
				if (low[e.v] == idx[e.v])
					is_bridge[i] = is_bridge[e.o] = true;
			}
			else if (e.v != u)
				low[v] = min(low[v], idx[e.v]);
		}
		if (u == v && children > 1)
			is_artic[v] = true;
	}
	void articulations() {
		Zero(idx); Zero(low);
		Zero(is_artic); Zero(is_bridge);
		cnt = 1;
		for (int i = 0; i < n; ++i) if (idx[i] == 0) dfs(i, i);
	}

	// Eulerian Trail
	struct Euler {
		ELV adj; IV t;
		Euler(ELV Adj) : adj(Adj) {}
		void build(int u) {
			while(! adj[u].empty()) {
				int v = adj[u].front().v;
				adj[u].erase(adj[u].begin());
				build(v);
			}
			t.push_back(u);
		}
	};
	bool eulerian_trail(IV &trail) {
		Euler e(adj);
		int odd = 0, s = 0;
		/*
		for (int v = 0; v < n; v++) {
			int diff = abs(in[v] - out[v]);
			if (diff > 1) return false;
			if (diff == 1) {
				if (++odd > 2) return false;
				if (out[v] > in[v]) start = v;
			}
		}
		*/
		e.build(s);
		reverse(e.t.begin(), e.t.end());
		trail = e.t;
		return true;
	}
};


//
// Floyd-Warshall Shortest Paths
//
void floyd_warshall()
{
	for (int k = 0; k < N; ++k)
		for(int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j) {
				if (g[i][k] == INF || g[k][j] == INF) continue;
				int t = g[i][k] + g[k][j];
				if (t < g[i][j]) g[i][j] = t;
			}
}


//
// 2-SAT
//
struct TwoSat {
	Graph g;
	int n;
	int sol[MAX_VERT];
	int nsol;
	int vscc[MAX_VERT];

	void init(int N) { n = N, g.init(2*n); }
	void add_cons(int a, bool ta, int b, bool tb) {
		int p = val(a, ta), q = val(b, tb);
		g.add(neg(p), Edge(q)); g.add(neg(q), Edge(p));
	}
	int val(int v, bool t) { return 2*v + (t ? 0 : 1); }
	int neg(int p) { return p ^ 1; }
	bool solve() {
		g.kosaraju();
		Clr(vscc);
		nsol = 0;
		for (int i = 0; i < g.nscc; ++i)
			for (int j = g.scc_head[i]; j >= 0; j = g.scc_next[j]) {
				int p = g.scc[j], v = p/2;
				if (vscc[v] == i+1) return false;
				if (vscc[v] != 0) break;
				vscc[v] = i+1;
				if (p & 1) sol[nsol++] = v;
			}
		return true;
	}
};
