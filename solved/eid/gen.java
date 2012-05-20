import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;

    void run() {
        rnd = new Random();
        int T = 200;
        System.out.println(T);

        while (T-- > 0)
            testCase();
    }

    void testCase() {
        int n = rnd.nextInt(999) + 2;
        System.out.println(n);

        boolean flg = true;
        while (n-- > 0) {
            if (flg) flg = false;
            else System.out.print(" ");
            int x = rnd.nextInt(10000) + 1;
            System.out.print(x);
        }
        System.out.println();
    }
}
