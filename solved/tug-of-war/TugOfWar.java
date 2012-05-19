import java.io.*;
import java.util.*;

public class TugOfWar {
    public static void main(String[] args) {
        new TugOfWar().run();
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
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    int[] p;
    int[] t;
    int N;
    int W;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();

            p = new int[N];
            t = new int[2];
            W = 0;
            for (int i = 0; i < N; i++) {
                p[i] = $r.nextInt();
                W += p[i];
            }

            solve();
            $w.println("Case " + ncase + ": " + t[0] + " " + t[1]);
        }
        $w.close();
    }

    void solve() {
        int halfW = W/2;
        int teamSize = N/2;

        boolean[][] dp = new boolean[teamSize+1][W+1];
        dp[0][0] = true;

        int[] max = new int[teamSize+1];
        int[] min = new int[teamSize+1];
        Arrays.fill(max, -1);
        Arrays.fill(min, W+1);

        max[0] = min[0] = 0;

        Arrays.sort(p);

        for (int i = 0; i < N; i++) {
            int kFrom = i+1 > teamSize ? teamSize : i+1;

            for (int k = kFrom; k >= 1; k--) {
                int jFrom = min[k-1] + p[i];
                int jTo = max[k-1] + p[i];

                final boolean[] dpK = dp[k];
                final boolean[] dpK1 = dp[k-1];

                for (int j = jFrom, j2 = j-p[i]; j <= jTo; j++, j2++) {
                    if (! dpK[j] && dpK1[j2])
                        dpK[j] = true;
                }
                if (jFrom < min[k]) min[k] = jFrom;
                max[k] = jTo;
            }
        }

        int bestW = 0;

        for (int j = 0; true; j++) {
            if (dp[teamSize][halfW + j]) {
                bestW = halfW + j;
                break;
            }
            if (dp[teamSize][halfW - j]) {
                bestW = halfW - j;
                break;
            }
        }

        t[0] = Math.min(bestW, W-bestW);
        t[1] = Math.max(bestW, W-bestW);
    }
}
