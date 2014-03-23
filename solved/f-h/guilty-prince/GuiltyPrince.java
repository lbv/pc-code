import java.io.*;
import java.util.*;

public class GuiltyPrince {
    public static void main(String[] args) {
        new GuiltyPrince().run();
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

    int W, H;
    char[][] map;
    void run() {
        $R $r = new $R(System.in);
        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            W = $r.nextInt();
            H = $r.nextInt();
            map = new char[H][W];
            for (int i = 0; i < H; i++) {
                map[i] = $r.nextLine().toCharArray();
            }

            System.out.printf("Case %d: %d\n", ncase, solution());
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

    int solution() {
        Queue<Node> q = new LinkedList<Node>();
        boolean[][] visited = new boolean[H][W];
        Node start = findStartingPos();
        q.add(start);
        visited[start.r][start.c] = true;

        int cells = 0;
        while (!q.isEmpty()) {
            Node n = q.remove();
            cells++;

            for (int i = 0; i < 4; i++) {
                int r = n.r + deltas[i][0];
                int c = n.c + deltas[i][1];

                if (isValidPos(r, c) && (!visited[r][c])
                    && map[r][c] == '.') {
                    q.add(new Node(r, c));
                    visited[r][c] = true;
                }
            }
        }
        return cells;
    }

    boolean isValidPos(int r, int c) {
        return r >= 0 && r < H && c >= 0 && c < W;
    }

    Node findStartingPos() {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (map[i][j] == '@')
                    return new Node(i, j);
            }
        }
        return null;
    }
}
