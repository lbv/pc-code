import java.util.*;

public class BusinessCenter {
    public static void main(String[] args) {
        new BusinessCenter().run();
    }

    class Node {
        int min, max, x;
        Node(int Min, int Max, int X) { min=Min; max=Max; x=X; }
    }
    Scanner scn;
    int n, m;
    int u, d;
    void run() {
        scn = new Scanner(System.in);
        while (scn.hasNextInt()) {
            n = scn.nextInt();
            m = scn.nextInt();
            int min = Integer.MAX_VALUE;
            for (int i = 0; i < m; i++) {
                u = scn.nextInt();
                d = scn.nextInt();
                int answer = search(new Node(0, n, n/2));
                if (answer < min) min = answer;
            }
            System.out.println(min);
        }
    }
    int search(Node initial) {
        Queue<Node> q = new LinkedList<Node>();
        q.add(initial);
        while (!q.isEmpty()) {
            Node nd = q.remove();
            int f = fun(nd.x);
            if (f <= 0) {
                q.add(new Node(nd.x+1, nd.max, nd.x + 1 + (nd.max-nd.x)/2));
                continue;
            }
            if (fun(nd.x-1) <= 0) {
                return f;
            }
            q.add(new Node(nd.min, nd.x-1, nd.x - 1 - (nd.x-nd.min)/2));
        }
        return -1;
    }
    int fun(int x) {
        return u*x - d*(n-x);
    }
}
