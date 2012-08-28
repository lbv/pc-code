import java.io.*;
import java.util.*;

public class Fibsieves {
    public static void main(String[] args) {
        new Fibsieves().run();
    }

    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        boolean hasNext() { skip(); return b >= 0; }
        void skip() { while (b >= 0 && b <= 32) read(); }
        String next() {
            StringBuilder sb = new StringBuilder();
            for (skip(); b > 32; read()) sb.append((char)b);
            return sb.length() == 0 ? null : sb.toString(); }
        String nextLine() {
            StringBuilder sb = new StringBuilder();
            for (; b != 10 && b != 13; read()) sb.append((char)b);
            while (b == 10 || b == 13) read(); return sb.toString(); }
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
        long nextLong() {
            long i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    long S, R, C;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            S = $r.nextLong();
            solve();
            $w.println("Case " + ncase + ": " + C + " " + R);
        }

        $w.close();
    }

    void solve() {
        long ring = (long) Math.ceil(Math.sqrt(S));

        long low = (ring-1)*(ring-1);
        long high = ring*ring;
        long n = high-low;

        if (S - low <= n/2) {
            R = ring;
            C = S - low;
        }
        else {
            C = ring;
            R = high - S + 1;
        }

        if ((ring & 1) == 1) {
            long x = R;
            R = C;
            C = x;
        }
    }
}
