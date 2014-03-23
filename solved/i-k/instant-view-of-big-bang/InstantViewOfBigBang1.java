import java.io.*;
import java.util.*;

/*
 * Simple solution that uses just the Bellman Ford algorithm. The idea is
 * that using a reverse graph, every vertex that is reported by Bellman Ford
 * is part of the solution, as well as any vertex reachable from it.
 */
public class InstantViewOfBigBang1 {
    public static void main(String[] args) {
        new InstantViewOfBigBang1().run();
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
            while (b == 10 || b == 13) read();
            return sb.toString(); }
        int nextInt() {
            int ival = 0; boolean isgn = false;
            skip(); if (b == '-') { isgn = true; read(); }
            for (; b > 32; read()) ival = ival*10 + b-48;
            return isgn ? -ival : ival; }
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
        EL ae; EL[] ve; int[] out; int n, m;
        $G(int N) { n=N; init(); } $G(int N, int M) { n=N; m=M; init(); }
        void init() {
            ae = m==0 ? new EL() : new EL(m);
            ve = new EL[n]; out = new int[n]; }
        void add(int u, int v, int w) {
            E e = new E(u, v, w); ae.add(e); check(u).add(e); out[u]++; }
        EL check(int v) { return ve[v] == null ? (ve[v]=new EL()) : ve[v]; }
        E edge(int v, int i) { return ve[v].get(i); }
        EL edges(int v) { return ve[v]; }
        // Auxiliary types/attrs
        int[] dis;
        boolean[] col;
        // Bellman Ford
        // Variation of the Bellman Ford algorithm, it doesn't start at any
        // vertex in particular, and is only concerned with finding negative
        // cycles, and the vertices that can be reached from them
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
    }

    int N, M;
    $G rg;  // reverse graph

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            M = $r.nextInt();

            rg = new $G(N, M);

            for (int i = 0; i < M; i++) {
                int x = $r.nextInt();
                int y = $r.nextInt();
                int t = $r.nextInt();
                rg.add(y, x, t);
            }

            rg.bellmanFordVertices();

            StringBuilder sb = new StringBuilder();
            sb.append("Case ");
            sb.append(ncase);
            sb.append(':');

            boolean possible = false;
            for (int i = 0; i < N; i++) {
                if (rg.col[i]) {
                    sb.append(' ');
                    sb.append(i);
                    possible = true;
                }
            }

            if (! possible)
                sb.append(" impossible");
            $w.println(sb.toString());
        }
        $w.close();
    }
}
