import java.io.*;
import java.util.*;

class WordPuzzle {
    public static void main(String[] args) {
        new WordPuzzle().run();
    }

    class $R {
        InputStream in; byte b; byte[] buf; int bi, bz;
        $R(InputStream I) { in=I; buf=new byte[65536]; bi=bz=0; read(); }
        boolean hasNext() { skip(); return b >= 0; }
        void skip() { while (b >= 0 && b <= 32) read(); }
        String next() {
            StringBuilder sb = new StringBuilder();
            for (skip(); b > 32; read()) sb.append((char)b);
            return sb.length() == 0 ? null : sb.toString(); }
        String nextLine() {
            StringBuilder sb = new StringBuilder();
            for (; b != 10 && b != 13; read()) sb.append((char)b);
            while (b == 10 || b == 13) read(); return sb.toString(); }
        int nextInt() {
            int i=0; boolean s=false; skip();
            if (b == '-') { s=true; read(); }
            for (; b > 32; read()) i = i*10 + b-48; return s ? -i : i; }
        void read() {
            if (bi==bz) {
                bi=0; try { bz=in.read(buf); } catch(Exception e) { bz=-1; } }
            b = bz == -1 ? -1 : buf[bi++];  }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }
    class $G {
        class E { int u, v, w; E(int U, int V, int W) { u=U; v=V; w=W; } }
        class EL extends ArrayList<E> { EL(){super();} EL(int c){super(c);} }
        EL ae; EL[] ve; int[] in, out; int n, m;
        $G(int N) { n=N; init(); } $G(int N, int M) { n=N; m=M; init(); }
        void init() {
            ae = m==0 ? new EL() : new EL(m);
            ve = new EL[n]; out = new int[n]; in = new int[n]; }
        void add(int u, int v, int w) {
            E e = new E(u, v, w);
            ae.add(e); check(u).add(e); out[u]++; in[v]++; }
        void addm(int u, int v, int w) { add(u, v, w); m++; }
        EL check(int v) { return ve[v] == null ? (ve[v]=new EL()) : ve[v]; }
        E edge(int v, int i) { return ve[v].get(i); }
        // Auxiliary types/attr
        class VL extends ArrayList<Integer> {}
        class VLL extends ArrayList<VL> {}
        class VQ extends ArrayDeque<Integer> {}
        class EQ extends ArrayDeque<E> {}
        VQ vq; boolean[] col; int[] dis, glow, gidx; int gcnt;
        // Euler trails
        VL _trail; EQ[] _adjq;
        VL eulerTrail() {
            _adjq = new EQ[n];
            int nOdd = 0, start = 0;
            for (int u = 0; u < n; u++) {
                _adjq[u] = new EQ();
                if (start == 0 && out[u] > 0) start = u;
                for (int i = 0; i < out[u]; i++)
                    _adjq[u].add(edge(u, i));
            }
            for (int v = 0; v < n; v++) {
                int diff = Math.abs(in[v] - out[v]);
                if (diff > 1) return null;
                if (diff == 1) {
                    if (++nOdd > 2) return null;
                    if (out[v] > in[v]) start = v;
                }
            }
            _trail = new VL();
            eulerBuildTrail(start);
            Collections.reverse(_trail);
            return _trail;
        }
        void eulerBuildTrail(int u) {
            while(! _adjq[u].isEmpty()) {
                E e = _adjq[u].remove();
                eulerBuildTrail(e.v);
            }
            _trail.add(u);
        }
    }

    class WordQueue extends ArrayDeque<String> {}

    int N;
    $G g;
    WordQueue[][] words;  // words indexed by first and last letter

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();

            g = new $G(26);
            words = new WordQueue[26][26];

            for (int i = 0; i < N; i++) {
                String node = $r.next();

                int first = (int) node.charAt(0) - 'a';
                int last = (int) node.charAt(node.length() - 1) - 'a';

                addWord(first, last, node);

                g.addm(first, last, 0);
            }

            $G.VL trail = g.eulerTrail();
            $w.print("Case " + ncase + ": ");

            if (trail == null || trail.size() != N + 1)
                $w.println("No");
            else {
                $w.println("Yes");
                int pre = trail.get(0);
                boolean firstPrint = true;
                for (int i = 1, nv = trail.size(); i < nv; i++) {
                    int cur = trail.get(i);
                    String w = getWord(pre, cur);
                    if (w == null) break;

                    if (firstPrint) firstPrint = false;
                    else $w.print(' ');
                    $w.print(w);
                    pre = cur;
                }
                $w.println();
            }
        }

        $w.close();
    }

    void addWord(int first, int last, String w) {
        if (words[first][last] == null)
            words[first][last] = new WordQueue();
        words[first][last].add(w);
    }

    String getWord(int first, int last) {
        if (words[first][last] == null || words[first][last].isEmpty())
            return null;
        return words[first][last].remove();
    }
}
