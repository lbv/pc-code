import java.io.*;
import java.text.*;
import java.util.*;

public class CircleInSquare {
    public static void main(String[] args) {
        new CircleInSquare().run();
    }

    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        void skip() { while (b >= 0 && b <= 32) read(); }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
        // Optional methods
        String next() {
            StringBuilder sb = new StringBuilder();
            for (skip(); b > 32; read()) sb.append((char)b);
            return sb.length() == 0 ? null : sb.toString(); }
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
        double nextDouble() { return Double.parseDouble(next()); }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    final DecimalFormat df =
        (DecimalFormat)NumberFormat.getNumberInstance(Locale.US);
    final double PI = 2 * Math.acos(0);

    double R;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        df.applyPattern("0.00");

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            R = $r.nextDouble();

            $w.println("Case " + ncase + ": " + df.format(area()));
        }

        $w.close();
    }

    double area() {
        return R*R*(4 - PI);
    }
}
