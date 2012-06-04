import java.io.*;
import java.util.*;

public class Brush {
    public static void main(String[] args) {
        new Brush().run();
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
        int[][] m;
        int[] dist, pred;
        boolean[] vis;
        int n, inf;
        $G(int N, int Inf) {
            n=N; inf=Inf; m = new int[n][n];
            for (int i = 0; i < n; i++) Arrays.fill(m[i], -1);
        }
        void dijkstra(int src) {
            dist = new int[n];
            pred = new int[n];
            vis = new boolean[n];
            Arrays.fill(dist, inf);
            dist[src] = 0;
            for (int nxt = minV(); nxt >= 0; nxt = minV()) {
                vis[nxt] = true;
                for (int v=0; v<n; v++) {
                    if(m[nxt][v] < 0) continue;
                    int d = dist[nxt] + m[nxt][v];
                    if (d < dist[v]) {
                        dist[v] = d;
                        pred[v] = nxt;
                    }
                }
            }
        }
        int minV() {
            int x=inf, y=-1;
            for (int i=0; i<n; i++)
                if (!vis[i] && dist[i] < x) { y=i; x=dist[i]; }
            return y;
        }
    }

    int N, M;
    $G g;
    final int INF = 1000 * 100 + 10;
    void run() {
        $R $r = new $R(System.in);

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            M = $r.nextInt();

            $G g = new $G(N, INF);

            for (int i = 0; i < M; i++) {
                int u = $r.nextInt();
                int v = $r.nextInt();
                int w = $r.nextInt();
                if (g.m[u-1][v-1] < 0 || w < g.m[u-1][v-1]) {
                    g.m[u-1][v-1] = w;
                    g.m[v-1][u-1] = w;
                }
            }

            g.dijkstra(0);

            System.out.println("Case " + ncase + ": " +
                               (g.dist[N-1] < INF ? g.dist[N-1] : "Impossible"));
        }
    }
}
