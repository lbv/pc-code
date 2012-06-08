import java.io.*;
import java.util.*;

public class ARefiningCompany {
    public static void main(String[] args) {
        new ARefiningCompany().run();
    }

    class $R {
        BufferedReader r;
        StringTokenizer s;
        $R(InputStream in) {
            r = new BufferedReader(new InputStreamReader(in));
            s = new StringTokenizer("");
        }

        String next() {
            String ln;
            while (!s.hasMoreTokens()) {
                try { ln = r.readLine(); }
                catch(Exception e) { return null; }
                if (ln == null) break;
                s = new StringTokenizer(ln);
            }
            return s.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }

    int T;
    int M, N;
    int[][] uranium, radium;
    void run() {
        $R $r = new $R(System.in);
        T = $r.nextInt();

        int ncase = 1;
        while (T-- > 0) {
            M = $r.nextInt();
            N = $r.nextInt();
            uranium = new int[M][N];
            radium = new int[M][N];
            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    uranium[i][j] = $r.nextInt() + prevCol(uranium, i, j);
            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    radium[i][j] = $r.nextInt() + prevRow(radium, i, j);
            System.out.printf("Case %d: %d\n", ncase++, solve());
        }
    }

    int solve() {
        int[][] dp = new int[M][N];

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                dp[i][j] = Math.max(
                    radium[i][j] + prevCol(dp, i, j),
                    uranium[i][j] + prevRow(dp, i, j));
            }
        }

        return dp[M-1][N-1];
    }

    int prevCol(int[][] a, int i, int j) {
        if (j == 0) return 0;
        return a[i][j-1];
    }

    int prevRow(int[][] a, int i, int j) {
        if (i == 0) return 0;
        return a[i-1][j];
    }
}
