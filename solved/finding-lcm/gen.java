import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();
        int T = 325;
        System.out.println(T);
        while (T-- > 0)
            testCase();
    }

    final int LIM1 = 1000000;
    final long LIM2 = 1000000000000L;


    long gcd(long a, long b) {
        for (long c = a%b; c != 0; a=b,b=c,c=a%b); return b;
    }

    long nextLong(long lim) {
        return Math.abs(rnd.nextLong()) % lim;
    }

    void testCase() {
        int a = rnd.nextInt(LIM1) + 1;
        int b = rnd.nextInt(LIM1) + 1;

        long c = 0;
        if (rnd.nextInt(6) == 5) {
            c = nextLong(LIM2) + 1;
        }
        else {
            long lcm = a/gcd(a, b) * b;
            long d = LIM2 / lcm;
            c = lcm * (nextLong(d) + 1);
        }
        System.out.println("" + a + " " + b + " " + c);
    }
}
