import java.io.*;
import java.util.*;

class Drunk {
    public static void main(String[] args) {
        new Drunk().run();
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
        // Topological sort
        class VL extends ArrayList<Integer> {}
        VL topoSort() {
            int[] in = new int[n];
            for (int i = 0; i<n; i++)
                for (int j = 0, ne = nEdges(i); j<ne; j++) {
                    E e = edg[i].get(j);
                    in[e.v]++;
                }
            Deque<Integer> q = new ArrayDeque<Integer>();
            for (int i = 0; i < n; i++)
                if (in[i] == 0) q.add(i);
            VL res = new VL();
            while(!q.isEmpty()) {
                int v = q.remove();
                res.add(v);
                for (int i=0, ne=nEdges(v); i<ne; i++) {
                    E e = edg[v].get(i);
                    in[e.v]--;
                    if (in[e.v] == 0)
                        q.add(e.v);
                }
            }
            return res;
        }
    }

    int M;
    $G g;

    void run() {
        $R $r = new $R(System.in);
        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            M = $r.nextInt();

            g = new $G(2*M);
            drinks = new DrinkMap();
            drinkCount = 0;

            for (int i=0; i < M; i++) {
                int a = drinkNum($r.next());
                int b = drinkNum($r.next());

                g.add(a, b, 0);
            }

            $G.VL sort = g.topoSort();

            System.out.println("Case " + ncase + ": " +
                               (sort.size() == g.n ? "Yes" : "No" ));
        }
    }

    class DrinkMap extends HashMap<String, Integer> {}
    DrinkMap drinks;
    int drinkCount;

    int drinkNum(String drink) {
        Integer r = drinks.get(drink);
        if (r != null) return r;
        drinks.put(drink, drinkCount++);
        return drinkCount - 1;
    }
}

