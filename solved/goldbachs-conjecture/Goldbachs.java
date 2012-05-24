import java.io.*;
import java.util.*;

public class Goldbachs {
    public static void main(String[] args) {
        new Goldbachs().run();
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

        precalculate();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            int n = $r.nextInt();

            $w.println("Case " + ncase + ": " + solve(n));
        }

        $w.close();
    }

    class IL extends ArrayList<Integer> {};

    final int MAX = 10000000;  // 10^7
    final int LMT = 3162 + 1;
    IL primes;

    void precalculate() {
        primes = primeSieveList();
    }

    int solve(int n) {
        int half = n/2;
        int ways = 0;
        for (int i = 0, np=primes.size(); i < np; i++) {
            int prime = primes.get(i);
            if (prime > half) break;
            if (isPrime(n - prime)) ways++;
        }
        return ways;
    }

    int[] _c;
    IL primeSieveList() {
        _c = new int[(MAX>>5)+1];
        setComp(0);setComp(1);
        for (int i=4; i <= MAX; i+=2) setComp(i);
        for (int i=3; i <= LMT; i+=2)
            if (!isComp(i)) for (int j = i*i; j <= MAX; j+=i+i) setComp(j);
        IL p = new IL();
        p.add(2);
        for (int i=3; i <= MAX; i+=2) if (!isComp(i)) p.add(i);
        return p;
    }
    boolean isComp(int n) { return (_c[n>>5]&(1<<(n&31))) != 0; }
    void setComp(int n) { _c[n>>5]|=(1<<(n&31)); }
    boolean isPrime(int n) { return (_c[n>>5]&(1<<(n&31))) == 0;  }
}
