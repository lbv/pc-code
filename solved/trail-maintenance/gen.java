import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;

    final int T = 25;
//    final int N = 200;
//    final int W = 1000;
    final int N = 5;
    final int W = 10;
    final int L = 10000;

    void run() {
        rnd = new Random();

        System.out.println(T);

        for (int i = 0; i < T; ++i)
            testCase();
    }

    void testCase() {
        int n = rnd.nextInt(N - 1) + 2;
        int w = rnd.nextInt(W) + 1;

        System.out.println("" + n + " " + w);

        for (int i = 0; i < w; ++i) {
            int u = rnd.nextInt(n) + 1;

            int v;
            do {
                v = rnd.nextInt(n) + 1;
            } while (v == u);

            int l = rnd.nextInt(L) + 1;

            System.out.println("" + u + " " + v + " " + l);
        }
    }
}
