import java.io.*;
import java.util.*;

class Minesweeper {
    public static void main(String[] args) {
        new Minesweeper().run();
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

    int N, M;
    char[][] map;
    void run() {
        $R $r = new $R(System.in);

        int nfield = 0;
        while (true) {
            N = $r.nextInt();
            M = $r.nextInt();
            if (N == 0 && M == 0) break;

            map = new char[N][M];
            for (int i = 0; i < N; i++)
                map[i] = $r.nextLine().toCharArray();

            if (nfield++ > 0)
                System.out.println();

            System.out.println("Field #" + nfield + ":");
            calcField();
            printField();
        }
    }

    int[][] mines;
    void calcField() {
        mines = new int[N][M];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (map[i][j] == '*') {
                    incMine(i, j-1);
                    incMine(i, j+1);
                    incMine(i-1, j);
                    incMine(i+1, j);
                    incMine(i-1, j-1);
                    incMine(i-1, j+1);
                    incMine(i+1, j-1);
                    incMine(i+1, j+1);
                }
            }
        }
    }

    void incMine(int i, int j) {
        if (i < 0 || i >= N || j < 0 || j >= M) return;
        mines[i][j]++;
    }

    void printField() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (map[i][j] == '*')
                    System.out.print("*");
                else
                    System.out.print(mines[i][j]);
            }
            System.out.println();
        }
    }
}

