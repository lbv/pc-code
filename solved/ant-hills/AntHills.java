import java.io.*;
import java.util.*;

public class AntHills {
    public static void main(String[] args) {
        new AntHills().run();
    }

    class $R {
        BufferedReader r;
        StringTokenizer s;
        $R(InputStream in) {
            r = new BufferedReader(new InputStreamReader(in));
            s = new StringTokenizer("");
        }
        String gets() {
            try { return r.readLine(); } catch(Exception e) { return null; } }
        String nextLine() {
            return s.hasMoreTokens() ? s.nextToken("") : gets(); }
        boolean hasNext() {
            while (!s.hasMoreTokens()) {
                String ln = gets();
                if (ln == null) return false;
                s = new StringTokenizer(ln);
            }
            return true;
        }
        String next() { return hasNext() ? s.nextToken() : null; }
        int nextInt() { return Integer.parseInt(next()); }
    }

    class $G {
        class E { int v, w; E(int V, int W) { v=V; w=W; } }
        class EL extends ArrayList<E> {}
        int n;
        EL[] edg;
        $G(int N) { n=N; edg = new EL[n]; }
        void add(int u, int v, int w) { edges(u).add(new E(v, w)); }
        EL edges(int v) {
            if (edg[v] == null) edg[v] = new EL();
            return edg[v];
        }
        int nEdges(int v) { return edg[v] == null ? 0 : edg[v].size(); }
        int[] pre, dis;
        // Biconnected components
        class VL extends ArrayList<Integer> {}
        int[] gLow, gIdx;
        boolean[] gArt;
        int gCnt;
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
    }

    int N, M;
    $G g;

    void run() {
        $R $r = new $R(System.in);
        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            M = $r.nextInt();

            g = new $G(N);
            for (int i = 0; i < M; i++) {
                int a = $r.nextInt() - 1;
                int b = $r.nextInt() - 1;

                g.add(a, b, 0);
                g.add(b, a, 0);
            }

            $G.VL ar = g.articulations();

            System.out.println("Case " + ncase + ": " + ar.size());
        }
    }
}
