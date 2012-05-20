import java.io.*;
import java.util.*;

public class SumOfConsecutive {
    public static void main(String[] args) {
        new SumOfConsecutive().run();
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
        long nextLong() {
            long i=0; boolean s=false; skip();
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

        precalculate();

        for (int ncase = 1; ncase <= T; ncase++) {
            long N = $r.nextLong();

            $w.println("Case " + ncase + ": " + solution(N));
        }

        $w.close();
    }

    class IL extends ArrayList<Integer> {}

    final int NPRIMES = 10000000 + 1;  // sqrt(10^14)
    IL primes;

    void precalculate() {
        primes = primeSieveList(NPRIMES);
    }

    int solution (long N) {
        // Routine based on the prime factorization of N
        int ways = 1;
        long n = N;
        while (n % 2 == 0) n /= 2;
        int sqrn = (int) Math.sqrt(n);
        for (int i = 1, np = primes.size(); i < np; i++) {
            int prime = primes.get(i);
            if (prime > sqrn) break;
            if (n % prime != 0) continue;
            int exp = 0;
            while (n % prime == 0) { n /= prime; exp++; }
            ways *= 1 + exp;
            sqrn = (int) Math.sqrt(n);
        }
        if (n > 1) ways *= 2;
        return ways - 1;
    }

    // Primes
    IL primeSieveList(int n) {
        boolean[] comp = new boolean[(n+1)/2];
        int sqrn = (int)Math.sqrt(n);
        for (int i=3, I=1; i <= sqrn; i+=2, I++)
            if (!comp[I])
                for (int j = i*i, J=(j-1)/2; j <= n; j+=i+i, J+=i)
                    comp[J] = true;
        IL p = new IL();
        p.add(2);
        for (int i=3, I=1; i <= n; i+=2, I++)
            if (!comp[I])
                p.add(i);
        return p;
    }
}
