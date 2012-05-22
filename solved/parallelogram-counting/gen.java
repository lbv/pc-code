import java.util.*;

public class gen
{
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();

        int T = 15;
        System.out.println(T);

        while (T-- > 0)
            testCase();
    }

    //final int LIM = 1000000000;
    final int LIM = 50;
    void testCase() {
        int n = rnd.nextInt(10) + 1;

        System.out.println(n);

        while (n-- > 0) {
            int x = rnd.nextInt(LIM);
            int y = rnd.nextInt(LIM);
            System.out.println("" + x + " " + y);
        }
    }
}
