import java.util.*;

public class Headshot {
    public static void main(String[] args) {
        new Headshot().run();
    }

    Scanner scn;
    void run() {
        scn = new Scanner(System.in);
        while (scn.hasNextLine()) {
            String ln = scn.nextLine();
            if (ln.isEmpty()) break;

            System.out.println(solution(ln));
        }
    }

    String solution(String data) {
        int t1, to, s1, so;
        t1 = to = s1 = so = 0;
        for (int i = 0; i < data.length(); i++) {
            char cur = data.charAt(i);
            char nxt = data.charAt((i+1) % data.length());
            to++;
            if (cur == '1')
                t1++;
            else {
                so++;
                if (nxt == '1') s1++;
            }
        }
        double pt = (double)t1/to;
        double ps = so == 0 ? 1 : (double)s1/so;
        return pt > ps ? "SHOOT" : (pt < ps ? "ROTATE" : "EQUAL");
    }
}
