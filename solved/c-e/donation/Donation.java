import java.io.*;
import java.util.*;

class Donation {
    public static void main(String[] args) {
        new Donation().run();
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
        // Prim
        void primMST(int src) {
            boolean[] vis = new boolean[n];
            dis = new int[n];
            pre = new int[n];
            Arrays.fill(dis, INF);
            Arrays.fill(pre, -1);

            dis[src] = 0;
            for (int v = src; v >= 0; v = minV(vis)) {
                vis[v] = true;
                for (int i=0, ne=nEdges(v); i < ne; i++) {
                    E e = edg[v].get(i);
                    if (!vis[e.v] && e.w < dis[e.v]) {
                        dis[e.v] = e.w;
                        pre[e.v] = v;
                    }
                }
            }
        }
        int minV(boolean[] vis) {
            int d=INF, v=-1;
            for (int i=0; i<n; i++)
                if (!vis[i] && dis[i] < d) { v=i; d=dis[i]; }
            return v;
        }
    }

    int N;
    $G g;
    final int INF = 50 * 50 * 100 + 10;

    void run() {
        $R $r = new $R(System.in);
        int T = $r.nextInt();

        for (int ncase=1; ncase<=T; ncase++) {
            N = $r.nextInt();

            g = new $G(N);
            int totCost = 0;
            for (int i=0; i<N; i++)
                for (int j=0; j<N; j++) {
                    int c = $r.nextInt();
                    if (c != 0) {
                        g.add(i, j, c);
                        g.add(j, i, c);
                        totCost += c;
                    }
                }

            g.primMST(0);
            int mstCost = 0;

            for (int i = 1; i < N; i++) {
                if (g.pre[i] < 0) {
                    mstCost = -1;
                    break;
                }
                mstCost += g.dis[i];
            }

            int donation = mstCost == -1 ? -1 : totCost - mstCost;

            System.out.println("Case " + ncase + ": " + donation);
        }
    }
}
