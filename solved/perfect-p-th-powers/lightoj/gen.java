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
        int x = 0;
        while (Math.abs(x) < 2)
            x = rnd.nextInt();
        System.out.println(x);
    }
}
