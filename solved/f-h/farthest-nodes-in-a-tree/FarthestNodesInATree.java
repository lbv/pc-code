import java.io.*;
import java.util.*;

public class FarthestNodesInATree {
    public static void main(String[] args) {
        new FarthestNodesInATree().run();
    }

    class $G {
        class E {
            int v, w;
            E(int V, int W) { v=V; w=W; }
        }
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

    int N;
    $G g;
    void run() {
        $R $r = new $R(System.in);

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();

            g = new $G(N);

            for (int i = 0; i < N-1; i++) {
                int u = $r.nextInt();
                int v = $r.nextInt();
                int w = $r.nextInt();
                g.add(u, v, w);
                g.add(v, u, w);
            }

            solve();
            System.out.println("Case " + ncase + ": " + diam);
        }
    }

    class Node {
        int v, c;  // vertex and cost (distance) so far
        Node(int V, int C) { v=V; c=C; }
    }

    int diam;  // graph diameter
    int cornerV;

    void solve() {
        dfs(getLeaf());
        dfs(cornerV);
    }

    void dfs(int start) {
        Stack<Node> s = new Stack<Node>();
        diam = 0;
        cornerV = -1;

        boolean[] vis = new boolean[N];

        s.push(new Node(start, 0));
        vis[start] = true;

        while (!s.isEmpty()) {
            Node nd = s.pop();
            if (g.nEdges(nd.v) == 1 && nd.c > diam) {
                diam = nd.c;
                cornerV = nd.v;
            }

            if (g.edg[nd.v] == null) continue;
            for ($G.E e : g.edg[nd.v]) {
                if (!vis[e.v]) {
                    s.push(new Node(e.v, nd.c + e.w));
                    vis[e.v] = true;
                }
            }
        }
    }

    int getLeaf() {
        for (int i = 0; i < N; i++) {
            if (g.nEdges(i) == 1) return i;
        }
        return -1;
    }
}
