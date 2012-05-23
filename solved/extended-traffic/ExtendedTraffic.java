import java.io.*;
import java.util.*;

public class ExtendedTraffic {
    public static void main(String[] args) {
        new ExtendedTraffic().run();
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
        // Bellman Ford
        class E2 {
            int u, v, w;
            E2(int U, int V, int W) { u=U; v=V; w=W; }
        }
        class E2L extends ArrayList<E2> {}
        E2L allEdges() {
            E2L edges = new E2L();
            for (int u = 0; u < n; u++)
                for(int i=0, lim=nEdges(u); i < lim; i++) {
                    E e = edg[u].get(i);
                    edges.add(new E2(u, e.v, e.w));
                }
            return edges;
        }
        boolean[] bellmanFordVertices(int src) {
            final E2L edges = allEdges();
            int nEdges = edges.size();
            dis = new int[n];
            Arrays.fill(dis, INF);
            dis[src] = 0;
            for (int i = 0; i < n-1; i++)
                for (int j=0; j < nEdges; j++) {
                    E2 e = edges.get(j);
                    if(dis[e.u] < INF && dis[e.u] + e.w < dis[e.v])
                        dis[e.v] = dis[e.u] + e.w;
                }
            boolean[] vis = new boolean[n];
            for (int i=0; i < nEdges; i++) {
                E2 e = edges.get(i);
                if (dis[e.u] < INF && dis[e.u] + e.w < dis[e.v] && !vis[e.u])
                    bellmanFordDFS(e.u, vis);
            }
            return vis;
        }
        void bellmanFordDFS(int v, boolean[] vis) {
            vis[v] = true;
            for (int i=0, ne=nEdges(v); i<ne; i++) {
                E e = edg[v].get(i);
                if (!vis[e.v]) bellmanFordDFS(e.v, vis);
            }
        }
    }

    int N, M, Q;
    int[] bus;  // busyness of the junctions
    final int INF = 20*20*20*50 + 10;
    $G g;

    void run() {
        $R $r = new $R(System.in);
        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();

            bus = new int[N];
            g = new $G(N);

            for (int i = 0; i < N; i++)
                bus[i] = $r.nextInt();

            M = $r.nextInt();

            for (int i = 0; i < M; i++) {
                int a = $r.nextInt() - 1;
                int b = $r.nextInt() - 1;
                int diff = bus[b]-bus[a];
                g.add(a, b, diff*diff*diff);
            }

            boolean[] ncp = g.bellmanFordVertices(0);

            Q = $r.nextInt();

            System.out.println("Case " + ncase + ":");
            for (int i = 0; i < Q; i++) {
                int dst = $r.nextInt() - 1;
                if (ncp[dst] || g.dis[dst] == INF || g.dis[dst] < 3)
                    System.out.println("?");
                else
                    System.out.println(g.dis[dst]);
            }

        }
    }
}
