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
        System.out.println(bigNumber() + " " + bigNumber());
    }

    String bigNumber() {
        int digits = rnd.nextInt(10000) + 1;
        StringBuilder sb = new StringBuilder();
        int d = rnd.nextInt(9) + 1;
        sb.append(d);
        for (int i = 1; i < digits; i++) {
            d = rnd.nextInt(10);
            sb.append(d);
        }

        return sb.toString();
    }
}
