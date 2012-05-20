import java.io.*;
import java.util.*;

public class RoadConstruction {
    public static void main(String[] args) {
        new RoadConstruction().run();
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
    final int MAX_DEGREE = 50;
    final int INF = Integer.MAX_VALUE;
    class $G {
        class E {
            int v, w;
            E(int V, int W) { v=V; w=W; }
        }
        int n, mstCost;
        boolean mstIsFull;
        E[][] edg;
        int[] deg;
        int[] dist, parent;
        $G(int N) {
            n=N;
            edg = new E[n][MAX_DEGREE];
            deg = new int[n];
        }
        void add(int u, int v, int w) { edg[u][deg[u]++] = new E(v, w); }
        void prim(int src) {
            boolean[] vis = new boolean[n];
            int[] dis = new int[n];
            int[] par = new int[n];
            Arrays.fill(dis, INF);
            Arrays.fill(par, -1);

            dis[src] = 0;
            mstCost = 0;
            for (int v = src; v >= 0; v = minV(vis, dis)) {
                vis[v] = true;
                for (int i=0; i < deg[v]; i++) {
                    E e = edg[v][i];
                    if (!vis[e.v] && e.w < dis[e.v]) {
                        dis[e.v] = e.w;
                        par[e.v] = v;
                    }
                }
            }
            dist=dis;
            parent=par;
        }
        int minV(boolean[] vis, int[] dis) {
            int d=INF, v=-1;
            for (int i=0; i<n; i++)
                if (!vis[i] && dis[i] < d) { v=i; d=dis[i]; }
            return v;
        }
    }

    class CityMap extends HashMap<String, Integer> {}

    CityMap cities;
    int N;

    void run() {
        $R $r = new $R(System.in);

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            int m = $r.nextInt();

            int[][] data = new int[m][3];
            N = 0;
            cities = new CityMap();
            for (int i = 0; i < m; i++) {
                String c1 = $r.next();
                String c2 = $r.next();
                int w = $r.nextInt();
                data[i][0] = nameToNumber(c1);
                data[i][1] = nameToNumber(c2);
                data[i][2] = w;
            }

            $G g = new $G(N);
            for (int i = 0; i < m; i++) {
                g.add(data[i][0], data[i][1], data[i][2]);
                g.add(data[i][1], data[i][0], data[i][2]);
            }

            g.prim(0);

            int cost = 0;
            boolean possible = true;
            for (int i = 1; i < N; i++) {
                if(g.parent[i] < 0) {
                    possible = false;
                    break;
                }
                cost += g.dist[i];
            }
            System.out.println("Case " + ncase + ": " +
                               (possible ? cost : "Impossible"));

        }
    }

    int nameToNumber (String name) {
        if (cities.containsKey(name)) return cities.get(name);
        cities.put(name, N++);
        return N - 1;
    }
}
