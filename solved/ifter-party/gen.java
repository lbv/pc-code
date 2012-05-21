import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();

        int T = 300;
        System.out.println(T);

        for (int i = 1; i <= 10; ++i)
            for (int j = 0; j < i; ++j) {
                System.out.println("" + i + " " + j);
                --T;
            }

        while (T-- > 0)
            testCase();
    }

    final int LIM = 2147483000;
    void testCase() {
        int P = rnd.nextInt(LIM);
        int L = rnd.nextInt(P);

        System.out.println("" + P + " " + L);
    }
}
