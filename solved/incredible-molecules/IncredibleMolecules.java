import java.io.*;
import java.util.*;

class IncredibleMolecules {
    public static void main(String[] args) {
        new IncredibleMolecules().run();
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

    int x1, y1, r1, x2, y2, r2;

    void run() {
        $R $r = new $R(System.in);
        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            x1 = $r.nextInt();
            y1 = $r.nextInt();
            r1 = $r.nextInt();

            x2 = $r.nextInt();
            y2 = $r.nextInt();
            r2 = $r.nextInt();

            System.out.println("Case " + ncase + ": " + area());
        }
    }

    double area() {
        int dx = x2-x1;
        int dy = y2-y1;
        double d = Math.sqrt(dx*dx + dy*dy);

        // Special case: te two circles don't intersect
        if (d >= r1+r2) return 0;

        double r1s = r1*r1;
        double r2s = r2*r2;

        // Special case: one circle is contained within the other
        if (d + r2 <= r1) return Math.PI * r2s;
        if (d + r1 <= r2) return Math.PI * r1s;

        double ds = d*d;

        double a = 2*Math.acos((ds + r1s - r2s) / (2*r1*d));
        double b = 2*Math.acos((ds + r2s - r1s) / (2*r2*d));

        return r1s/2*(a - Math.sin(a)) + r2s/2*(b - Math.sin(b));
    }
}
