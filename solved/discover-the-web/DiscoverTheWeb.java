import java.io.*;
import java.util.*;

class DiscoverTheWeb {
    public static void main(String[] args) {
        new DiscoverTheWeb().run();
    }

    class $R {
        BufferedReader r;
        StringTokenizer s;
        $R(InputStream in) {
            r = new BufferedReader(new InputStreamReader(in));
            s = new StringTokenizer("");
        }
        String gets() {
            try { return r.readLine(); } catch(Exception e) { return null; } }
        String nextLine() {
            return s.hasMoreTokens() ? s.nextToken("") : gets(); }
        boolean hasNext() {
            while (!s.hasMoreTokens()) {
                String ln = gets();
                if (ln == null) return false;
                s = new StringTokenizer(ln);
            }
            return true;
        }
        String next() { return hasNext() ? s.nextToken() : null; }
        int nextInt() { return Integer.parseInt(next()); }
    }

    class WebStack extends ArrayDeque<String> {}

    void run() {
        $R $r = new $R(System.in);
        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            String command = "";
            WebStack fw = new WebStack();  // forward stack
            WebStack bw = new WebStack();  // backward stack
            String current = "http://www.lightoj.com/";  // current url

            System.out.println("Case " + ncase + ":");

            while (! command.equals("QUIT")) {
                command = $r.next();

                if (command.equals("VISIT")) {
                    bw.push(current);
                    current = $r.next();
                    fw.clear();
                    System.out.println(current);
                    continue;
                }

                if (command.equals("BACK")) {
                    if (bw.size() == 0)
                        System.out.println("Ignored");
                    else {
                        fw.push(current);
                        current = bw.pop();
                        System.out.println(current);
                    }
                    continue;
                }

                if (command.equals("FORWARD")) {
                    if (fw.size() == 0)
                        System.out.println("Ignored");
                    else {
                        bw.push(current);
                        current = fw.pop();
                        System.out.println(current);
                    }
                }
            }
        }
    }
}

