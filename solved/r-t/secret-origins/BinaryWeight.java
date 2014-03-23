import java.io.*;
import java.util.*;

public class BinaryWeight {
    public static void main(String[] args) {
        new BinaryWeight().run();
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

    int N;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            $w.println("Case " + ncase + ": " + solution());
        }

        $w.close();
    }

    int solution() {
        boolean[] bin = new boolean[33];  // binary representation of N
        for (int x = N, i = 0; x != 0; x >>= 1, i++)
            bin[i] = (x & 1) == 1;

        int i;
        for (i = 0; !bin[i]; i++);

        // number of 1 bits that have to be "moved" to the lowest significant positions
        int bits = 0;
        while (bin[i + 1]) { bits++; i++; }

        // now i is the position of the 1 that has to be shifted to the left
        bin[i + 1] = true;

        for (int j = 0; j <= i; j++) bin[j] = (j < bits ? true : false);

        int sol = 0;
        for (int j = 0, p = 1; j < 32; j++, p<<=1) {
            if (bin[j]) sol += p;
        }
        return sol;
    }
}
