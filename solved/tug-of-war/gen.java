import java.util.*;

public class gen {
    public static void main(String[] args) {
        int cases = 50;

        System.out.println(cases);
        for (int i = 0; i < cases; i++) {
            printCase();
        }
    }

    static void printCase() {
        Random rnd = new Random();

        System.out.println();
        int N = rnd.nextInt(99) + 2;
        System.out.println(N);
        int max = 100000 / N;

        for (int i = 0; i < N; i++) {
            int w = rnd.nextInt(max) + 1;
            System.out.println(w);
        }
    }
}
