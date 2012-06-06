import java.io.*;
import java.util.*;

public class AgainStoneGame {
    public static void main(String[] args) {
        new AgainStoneGame().run();
    }

    class $R {
        BufferedReader r;
        StringTokenizer s;
        String ln;
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

    int n;
    void run() {
        $R $r = new $R(System.in);
        int T = $r.nextInt();
        int ncase = 1;
        int nim;
        while (T-- > 0) {
            n = $r.nextInt();
            nim = 0;
            for (int j = 0; j < n; j++)
                nim ^= nimNumber($r.nextInt());
            System.out.printf("Case %d: %s\n", ncase++, nim == 0 ? "Bob" : "Alice");
        }
    }

    int nimNumber (int stones) {
        while ((stones & 1) != 0)
            stones >>= 1;
        return stones >> 1;
    }
}
