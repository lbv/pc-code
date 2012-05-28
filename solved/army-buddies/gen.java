import java.util.*;

public class gen {
    public static void main(String[] args) {
        new gen().run();
    }

    Random rnd;

    void run() {
        rnd = new Random();
        int T = 20;

        for (int i = 0; i < T; i++)
            printTestCase();

        System.out.println("0 0");
    }

    class Range {
        int l, r;
        Range(int L, int R) { l=L; r=R; }
    }

    void printTestCase() {
        int S = rnd.nextInt(100000) + 1;
        int n = rnd.nextInt(S) + 1;

        int[] num = new int[n];
        for (int i = 0; i < n; i++)
            num[i] = rnd.nextInt(S) + 1;

        Arrays.sort(num);
        List<Range> ranges = new ArrayList<Range>();

        for (int i = 0; i < n; ) {
            Range r = new Range(num[i], i + 1 < n ? num[i+1] : num[i]);
            ranges.add(r);
            i += 2;
            while (i < n && num[i] == r.r) i++;
        }
        Collections.shuffle(ranges);
        int B = ranges.size();

        System.out.println("" + S + " " + B);
        for (Range r : ranges) {
            System.out.println("" + r.l + " " + r.r);
        }
    }
}
