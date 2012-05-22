import java.io.*;
import java.util.*;

/*
 * Alternative solution. It uses the Bellman Ford algorithm, but in addition
 * it also splits the graph in its strongly connected components, and tries
 * to find which SCCs are negative cycles. Then it checks for every SCC, if
 * a negative cycle SCC can be reached from it.
 */
public class InstantViewOfBigBang2 {
    public static void main(String[] args) {
        new InstantViewOfBigBang2().run();
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
        void addm(int u, int v, int w) { add(u, v, w); m++; }
        EL check(int v) { return ve[v] == null ? (ve[v]=new EL()) : ve[v]; }
        E edge(int v, int i) { return ve[v].get(i); }
        // Auxiliary types/attr
        class VL extends ArrayList<Integer> {}
        class VLL extends ArrayList<VL> {}
        class VQ extends ArrayDeque<Integer> {}
        VQ vq;
        int[] dis, glow, gidx;
        boolean[] col;
        int gcnt;
        // Helper methods
        $G subgraph(VL vl) {
            int[] idx = new int[n];
            for (int i = 0, nv=vl.size(); i < nv; i++)
                idx[vl.get(i)] = i+1;
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
        // Tarjan
        VLL _sccs;
        VLL tarjanSCC() {
            _sccs = new VLL(); vq = new VQ(); col = new boolean[n];
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
            VL scc = new VL();
            for (int u=-1; u != v;) { u=vq.pop(); col[u]=false; scc.add(u); }
            _sccs.add(scc);
        }
    }

    int N, M;
    $G g;
    boolean[] sol;  // sol[i] is true if SCC i is part of the solution
    boolean[] vis;
    int[] vscc;  // vscc[i] is the SCC of vertex i

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            M = $r.nextInt();

            g = new $G(N, M);

            for (int i = 0; i < M; i++) {
                int x = $r.nextInt();
                int y = $r.nextInt();
                int t = $r.nextInt();
                g.add(x, y, t);
            }

            $G.VLL sccs = g.tarjanSCC();
            sol = new boolean[sccs.size()];
            vscc = new int[N];

            for (int i=0, ns=sccs.size(); i < ns; i++) {
                $G.VL scc = sccs.get(i);
                for (int j=0, nv=scc.size(); j<nv; j++)
                    vscc[scc.get(j)] = i;

                $G sub = g.subgraph(scc);
                if (sub.n > 1 && sub.bellmanFordHasNegCycle())
                    sol[i] = true;
            }

            vis = new boolean[N];
            StringBuilder sb = new StringBuilder();
            sb.append("Case ");
            sb.append(ncase);
            sb.append(':');
            boolean possible = false;
            for (int i = 0; i < N; i++) {
                if (!vis[i]) dfs(i);
                if (sol[vscc[i]]) {
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

    void dfs(int v) {
        vis[v] = true;
        for (int i=0; i < g.out[v]; i++) {
            $G.E e = g.edge(v, i);
            if (!vis[e.v]) dfs(e.v);
            if (sol[vscc[e.v]]) sol[vscc[v]] = true;
        }
    }
}
