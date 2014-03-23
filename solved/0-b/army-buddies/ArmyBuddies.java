import java.io.*;
import java.util.*;

class ArmyBuddies {
    public static void main(String[] args) {
        new ArmyBuddies().run();
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
        $W() { super(new BufferedOutputStream(System.out)); } }

    int S, B, L, R;
    int[] lt, rt;  // left and right buddies

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        while (true) {
            S = $r.nextInt();
            B = $r.nextInt();
            if (S == 0 && B == 0) break;

            lt = new int[S + 2];
            rt = new int[S + 2];

            for (int i = 1, l = 0, r = 2; i <= S; i++, l++, r++) {
                lt[i] = l;
                rt[i] = r;
            }

            for (int i = 0; i < B; i++) {
                L = $r.nextInt();
                R = $r.nextInt();

                StringBuilder sb = new StringBuilder();
                if (lt[L] > 0) sb.append(lt[L]);
                else sb.append('*');

                sb.append(' ');

                if (rt[R] <= S) sb.append(rt[R]);
                else sb.append('*');

                $w.println(sb.toString());

                rt[lt[L]] = rt[R];
                lt[rt[R]] = lt[L];
            }
            $w.println("-");
        }

        $w.close();
    }
}
