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
    }
}
