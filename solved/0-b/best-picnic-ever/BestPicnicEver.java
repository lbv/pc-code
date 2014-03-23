import java.io.*;
import java.util.*;

public class BestPicnicEver {
    public static void main(String[] args) {
        new BestPicnicEver().run();
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
    }

    int K, N, M;
    int[] people;  // cities where people live
    $G g;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            K = $r.nextInt();
            N = $r.nextInt();
            M = $r.nextInt();

            people = new int[K];
            for (int i = 0; i < K; i++)
                people[i] = $r.nextInt() - 1;

            g = new $G(N, M);

            for (int i = 0; i < M; i++) {
                int u = $r.nextInt() - 1;
                int v = $r.nextInt() - 1;
                g.add(u, v, 0);
            }

            solve();

            $w.println("Case " + ncase + ": " + reachable);
        }

        $w.close();
    }

    boolean[] col;
    int[] reached;  // number of people that can reach each city
    int reachable;  // global answer

    void solve() {
        reachable = 0;
        reached = new int[N];
        for (int i = 0; i < K - 1; i++) {
            col = new boolean[N];
            dfs(people[i]);
        }

        col = new boolean[N];
        dfsLast(people[K-1]);
    }

    void dfs(int v) {
        col[v] = true;
        reached[v]++;
        for (int i = 0; i < g.out[v]; i++) {
            $G.E e = g.edge(v, i);
            if (!col[e.v]) dfs(e.v);
        }
    }

    void dfsLast(int v) {
        col[v] = true;
        reached[v]++;
        if (reached[v] == K) reachable++;
        for (int i = 0; i < g.out[v]; i++) {
            $G.E e = g.edge(v, i);
            if (!col[e.v]) dfsLast(e.v);
        }
    }
}
