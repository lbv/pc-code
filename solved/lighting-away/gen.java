import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();

        int T = 10;

        System.out.println(T);
        while (T-- > 0) {
            printTestCase();
        }
    }

    void printTestCase() {
        System.out.println();
//        int N = rnd.nextInt(1000) + 1;
//        int M = rnd.nextInt(10001);
        int N = rnd.nextInt(100) + 1;
        int M = rnd.nextInt(11);

        System.out.println("" + N + " " + M);

        while (M-- > 0) {
            int a = rnd.nextInt(N) + 1;
            int b = rnd.nextInt(N) + 1;

            System.out.println("" + a + " " + b);
        }
    }
}
