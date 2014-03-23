import java.io.*;
import java.util.*;

public class Bishops {
    public static void main(String[] args) {
        new Bishops().run();
    }
    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        void skip() { while (b >= 0 && b <= 32) read(); }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    int r1, c1, r2, c2;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();

        for (int ncase=1; ncase <= T; ncase++) {
            r1 = $r.nextInt();
            c1 = $r.nextInt();
            r2 = $r.nextInt();
            c2 = $r.nextInt();

            $w.print("Case " + ncase + ": ");
            int sol = solve();
            if (sol < 0)
                $w.println("impossible");
            else
                $w.println(sol);
        }

        $w.close();
    }

    int solve() {
        if (r1==r2 && c1==c2) return 0;
        if (((r1+c1) & 1) != ((r2+c2) & 1)) return -1;
        if (Math.abs(r1-r2) == Math.abs(c1-c2)) return 1;
        return 2;
    }
}
