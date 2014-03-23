import java.io.*;
import java.util.*;
import java.math.*;

public class LargeDivision {
    public static void main(String[] args) {
        new LargeDivision().run();
    }

    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        void skip() { while (b >= 0 && b <= 32) read(); }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
        String next() {
            StringBuilder sb = new StringBuilder();
            for (skip(); b > 32; read()) sb.append((char)b);
            return sb.length() == 0 ? null : sb.toString(); }
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
        BigInteger nextBigInteger() { return new BigInteger(next()); }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            BigInteger a = $r.nextBigInteger();
            BigInteger b = $r.nextBigInteger();

            BigInteger r = a.remainder(b);

            $w.println("Case " + ncase + ": "
                       + (r.compareTo(BigInteger.ZERO) == 0 ? "divisible"
                          : "not divisible"));
        }

        $w.close();
    }
}
