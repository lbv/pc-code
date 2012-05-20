import java.io.*;
import java.util.*;

public class SimilarTrees {
    public static void main(String[] args) {
        new SimilarTrees().run();
    }

    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        boolean hasNext() { skip(); return b >= 0; }
        void skip() { while (b >= 0 && b <= 32) read(); }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
        String nextRealLine() {
            StringBuilder sb = new StringBuilder();
            for (; b != 10 && b != 13; read()) sb.append((char)b);
            byte p = b; read();
            if ((p == 10 && b == 13) || (p == 13 && b == 10)) read();
            return sb.toString(); }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    class TL extends ArrayList<Tree> {};
    class IL extends ArrayList<Integer> {};

    class Tree implements Comparable<Tree> {
        TL children;
        IL rep;  // representation of the tree as a list of 1's and 0's
        Tree parent;
        Tree() { children = new TL(); rep = new IL(); }
        void add(Tree child) {
            children.add(child);
            child.parent = this;
        }
        public int compareTo(Tree t) {
            int s1 = rep.size();
            int s2 = t.rep.size();
            if (s1 < s2) return -1;
            if (s1 > s2) return 1;
            for (int i = 0; i < s1; i++) {
                int a = rep.get(i);
                int b = t.rep.get(i);
                if (a < b) return -1;
                if (a > b) return 1;
            }
            return 0;
        }
        String normalize() {
            dfsRep(this);
            StringBuilder sb = new StringBuilder();
            for (int i = 0, n=rep.size(); i < n; i++) {
                int d = rep.get(i);
                sb.append(d);
            }
            return sb.toString();
        }

        void dfsRep(Tree t) {
            if (t.children.size() == 0)
                return;
            for (int i = 0, n=t.children.size(); i < n; i++) {
                Tree c = t.children.get(i);
                dfsRep(c);
            }
            Collections.sort(t.children);
            for (int i = 0, n=t.children.size(); i < n; i++) {
                Tree c = t.children.get(i);
                t.rep.add(1);
                t.rep.addAll(c.rep);
                t.rep.add(0);
            }
        }
        void dfs(Tree t, StringBuilder sb) {
            Collections.sort(t.children);
            for (int i = 0, n=t.children.size(); i < n; i++) {
                Tree c = t.children.get(i);
                sb.append('1');
                dfs(c, sb);
                sb.append('0');
            }
        }
    }

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        $r.nextRealLine();

        for (int ncase = 1; ncase <= T; ncase++) {
            Tree t1 = parseTree($r.nextRealLine());
            Tree t2 = parseTree($r.nextRealLine());

            /*
            System.out.println("Normalized t1: " + t1.normalize());
            System.out.println("Normalized t2: " + t2.normalize());
            */

            $w.println("Case " + ncase + ": "
                       + (t1.normalize().equals(t2.normalize())
                          ? "Same" : "Different" ));
        }

        $w.close();
    }

    Tree parseTree(String s) {
        Tree root, t, aux;
        t = root = new Tree();
        for (int i = 0, len = s.length(); i < len; i++) {
            if (s.charAt(i) == '1') {
                aux = new Tree();
                t.add(aux);
                t = aux;
            }
            else if (s.charAt(i) == '0') {
                t = t.parent;
            }
        }

        return root;
    }
}
