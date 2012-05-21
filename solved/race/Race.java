import java.io.*;
import java.util.*;

public class Race {
    public static void main(String[] args) {
        new Race().run();
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

    class $U {
        // Binomial coefficients
        int[][] chooseMod(int lim, int mod) {
            int[][] bc = new int[lim + 1][lim + 1];
            for (int n = 1; n <= lim; n++) { bc[n][n] = 1; bc[n][1] = n; }
            for (int n = 3; n <= lim; n++)
                for (int k = 2; k < n; k++)
                    bc[n][k] = (bc[n-1][k-1] + bc[n-1][k]) % mod;
            return bc;
        }
    }

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        prepare();

        for (int ncase = 1; ncase <= T; ncase++) {
            int n = $r.nextInt();

            $w.println("Case " + ncase + ": " + dp[n]);
        }

        $w.close();
    }

    int[] dp;
    final int LIM=1000;
    final int MOD=10056;

    void prepare() {
        dp = new int[LIM + 1];
        int[][] bc = new $U().chooseMod(LIM, MOD);
        dp[0] = dp[1] = 1;

        for (int i=2; i <= LIM; i++) {
            int sum = 0;
            for (int j=1; j <= i; j++)
                sum = (sum + (dp[i-j] * bc[i][j]) % MOD) % MOD;
            dp[i] = sum;
        }
    }
}
