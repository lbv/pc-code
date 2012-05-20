import java.io.*;
import java.util.*;

public class TheCrystalMaze {
    public static void main(String[] args) {
        new TheCrystalMaze().run();
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

    class Sol {
        int val;
        Sol(int V) { val=V; }
    }
    Sol[][] solMap;
    char[][] map;
    int M, N, Q;
    void run() {
        $R $r = new $R(System.in);

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            M = $r.nextInt();
            N = $r.nextInt();
            Q = $r.nextInt();

            map = new char[M][N];
            for (int i = 0; i < M; i++)
                map[i] = $r.nextLine().toCharArray();

            solMap = new Sol[M][N];

            System.out.println("Case " + ncase + ":");
            for (int i = 0; i < Q; i++) {
                int x = $r.nextInt();
                int y = $r.nextInt();

                if (solMap[x-1][y-1] == null)
                    solve(x-1, y-1);

                System.out.println(solMap[x-1][y-1].val);
            }
        }
    }

    class Node {
        int r, c;
        Node(int R, int C) { r=R; c=C; }
    }
    int[][] deltas = {
        { 0, 1 },
        { 0, -1 },
        { 1, 0 },
        { -1, 0 },
    };
    void solve(int r, int c) {
        Queue<Node> q = new LinkedList<Node>();
        q.add(new Node(r, c));

        boolean[][] vis = new boolean[M][N];
        vis[r][c] = true;

        final Sol sol = new Sol(0);

        while (!q.isEmpty()) {
            Node nd = q.remove();
            solMap[nd.r][nd.c] = sol;

            if (map[nd.r][nd.c] == 'C') sol.val++;
            for (int[] delta : deltas) {
                int nr = nd.r + delta[0];
                int nc = nd.c + delta[1];

                if (isValidPos(nr, nc) && !vis[nr][nc] && map[nr][nc] != '#') {
                    q.add(new Node(nr, nc));
                    vis[nr][nc] = true;
                }
            }
        }
    }

    boolean isValidPos(int r, int c) {
        return r >= 0 && r < M && c >= 0 && c < N;
    }
}
