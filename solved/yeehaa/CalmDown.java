import java.io.*;
import java.util.*;

public class CalmDown {
    public static void main(String[] args) {
        new CalmDown().run();
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
        double nextDouble() { return Double.parseDouble(next()); }
    }

    void run() {
        $R $r = new $R(System.in);

        int T = $r.nextInt();
        int ncase = 1;
        while (T-- > 0) {
            double R = $r.nextDouble();
            int N = $r.nextInt();
            System.out.println("Case " + (ncase++) + ": " + f(R, N));
        }
    }

    double f(double R, int n) {
        return R / (1/Math.sin(Math.PI/n) + 1);
    }
}
