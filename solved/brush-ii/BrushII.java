import java.io.*;
import java.util.*;

public class BrushII {
    public static void main(String[] args) {
        new BrushII().run();
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
            int N = $r.nextInt();
            int W = $r.nextInt();

            int[] ys = new int[N];  // Y coordinates of points

            for (int i = 0; i < N; i++) {
                $r.nextInt();  // ignore X coordinate
                ys[i] = $r.nextInt();
            }

            Arrays.sort(ys);

            // current y position of the top of the brush
            int y = ys[0] - 1;
            int moves = 0;

            for (int i = 0; i < N; i++) {
                if (ys[i] > y) {
                    moves++;
                    y = ys[i] + W;
                }
            }

            $w.println("Case " + ncase + ": " + moves);
        }

        $w.close();
    }
}
