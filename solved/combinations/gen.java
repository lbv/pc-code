import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();

        int T = 1000;
        System.out.println(T);

        while (T-- > 0)
            testCase();
    }

    void testCase() {
        int n = rnd.nextInt(1000000) + 1;
        int k = rnd.nextInt(n);

        System.out.println("" + n + " " + k);
    }
}
