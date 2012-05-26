import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();

        int T = 100;
        System.out.println(T);

        while (T-- > 0)
            testCase();
    }

    void testCase() {
        System.out.println();

        int n = rnd.nextInt(50) + 1;
        System.out.println(n);

        for (int i = 0; i < n; ++i) {
            int w = rnd.nextInt(101);
            System.out.print(w);

            for (int j = 1; j < n; ++j) {
                w = rnd.nextInt(101);
                System.out.print(" " + w);
            }

            System.out.println();
        }
    }
}
