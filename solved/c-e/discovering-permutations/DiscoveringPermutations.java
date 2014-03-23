import java.io.*;
import java.util.*;

public class DiscoveringPermutations {
    public static void main(String[] args) {
        new DiscoveringPermutations().run();
    }

    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        void skip() { while (b >= 0 && b <= 32) read(); }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
        // Optional methods
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }
    class $U {
        boolean nextPermutation(char[] p, int n) {
            if (n < 2) return false;
            int i = n - 2;
            while (p[i] >= p[i + 1]) if (--i < 0) return false;
            int j = n - 1;
            while (p[j] <= p[i]) j--;
            _swap(p, i, j);
            for (i++, j=n-1; i < j; i++, j--) _swap(p, i, j);
            return true;
        }

        void _swap(char[] p, int a, int b) {
            char x = p[a];
            p[a] = p[b];
            p[b] = x;
        }
    }

    int N, K;
    char[] perm;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();

        $U $u = new $U();

        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            K = $r.nextInt();

            perm = new char[N];

            for (int i = 0; i < N; i++)
                perm[i] = (char)('A' + i);

            $w.println("Case " + ncase + ":");

            for (int i = 0; i < K; i++) {
                $w.println(perm);
                if (! $u.nextPermutation(perm, N)) break;
            }
        }

        $w.close();
    }
}
