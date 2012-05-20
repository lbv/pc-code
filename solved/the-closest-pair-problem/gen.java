import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;

    void run() {
        int T = 15;
        rnd = new Random();

        while (T-- > 0)
            printTestCase();
        System.out.println("0");
    }

    void printTestCase() {
        int N = rnd.nextInt(10000) + 1;

        System.out.println(N);
        while (N-- > 0) {
            double x = rnd.nextDouble() * 40000;
            double y = rnd.nextDouble() * 40000;

            System.out.println("" + x + " " + y);
        }
    }
}
