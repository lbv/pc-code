import java.io.*;
import java.util.*;

public class CountryRoads {
    public static void main(String[] args) {
        new CountryRoads().run();
    }

    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        boolean hasNext() { skip(); return b >= 0; }
        void skip() { while (b >= 0 && b <= 32) read(); }
        String next() {
            StringBuilder sb = new StringBuilder();
            for (skip(); b > 32; read()) sb.append((char)b);
            return sb.length() == 0 ? null : sb.toString(); }
        String nextLine() {
            StringBuilder sb = new StringBuilder();
            for (; b != 10 && b != 13; read()) sb.append((char)b);
            while (b == 10 || b == 13) read(); return sb.toString(); }
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
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
        // Auxiliary types/attr
        boolean[] col; int[] dis, glow, gidx; int gcnt;
        // Dijkstra's algorithm
        // Modified according to the problem, so the cost of a path is the
        // cost of the maximum road visited
        void dijkstraSSSP(int src) {
            dis = new int[n];
            col = new boolean[n];
            Arrays.fill(dis, INF);
            dis[src] = 0;
            for (int nxt = _minV(); nxt >= 0; nxt = _minV()) {
                col[nxt] = true;
                for (int i=0; i < out[nxt]; i++) {
                    E e = edge(nxt, i);
                    int d = Math.max(dis[nxt], e.w);
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

    $G g;
    int N, M;

    final int INF = 20000 * 16000 + 100;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            M = $r.nextInt();

            g = new $G(N, M);
            for (int i=0; i < M; i++) {
                int u = $r.nextInt();
                int v = $r.nextInt();
                int w = $r.nextInt();

                g.add(u, v, w);
                g.add(v, u, w);
            }

            int t = $r.nextInt();

            g.dijkstraSSSP(t);

            $w.println("Case " + ncase + ":");
            for (int i = 0; i < N; i++) {
                if (g.dis[i] >= INF)
                    $w.println("Impossible");
                else
                    $w.println(g.dis[i]);
            }
        }

        $w.close();
    }
}
