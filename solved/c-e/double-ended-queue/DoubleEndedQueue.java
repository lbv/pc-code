import java.io.*;
import java.util.*;

public class DoubleEndedQueue {
    public static void main(String[] args) {
        new DoubleEndedQueue().run();
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
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    class IQ extends ArrayDeque<Integer> {};

    int N, M;
    IQ q;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();

        q = new IQ();

        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            M = $r.nextInt();

            $w.println("Case " + ncase + ":");
            q.clear();

            while (M-- > 0) {
                String command = $r.next().intern();

                if (command == "pushLeft") {
                    int x = $r.nextInt();

                    if (q.size() == N)
                        $w.println("The queue is full");
                    else {
                        q.addFirst(x);
                        $w.println("Pushed in left: " + x);
                    }
                }
                else if (command == "pushRight") {
                    int x = $r.nextInt();

                    if (q.size() == N)
                        $w.println("The queue is full");
                    else {
                        q.addLast(x);
                        $w.println("Pushed in right: " + x);
                    }
                }
                else if (command == "popLeft") {
                    if (q.size() == 0)
                        $w.println("The queue is empty");
                    else {
                        int x = q.removeFirst();
                        $w.println("Popped from left: " + x);
                    }
                }
                else if (command == "popRight") {
                    if (q.size() == 0)
                        $w.println("The queue is empty");
                    else {
                        int x = q.removeLast();
                        $w.println("Popped from right: " + x);
                    }
                }
            }
        }

        $w.close();
    }
}
