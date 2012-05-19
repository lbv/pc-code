import java.math.BigInteger;
import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    void run() {
        Random rnd = new Random();
        int T = 10;

        for (int k = 0; k < T; k++) {
            int r = rnd.nextInt(299) + 2;
            int c = rnd.nextInt(299) + 2;
            int n0 = rnd.nextInt(Integer.MAX_VALUE);
            BigInteger n = BigInteger.valueOf(n0).multiply(
                BigInteger.TEN.pow(100).divide(
                    BigInteger.valueOf(Integer.MAX_VALUE)));

            System.out.println("" + r + " " + c + " " + n);

            for (int i = 0; i < r-1; i++) {
                for (int j = 0; j < c-1; j++) {
                    int l = rnd.nextInt(3);
                    char ch = l == 0 ? 'L' : ( l == 1 ? 'R' : 'N');
                    System.out.print(ch);
                }
                System.out.println();
            }
        }
    }
}
