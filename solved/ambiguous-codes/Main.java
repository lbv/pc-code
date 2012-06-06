import java.util.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    Scanner scn;
    String[] words;
    int N;

    void run() {
        Scanner scn = new Scanner(System.in);
        while (true) {
            N = scn.nextInt();
            if (N == 0)
                break;

            scn.nextLine();
            words = new String[N];
            for (int i = 0; i < N; i++) {
                words[i] = scn.nextLine();
            }

            System.out.println(ambiguous());
        }
    }

    class Node implements Comparable<Node>{
        String s;
        int c;

        public Node(String s, int c) {
            this.s = s;
            this.c = c;
        }

        public int compareTo(Node o) {
            if (c < o.c) return -1;
            if (c > o.c) return 1;
            return 0;
        }
    }

    int ambiguous() {
        Queue<Node> q = new PriorityQueue<Node>();
        Set<String> visited = new HashSet<String>();

        Node res;

        for (int i = 1; i < N; i++) {
            for (int j = 0; j < i; j++) {
                res = checkCommonPrefix(words[i], words[j]);
                if (res != null)
                    q.add(res);
            }
        }

        while (! q.isEmpty()) {
            Node n = q.remove();
            if (n.s.equals(""))
                return n.c;

            visited.add(n.s);
            for (int i = 0; i < N; i++) {
                res = checkCommonPrefix(n.s, words[i]);
                if (res == null || visited.contains(res.s))
                    continue;
                q.add(this.new Node(res.s, n.c + res.c));
            }
        }

        return -1;
    }

    Node checkCommonPrefix(String s1, String s2) {
        String aux;
        if (s1.length() > s2.length()) {
            aux = s1;
            s1 = s2;
            s2 = aux;
        }
        if (s2.startsWith(s1)) {
            return this.new Node(s2.substring(s1.length()), s1.length());
        }
        return null;
    }
}
