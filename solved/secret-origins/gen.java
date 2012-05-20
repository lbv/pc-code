import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();

        int T = 100000;
        System.out.println(T);

        for (int i = 1; i <= T; ++i)
            System.out.println(i);


        //while (T-- > 0)
        //    testCase();
    }

    final int LIM = 1000000000;
    void testCase() {
        int m = rnd.nextInt(LIM) + 1;
        System.out.println(m);
    }
}
