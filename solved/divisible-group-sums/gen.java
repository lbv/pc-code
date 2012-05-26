import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();

        int T = 20;
        System.out.println(T);

        while (T-- > 0)
            testCase();
    }

    void testCase() {
        int N = rnd.nextInt(200) + 1;
        int Q = rnd.nextInt(10) + 1;
        System.out.println("" + N + " " + Q);

        while (N-- > 0)
            System.out.println(rnd.nextInt());
        while (Q-- > 0) {
            int D = rnd.nextInt(20) + 1;
            int M = rnd.nextInt(10) + 1;
            System.out.println("" + D + " " + M);
        }
    }
}
