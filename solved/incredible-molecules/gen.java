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

    int coord() {
        return rnd.nextInt(1999) - 999;
    }

    void testCase() {
        int x1 = coord();
        int y1 = coord();
        int r1 = rnd.nextInt(999) + 1;

        int x2 = coord();
        int y2 = coord();
        int r2 = rnd.nextInt(999) + 1;

        System.out.println("" + x1 + " " + y1 + " " + r1 + " " + x2 + " " + y2 + " " + r2);
    }
}
