import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();
        int T = 5000;

        System.out.println(T);

        while (T-- > 0)
            testCase();
    }

    final int LIM = 1000000000;
    void testCase() {
        int r1 = rnd.nextInt(LIM) + 1;
        int c1 = rnd.nextInt(LIM) + 1;
        int r2 = rnd.nextInt(LIM) + 1;
        int c2 = rnd.nextInt(LIM) + 1;

        System.out.println("" + r1 + " " + c1 + " " + r2 + " " + c2);
    }
}
