import java.io.*;
import java.util.*;

class PrimeGenerator2 {
    public static void main(String[] args) {
        new PrimeGenerator2().run();
    }

    class $R {
        BufferedReader r;
        StringTokenizer s;
        $R(InputStream in) {
            r = new BufferedReader(new InputStreamReader(in));
            s = new StringTokenizer("");
        }
        String gets() {
            try { return r.readLine(); } catch(Exception e) { return null; } }
        String nextLine() {
            return s.hasMoreTokens() ? s.nextToken("") : gets(); }
        boolean hasNext() {
            while (!s.hasMoreTokens()) {
                String ln = gets();
                if (ln == null) return false;
                s = new StringTokenizer(ln);
            }
            return true;
        }
        String next() { return hasNext() ? s.nextToken() : null; }
        int nextInt() { return Integer.parseInt(next()); }
    }
    class $U {
        boolean[] primeSieve(int n) {
            boolean[] primes = new boolean[n+1];
            Arrays.fill(primes, true);
            primes[0] = primes[1] = false;
            for (int i=2; i*i <= n; i++)
                if (primes[i])
                    for (int j = i, v=i*j; v <= n; j++, v+=i)
                        primes[v] = false;
            return primes;
        }
        boolean[] primeSegSieve(int a, int b, List<Integer> inp) {
            boolean[] primes = new boolean[b-a+1];
            Arrays.fill(primes, true);
            int sqr_b = (int)Math.sqrt(b);
            for (int i=0, np=inp.size(); i<np; i++) {
                int p = inp.get(i);
                if (p > sqr_b) break;
                for (int j = (a+p-1)/p, v=j*p; v <= b; j++, v += p)
                    primes[v-a] = false;
            }
            return primes;
        }
    }

    final int BASE_PRIMES = 31623;  // sqrt(10^9)
    boolean[] primeMap;

    void run() {
        $R $r = new $R(System.in);
        int t = $r.nextInt();

        $U $u = new $U();
        primeMap = $u.primeSieve(BASE_PRIMES);
        List<Integer> firstPrimes = new ArrayList<Integer>();
        for (int i = 0; i <= BASE_PRIMES; i++)
            if (primeMap[i])
                firstPrimes.add(i);

        boolean first = true;
        while (t-- > 0) {
            int m = $r.nextInt();
            int n = $r.nextInt();

            if (first) first = false;
            else System.out.println();

            for (; m <= BASE_PRIMES && m <= n; m++)
                if (primeMap[m])
                    System.out.println(m);

            if (m > n) continue;

            boolean[] segPrimes = $u.primeSegSieve(m, n, firstPrimes);

            for (int i = m, j = 0; i <= n; i++, j++) {
                if (segPrimes[j])
                    System.out.println(i);
            }
        }
    }
}

