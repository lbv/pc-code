import java.io.*;
import java.util.*;

public class EkkaDokka {
    public static void main(String[] args) {
        new EkkaDokka().run();
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

    boolean possible;
    long N, M, W;
    long[] powers;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        precompute();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            W = $r.nextLong();

            solve();

            $w.print("Case " + ncase + ": ");
            if (possible)
                $w.println("" + N + " " + M);
            else
                $w.println("Impossible");
        }

        $w.close();
    }

    void precompute() {
        powers = new long[64];
        long p = 2;
        for (int i=1; i <= 63; i++) {
            powers[i] = p;
            p <<= 1;
        }
    }

    void solve() {
        if ((W & 1) == 1) {
            possible = false;
            return;
        }

        long half = W/2;
        long div, mod, den;
        int idx = 1;

        den = powers[idx];
        while (true) {
            div = W / den;
            mod = W % den;
            if (mod != 0) continue;

            if ((div & 1) == 1) {
                N = div;
                M = den;
                possible = true;
                return;
            }

            den = powers[++idx];
            if (den > half) break;
        }

        possible = false;
    }
}
