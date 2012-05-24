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
        int n = rnd.nextInt(10000000 - 4) + 4;
        n = (n>>1)<<1;
        System.out.println(n);
    }
}
