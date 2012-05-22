import java.io.*;
import java.util.*;

public class Hexabonacci {
    public static void main(String[] args) {
        new Hexabonacci().run();
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
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    int[] hex;
    final int MAX = 10000;
    final int MOD = 10000007;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();

        hex = new int[MAX + 1];
        int N;
        int idx;  // index of the last valid value

        for (int ncase = 1; ncase <= T; ncase++) {
            hex[6] = 0;
            for (int i = 0; i < 6; i++) {
                hex[i] = $r.nextInt() % MOD;
                hex[6] = (hex[6] + hex[i]) % MOD;
            }
            idx = 6;

            N = $r.nextInt();

            while (idx < N) {
                int val = (hex[idx] * 2 - hex[idx-6]) % MOD;
                if (val < 0) val += MOD;
                hex[++idx] = val;
            }

            $w.println("Case " + ncase + ": " + hex[N]);
        }

        $w.close();
    }
}
