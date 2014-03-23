import java.io.*;
import java.util.*;

public class EnormousInputTest {
    public static void main(String[] args) {
        new EnormousInputTest().run();
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
            while (b == 10 || b == 13) read();
            return sb.toString(); }
        int nextInt() {
            int ival = 0; boolean isgn = false;
            skip(); if (b == '-') { isgn = true; read(); }
            for (; b > 32; read()) ival = ival*10 + b-48;
            return isgn ? -ival : ival; }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int n = $r.nextInt();
        int k = $r.nextInt();
        int d = 0;
        while (n-- > 0) {
            int i = $r.nextInt();
            if (i % k == 0) d++;
        }
        $w.println(d);
        $w.close();
    }
}
