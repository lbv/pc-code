import java.io.*;
import java.util.*;

public class Rooks {
    public static void main(String[] args) {
        new Rooks().run();
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

    long[][] dp;
    final int MAX_N = 30;
    final int MAX_K = 30*30;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        precompute();
        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            int n = $r.nextInt();
            int k = $r.nextInt();

            $w.println("Case " + ncase + ": " + dp[n][k]);
        }

        $w.close();
    }

    void precompute() {
        dp = new long[MAX_N + 1][MAX_K + 1];
        for (int i = 0; i <= MAX_N; i++) {
            dp[i][0] = 1;
            dp[i][1] = i*i;
        }
        for (int j = 2; j <= MAX_K; j++)
            for (int i = 1; i <= MAX_N; i++) {
                int rows = i - j + 1;
                int rs = rows*rows;
                if (rs % j == 0)
                    dp[i][j] = dp[i][j-1]*(rs/j);
                else
                    dp[i][j] = (dp[i][j-1]/j)*rs;

            }
    }
}
