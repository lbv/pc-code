import java.io.*;
import java.util.*;

class LifeTheUniverseAndEverything {
    public static void main(String[] args) {
        new LifeTheUniverseAndEverything().run();
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

    void run() {
        $R $r = new $R(System.in);

        while (true) {
            int n = $r.nextInt();
            if (n == 42) break;
            System.out.println(n);
        }
    }
}

