import java.io.*;
import java.util.*;

public class HitTheLightSwitches {
    public static void main(String[] args) {
        new HitTheLightSwitches().run();
    }

    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        void skip() { while (b >= 0 && b <= 32) read(); }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }
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
        IQ vq; boolean[] col; int[] dis, glow, gidx; int gcnt;
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
    }

    $G g;
    int N, M;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            M = $r.nextInt();

            g = new $G(N, M);

            while (M-- > 0) {
                int u = $r.nextInt() - 1;
                int v = $r.nextInt() - 1;
                g.add(u, v, 0);
            }

            ILL sccs = g.kosarajuSSC();

            col = new boolean[N];
            int switches = 0;
            for (int i = 0, n = sccs.size(); i < n; i++) {
                int v = sccs.get(i).get(0);

                if (!col[v]) {
                    dfs(v);
                    switches++;
                }
            }

            $w.println("Case " + ncase + ": " + switches);
        }

        $w.close();
    }

    boolean[] col;
    void dfs(int v) {
        col[v] = true;

        for (int i = 0; i < g.out[v]; i++) {
            $G.E e = g.edge(v, i);
            if (!col[e.v]) dfs(e.v);
        }
    }
}
