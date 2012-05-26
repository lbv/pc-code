import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        int T = 5000;
        System.out.println(T);

        for (int n = 1000000000, i = 0; i < 500; ++i, ++n)
            for (int m = 0, j = 0; j < 10; ++j, ++m)
                System.out.println("" + n + " " + m);
        /*
        rnd = new Random();

        int T = 5000;
        System.out.println(T);

        while (T-- > 0)
            testCase();
            */
    }

    final int LIM = 1 << 30;
    void testCase() {
        int n = rnd.nextInt(LIM) + 1;
        int m = rnd.nextInt(LIM);

        System.out.println("" + n + " " + m);
    }
}
