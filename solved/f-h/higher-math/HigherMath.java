import java.io.*;
import java.util.*;

public class HigherMath {
    public static void main(String[] args) {
        new HigherMath().run();
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

    int[] num;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();

        num = new int[3];

        for (int ncase = 1; ncase <= T; ncase++) {
            num[0] = $r.nextInt();
            num[1] = $r.nextInt();
            num[2] = $r.nextInt();

            sort();

            int a = num[0]*num[0];
            int b = num[1]*num[1];
            int c = num[2]*num[2];

            $w.println("Case " + ncase + ": "
                       + (a+b==c ? "yes" : "no" ));
        }

        $w.close();
    }

    void sort() {
        if (num[1] < num[0]) swap(1, 0);
        if (num[2] < num[1]) {
            swap(2, 1);
            if (num[1] < num[0]) swap(1, 0);
        }
    }

    void swap(int i, int j) {
        int x = num[i];
        num[i] = num[j];
        num[j] = x;
    }
}
