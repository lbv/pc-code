import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();

        int T=110;
        System.out.println(T);
        for (int i = 0; i < T; i++) {
            int n = rnd.nextInt(1000) + 1;
            int m = rnd.nextInt(2001);

            if (n == 1) m = 0;

            System.out.println();
            System.out.println("" + n + " " + m);
            for (int j=0; j < m; j++) {
                int x = rnd.nextInt(n);
                int y = rnd.nextInt(n);
                while (x == y) {
                    y = rnd.nextInt(n);
                }
                int t = rnd.nextInt(2001) - 1000;

                System.out.println("" + x + " " + y + " " + t);
            }
        }
    }
}
