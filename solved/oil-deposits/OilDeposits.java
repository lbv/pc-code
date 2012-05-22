import java.io.*;
import java.util.*;

public class OilDeposits {
    public static void main(String[] args) {
        new OilDeposits().run();
    }

    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        void skip() { while (b >= 0 && b <= 32) read(); }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
        String nextLine() {
            StringBuilder sb = new StringBuilder();
            for (; b != 10 && b != 13; read()) sb.append((char)b);
            while (b == 10 || b == 13) read(); return sb.toString(); }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    int M, N;
    char[][] map;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        while (true) {
            M = $r.nextInt();
            N = $r.nextInt();
            if (M == 0) break;

            $r.skip();

            map = new char[M][];
            for (int i = 0; i < M; i++)
                map[i] = $r.nextLine().toCharArray();

            $w.println(solve());
        }

        $w.close();
    }

    boolean[][] col;

    int solve() {
        col = new boolean[M][N];  // colored or not

        int deposits = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (!col[i][j] && map[i][j] == '@') {
                    dfs(i, j);
                    deposits++;
                }
            }
        }
        return deposits;
    }

    // offsets to visit neighbours in the map
    final int[][] dd = {
        { -1, -1 },
        { -1, 0 },
        { -1, 1 },
        { 0, -1 },
        { 0, 1 },
        { 1, -1 },
        { 1, 0 },
        { 1, 1 }
    };
    void dfs(int i, int j) {
        col[i][j] = true;

        for (int k = 0; k < 8; k++) {
            int ni = i + dd[k][0];
            int nj = j + dd[k][1];
            if (isValid(ni, nj) && !col[ni][nj] && map[ni][nj] == '@')
                dfs(ni, nj);
        }
    }

    boolean isValid(int i, int j) {
        return i >= 0 && i < M && j >= 0 && j < N;
    }
}
