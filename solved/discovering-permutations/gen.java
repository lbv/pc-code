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
        int N = rnd.nextInt(26) + 1;
        int K = rnd.nextInt(30) + 1;

        System.out.println("" + N + " " + K);
    }
}
