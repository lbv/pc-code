import java.io.*;
import java.util.*;

public class BackToUnderworld {
    public static void main(String[] args) {
        new BackToUnderworld().run();
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

    class RivalList extends ArrayList<Integer> {}

    RivalList[] fights;
    boolean[] vis;
    int maxSize;

    void run() {
        $R $r = new $R(System.in);

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            int n = $r.nextInt();

            fights = new RivalList[20001];
            for (int i=0; i<n; i++) {
                int u = $r.nextInt();
                int v = $r.nextInt();

                if (fights[u] == null) fights[u] = new RivalList();
                if (fights[v] == null) fights[v] = new RivalList();
                fights[u].add(v);
                fights[v].add(u);
            }

            vis = new boolean[20001];
            maxSize = 0;
            for (int v=nextUnvisited(); v >= 0; v = nextUnvisited()) {
                dfs(v);
            }

            System.out.printf("Case %d: %d\n", ncase, maxSize);
        }
    }

    int nextUnvisited() {
        for (int i=1; i<=20000; i++) {
            if (!vis[i] && fights[i] != null)
                return i;
        }
        return -1;
    }

    class Node {
        int v;
        int team;
        Node(int V, int T) { v=V; team=T; }
    }
    void dfs(int start) {
        Stack<Node> s = new Stack<Node>();
        s.push(new Node(start, 0));
        vis[start] = true;

        int[] teams = new int[2];

        while (!s.isEmpty()) {
            Node nd = s.pop();
            teams[nd.team]++;

            if (fights[nd.v] == null) continue;
            for (int v : fights[nd.v]) {
                if (! vis[v]) {
                    s.push(new Node(v, (nd.team + 1) % 2));
                    vis[v] = true;
                }
            }
        }
        maxSize += Math.max(teams[0], teams[1]);
    }
}
