import java.io.*;
import java.util.*;

public class KnightsInChessboard {
    public static void main(String[] args) {
        new KnightsInChessboard().run();
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

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            int m = $r.nextInt();
            int n = $r.nextInt();

            if (m > n) {
                int x = m;
                m = n;
                n = x;
            }

            $w.println("Case " + ncase + ": " + solve(m, n));
        }

        $w.close();
    }

    int solve(int a, int b) {
        if (a == 1) return b;
        if (a == 2)
            return b/4*4 + Math.min(2, b%4)*2;

        int prod = a*b;
        int res = prod/2;
        if ((prod & 1) == 1) res++;
        return res;
    }
}
