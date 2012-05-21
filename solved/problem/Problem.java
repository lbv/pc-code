import java.io.*;
import java.math.BigInteger;
import java.util.*;

class Problem {
    public static void main(String[] args) {
        new Problem().run();
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
        BigInteger nextBigInteger() { return new BigInteger(next()); }
    }

    void run() {
        $R $r = new $R(System.in);

        int N = $r.nextInt();
        while (N-- != 0) {
            BigInteger num = $r.nextBigInteger();
            System.out.println(answer(num));
        }
    }

    long answer(BigInteger n) {
        if (n.compareTo(BigInteger.ZERO) == 0) return 1;

        long res = 0;
        while (n.compareTo(BigInteger.ZERO) != 0) {
            int d = n.mod(BigInteger.TEN).intValue();
            if (d == 0 || d == 6 || d == 9)
                res++;
            else if (d == 8)
                res += 2;

            n = n.divide(BigInteger.TEN);
        }

        return res;
    }
}
