import java.io.*;
import java.util.*;

public class HiddenSecret {
    public static void main(String[] args) {
        new HiddenSecret().run();
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
        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            String a = normalise($r.nextLine());
            String b = normalise($r.nextLine());

            System.out.println("Case " + ncase + ": "
                               + (a.equals(b) ? "Yes" : "No"));
        }
    }

    String normalise(String str) {
        StringBuilder sb = new StringBuilder();

        char[] a = str.toLowerCase().toCharArray();
        Arrays.sort(a);
        for (int i = 0, nc=a.length; i<nc; i++) {
            if (! Character.isWhitespace(a[i]))
                sb.append(a[i]);
        }

        return sb.toString();
    }
}
