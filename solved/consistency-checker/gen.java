import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();

        int T = 50;
        System.out.println(T);

        while (T-- > 0)
            testCase();
    }

    void testCase() {
        int n = rnd.nextInt(10000) + 1;

        System.out.println(n);

        while (n-- > 0) {
            int N = rnd.nextInt(1000000000);
            System.out.println(N);
        }
    }
}
