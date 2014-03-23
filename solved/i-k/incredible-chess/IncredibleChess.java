import java.io.*;
import java.util.*;

public class IncredibleChess {
    public static void main(String[] args) {
        new IncredibleChess().run();
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
            int n = $r.nextInt();

            int[] W = new int[n];
            for (int i = 0; i < n; i++)  W[i] = $r.nextInt();
            int[] B = new int[n];
            for (int i = 0; i < n; i++)  B[i] = $r.nextInt();

            int nim = 0;

            for (int i = 0; i < n; i++) {
                int diff = B[i] - W[i] - 1;
                nim ^= diff;
            }

            $w.println("Case " + ncase + ": "
                       + (nim == 0 ? "black" : "white" ) + " wins");
        }

        $w.close();
    }
}
