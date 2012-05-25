import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;
    void run() {
        rnd = new Random();

        int T = 15;

        System.out.println(T);
        for (int i = 0; i < T; i++) {
            int n = rnd.nextInt(20000) + 1;
            int m = rnd.nextInt(8000) + 1;

            System.out.println("" + n + " " + m);
            for (int j = 0; j<n; j++) {
                int a = rnd.nextInt(m) + 1;
                int b = rnd.nextInt(m) + 1;

                boolean ba = rnd.nextBoolean();
                boolean bb = rnd.nextBoolean();
                System.out.printf("%s%d %s%d\n", ba ? "+" : "-", a, bb ? "+" : "-", b);
            }
        }
    }
}
