import java.io.*;
import java.util.*;

public class KSatProblem {
    public static void main(String[] args) {
        new KSatProblem().run();
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

    int N, M, K;
    int[][] wishes;
    boolean[] taken;
    void run() {
        $R $r = new $R(System.in);

        int T = $r.nextInt();
        int ncase = 1;
        while (T-- > 0) {
            N = $r.nextInt();
            M = $r.nextInt();
            K = $r.nextInt();

            wishes = new int[N+1][K+1];
            taken = new boolean[M+1];
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= K; j++) {
                    String str = $r.next();

                    int w = str.charAt(0) == '+'
                        ? Integer.parseInt(str.substring(1))
                        : Integer.parseInt(str);

                    wishes[i][j] = w;
                }
            }
            int p = $r.nextInt();
            for (int i = 0; i < p; i++) {
                int nTaken = $r.nextInt();
                taken[nTaken] = true;
            }

            System.out.printf("Case %d: %s\n", ncase++, solution());
        }
    }

    String solution() {
        for (int i = 1; i <= N; i++) {
            boolean happy = false;
            for (int j = 1; j <= K; j++) {
                int obj = Math.abs(wishes[i][j]);

                if ((wishes[i][j] > 0 && taken[obj])
                    || (wishes[i][j] < 0 && !taken[obj])) {
                    happy = true;
                    break;
                }
            }
            if (!happy) return "No";
        }
        return "Yes";
    }
}
