import java.io.*;
import java.util.*;

class The3nPlus1Problem {
    public static void main(String[] args) {
        new The3nPlus1Problem().run();
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

    int[] cycles;

    void run() {
        $R $r = new $R(System.in);

        initCycles();

        while ($r.hasNext()) {
            int i = $r.nextInt();
            int j = $r.nextInt();

            int from = Math.min(i, j);
            int to = Math.max(i, j);

            int max = 0;
            for (int k = from; k <= to; k++) {
                int cycle = cycleLen(k);
                if (cycle > max)
                    max = cycle;
            }

            System.out.println("" + i + " " + j + " " + max);
        }
    }

    final int MAX = 1000000 - 1;

    void initCycles() {
        cycles = new int[MAX+1];
        cycles[1] = 1;
    }

    int cycleLen(int n) {
        if (cycles[n] != 0) return cycles[n];

        int x = n;
        int cnt = 0;
        while (x > MAX || cycles[x] == 0) {
            if (x % 2 == 0)
                x /= 2;
            else
                x = 3*x + 1;
            cnt++;
        }
        cnt += cycles[x];
        cycles[n] = cnt;
        return cnt;
    }
}
