import java.io.*;
import java.util.*;

public class AgeSort {
    public static void main(String[] args) {
        new AgeSort().run();
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

    int[] ages;
    void run() {
        $R $r = new $R(System.in);

        while (true) {
            int n = $r.nextInt();
            if (n == 0) break;

            ages = new int[100];

            for (int i = 0; i < n; i++) {
                int idx = $r.nextInt();
                ages[idx]++;
            }

            boolean space = false;
            StringBuffer sb = new StringBuffer();
            for (int i = 1; i < 100; i++) {
                for (int j = 0; j < ages[i]; j++) {
                    if (! space) space = true;
                    else sb.append(' ');

                    sb.append(i);
                }
            }
            System.out.println(sb.toString());
        }
    }
}
