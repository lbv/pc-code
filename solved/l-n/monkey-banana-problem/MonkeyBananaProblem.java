import java.io.*;
import java.util.*;

public class MonkeyBananaProblem {
    public static void main(String[] args) {
        new MonkeyBananaProblem().run();
    }

    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        boolean hasNext() { skip(); return b >= 0; }
        void skip() { while (b >= 0 && b <= 32) read(); }
        String next() {
            StringBuilder sb = new StringBuilder();
            for (skip(); b > 32; read()) sb.append((char)b);
            return sb.length() == 0 ? null : sb.toString(); }
        String nextLine() {
            StringBuilder sb = new StringBuilder();
            for (; b != 10 && b != 13; read()) sb.append((char)b);
            while (b == 10 || b == 13) read(); return sb.toString(); }
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    int N;
    int[][] map, sol;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            map = new int[N][N];
            sol = new int[N][N];

            int r, c;

            for (int i = 0, rows = 2*N-1; i < rows; i++) {
                if (i < N) {
                    r = i;
                    c = 0;
                }
                else {
                    r = N - 1;
                    c = i - r;
                }

                while (r >= 0 && c < N) {
                    map[r][c] = $r.nextInt();
                    r--;
                    c++;
                }
            }

            dp();

            $w.println("Case " + ncase + ": " + sol[N-1][N-1]);
        }

        $w.close();
    }

    void dp() {
        sol[0][0] = map[0][0];

        for (int j = 1; j < N; j++)
            sol[0][j] = sol[0][j-1] + map[0][j];
        for (int i = 1; i < N; i++)
            sol[i][0] = sol[i-1][0] + map[i][0];

        for (int i = 1; i < N; i++)
            for (int j = 1; j < N; j++)
                sol[i][j] = Math.max(sol[i-1][j], sol[i][j-1]) + map[i][j];
    }
}
