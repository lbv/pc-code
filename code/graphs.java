public class TestGraphs {
    class IL extends ArrayList<Integer> {};
    class ILL extends ArrayList<IL> {};
    class IQ extends ArrayDeque<Integer> {};
    class $G {
        class E { int u, v, w; E(int U, int V, int W) { u=U; v=V; w=W; } }
        class EL extends ArrayList<E> { EL(){super();} EL(int c){super(c);} }
        EL ae; EL[] ve; int[] in, out; int n, m;
        $G(int N) { n=N; init(); } $G(int N, int M) { n=N; m=M; init(); }
        void init() {
            ae = m==0 ? new EL() : new EL(m);
            ve = new EL[n]; out = new int[n]; in = new int[n]; }
        void add(int u, int v, int w) {
            E e = new E(u, v, w);
            ae.add(e); check(u).add(e); out[u]++; in[v]++; }
        void addm(int u, int v, int w) { add(u, v, w); m++; }
        EL check(int v) { return ve[v] == null ? (ve[v]=new EL()) : ve[v]; }
        E edge(int v, int i) { return ve[v].get(i); }
        // Auxiliary types/attr
        class EQ extends ArrayDeque<E> {}
        IQ vq; boolean[] col; int[] dis, glow, gidx; int gcnt;
        // Helper methods
        $G subgraph(IL vl) {
            int[] idx = new int[n];
            for (int i = 0, nv=vl.size(); i < nv; i++) idx[vl.get(i)] = i+1;
            $G sub = new $G(vl.size());
            for (int i = 0, nv=vl.size(); i < nv; i++) {
                int v = vl.get(i);
                for (int j=0; j < out[v]; j++) {
                    E e = edge(v, j);
                    if (idx[e.v] != 0)
                        sub.addm(idx[e.u]-1, idx[e.v]-1, e.w);
                }
            }
            return sub;
        }
        // Topological sort
        IL topoSort() {
            int[] tin = (int[]) in.clone();
            IQ q = new IQ();
            for (int i = 0; i < n; i++) if (tin[i] == 0) q.add(i);
            IL res = new IL();
            while(! q.isEmpty()) {
                int v = q.remove(); res.add(v);
                for (int i = 0; i < out[v]; i++) {
                    E e = edge(v, i);
                    tin[e.v]--;
                    if (tin[e.v] == 0) q.add(e.v);
                }
            }
            return res;
        }
        // Kosaraju's algorithm
        $G _rg; IL _scc;
        ILL kosarajuSSC() {
            col = new boolean[n]; vq = new IQ(); _rg = new $G(n);
            for (int v=0; v<n; v++) if (!col[v]) kosarajuDFS(v);
            Arrays.fill(col, false);
            ILL sccs = new ILL();
            while (!vq.isEmpty()) {
                int v = vq.pop();
                if (col[v]) continue;
                _scc = new IL();
                kosarajuDFS2(v);
                sccs.add(_scc);
            }
            return sccs;
        }
        void kosarajuDFS(int v) {
            col[v] = true;
            for (int i=0; i<out[v]; i++) {
                E e = edge(v, i);
                _rg.add(e.v, e.u, e.w);
                if (!col[e.v]) kosarajuDFS(e.v);
            }
            vq.push(v);
        }
        void kosarajuDFS2(int v) {
            col[v] = true;
            _scc.add(v);
            for (int i=0; i<_rg.out[v]; i++) {
                E e = _rg.edge(v, i);
                if (!col[e.v]) kosarajuDFS2(e.v);
            }
        }
        // Tarjan
        ILL _sccs;
        ILL tarjanSCC() {
            _sccs = new ILL(); vq = new IQ(); col = new boolean[n];
            glow = new int[n]; gidx = new int[n]; gcnt = 1;
            for (int i = 0; i<n; i++)
                if (glow[i] == 0) tarjanVisit(i);
            return _sccs;
        }
        void tarjanVisit(int v) {
            gidx[v] = glow[v] = gcnt++;
            vq.push(v); col[v] = true;
            for (int i=0; i < out[v]; i++) {
                E e = edge(v, i);
                if (glow[e.v] == 0) {
                    tarjanVisit(e.v);
                    glow[v] = Math.min(glow[v], glow[e.v]);
                }
                else if (col[e.v])
                    glow[v] = Math.min(glow[v], gidx[e.v]);
            }
            if (glow[v] != gidx[v]) return;
            IL scc = new IL();
            for (int u=-1; u != v;) { u=vq.pop(); col[u]=false; scc.add(u); }
            _sccs.add(scc);
        }
        // SCC to DAG
        $G sccDag(ILL sccs) {
            int ndag = sccs.size();
            int[] vcomp = new int[n];
            for (int i=0; i<ndag; i++) {
                IL scc = sccs.get(i);
                for (int j=0, lim=scc.size(); j<lim; j++) {
                    int v = scc.get(j);
                    vcomp[v] = i;
                }
            }
            $G dag = new $G(ndag);
            for (int u=0; u < n; u++)
                for (int i=0; i < out[u]; i++) {
                    E e = edge(u, i);
                    if (vcomp[u] != vcomp[e.v])
                        dag.addm(vcomp[u], vcomp[e.v], 0);
                }
            return dag;
        }
        // Bellman Ford
        boolean bellmanFordHasNegCycle() {
            dis = new int[n];
            for (int i = 0; i < n-1; i++)
                for (int j = 0; j < m; j++) {
                    E e = ae.get(j);
                    if(dis[e.u] + e.w < dis[e.v])
                        dis[e.v] = dis[e.u] + e.w;
                }
            for (int j=0; j < m; j++) {
                E e = ae.get(j);
                if (dis[e.u] + e.w < dis[e.v])
                    return true;
            }
            return false;
        }
        void bellmanFordVertices() {
            dis = new int[n];
            for (int i = 0; i < n-1; i++)
                for (int j = 0; j < m; j++) {
                    E e = ae.get(j);
                    if(dis[e.u] + e.w < dis[e.v])
                        dis[e.v] = dis[e.u] + e.w;
                }
            col = new boolean[n];
            for (int i = 0; i < m; i++) {
                E e = ae.get(i);
                if (!col[e.u] && dis[e.u] + e.w < dis[e.v])
                    bellmanFordDFS(e.u);
            }
        }
        void bellmanFordDFS(int v) {
            col[v] = true;
            for (int i=0; i < out[v]; i++) {
                E e = edge(v, i);
                if (!col[e.v]) bellmanFordDFS(e.v);
            }
        }
        // Euler trails
        IL _trail; EQ[] _adjq;
        IL eulerTrail() {
            _adjq = new EQ[n];
            int nOdd = 0, start = 0;
            for (int u = 0; u < n; u++) {
                _adjq[u] = new EQ();
                if (start == 0 && out[u] > 0) start = u;
                for (int i = 0; i < out[u]; i++)
                    _adjq[u].add(edge(u, i));
            }
            for (int v = 0; v < n; v++) {
                int diff = Math.abs(in[v] - out[v]);
                if (diff > 1) return null;
                if (diff == 1) {
                    if (++nOdd > 2) return null;
                    if (out[v] > in[v]) start = v;
                }
            }
            _trail = new IL();
            eulerBuildTrail(start);
            Collections.reverse(_trail);
            return _trail;
        }
        void eulerBuildTrail(int u) {
            while(! _adjq[u].isEmpty()) {
                E e = _adjq[u].remove();
                eulerBuildTrail(e.v);
            }
            _trail.add(u);
        }
        // Dijkstra's algorithm
        void dijkstraSSSP(int src) {
            dis = new int[n];
            col = new boolean[n];
            Arrays.fill(dis, INF);
            dis[src] = 0;
            for (int nxt = _minV(); nxt >= 0; nxt = _minV()) {
                col[nxt] = true;
                for (int i=0; i < out[nxt]; i++) {
                    E e = edge(nxt, i);
                    int d = dis[nxt] + e.w;
                    if (d < dis[e.v]) dis[e.v] = d;
                }
            }
        }
        int _minV() {
            int x=INF, y=-1;
            for (int i=0; i<n; i++)
                if (!col[i] && dis[i] < x) { y=i; x=dis[i]; }
            return y;
        }
    }



        //
        // OLD CODE
        //
        // Biconnected components
        boolean[] gArt;
        VL articulations() {
            gLow = new int[n];
            gIdx = new int[n];
            gArt = new boolean[n];
            gCnt = 1;
            for (int i=0; i < n; i++)
                if (gIdx[i] == 0) articDFS(i, i);
            VL art = new VL();
            for (int i=0; i < n; i++)
                if (gArt[i]) art.add(i);
            return art;
        }
        void articDFS(int u, int v) {
            int children = 0;
            gLow[v] = gIdx[v] = gCnt++;
            for (int i=0, ne=nEdges(v); i<ne; i++) {
                E e = edg[v].get(i);
                if (gIdx[e.v] == 0) {
                    children++;
                    articDFS(v, e.v);
                    gLow[v] = Math.min(gLow[v], gLow[e.v]);
                    if (gLow[e.v] >= gIdx[v] && u != v)
                        gArt[v] = true;
                }
                else if (e.v != u)
                    gLow[v] = Math.min(gLow[v], gIdx[e.v]);
            }
            if (u == v && children > 1)
                gArt[v] = true;
        }
        int minV(boolean[] vis) {
            int d=INF, v=-1;
            for (int i=0; i<n; i++)
                if (!vis[i] && dis[i] < d) { v=i; d=dis[i]; }
            return v;
        }
    }
}
