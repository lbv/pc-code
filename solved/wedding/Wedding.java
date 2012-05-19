import java.io.*;
import java.util.*;

public class Wedding {
    public static void main(String[] args) {
        new Wedding().run();
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
    class IL extends ArrayList<Integer> {};
    class ILL extends ArrayList<IL> {};
    class IQ extends ArrayDeque<Integer> {};
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
        class EQ extends ArrayDeque<E> {}
        IQ vq; boolean[] col; int[] dis, glow, gidx; int gcnt;
        // Kosaraju's algorithm
        $G _rg; IL _scc;
        ILL kosarajuSSC() {
            col = new boolean[n]; vq = new IQ(); _rg = new $G(n);
            for (int v=0; v<n; v++) if (!col[v]) kosarajuDFS(v);
            Arrays.fill(col, false);
            ILL sccs = new ILL();
            while (!vq.isEmpty()) {
                int v = vq.pop();
                if (col[v]) continue;
                _scc = new IL();
                kosarajuDFS2(v);
                sccs.add(_scc);
            }
            return sccs;
        }
        void kosarajuDFS(int v) {
            col[v] = true;
            for (int i=0; i<out[v]; i++) {
                E e = edge(v, i);
                _rg.add(e.v, e.u, e.w);
                if (!col[e.v]) kosarajuDFS(e.v);
            }
            vq.push(v);
        }
        void kosarajuDFS2(int v) {
            col[v] = true;
            _scc.add(v);
            for (int i=0; i<_rg.out[v]; i++) {
                E e = _rg.edge(v, i);
                if (!col[e.v]) kosarajuDFS2(e.v);
            }
        }
    }
    class $2SAT {
        int n; $G g;
        $2SAT(int N) { n=N; g = new $G(2*n); }
        void addCondition(int a, boolean ta, int b, boolean tb) {
            int p = val(a, ta); int q = val(b, tb);
            g.add(neg(p), q, 0); g.add(neg(q), p, 0); }
        int val(int v, boolean t) { return 2*v + (t ? 0 : 1); }
        int neg(int p) { return p%2==0 ? p+1 : p-1; }
        IL solve() {
            ILL sccs = g.kosarajuSSC();
            int[] vscc = new int[n];
            IL sol = new IL();
            for (int i = 0, ns=sccs.size(); i<ns; i++) {
                IL scc = sccs.get(i);
                for (int j=0, nv=scc.size(); j<nv; j++) {
                    int p = scc.get(j);
                    int v = p/2;
                    if (vscc[v] == i+1) return null;
                    if (vscc[v] != 0) break;
                    vscc[v] = i+1;
                    if ((p & 1) == 1) sol.add(v);
                }
            }
            return sol;
        }
    }

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        while (true) {
            int n = $r.nextInt();  // number of couples
            int m = $r.nextInt();  // number of adulterous couples
            if (n == 0 && m == 0) break;

            $2SAT sat = new $2SAT(2*n);

            // The groom shouldn't be in the answer
            sat.addCondition(0, false, 0, false);

            // The bride must be, although we don't print it
            sat.addCondition(1, true, 1, true);

            // For each couple, one and only one of them should be there
            for (int i = 1; i < n; i++) {
                sat.addCondition(i*2, false, i*2+1, false);
                sat.addCondition(i*2, true, i*2+1, true);
            }

            while (m-- > 0) {
                int a = personStrToInt($r.next());
                int b = personStrToInt($r.next());

                // For an adulterous couple, at least one of them must be at
                // the same side as the bride
                sat.addCondition(a, true, b, true);
            }

            IL sol = sat.solve();

            if (sol == null)
                $w.println("bad luck");
            else {
                boolean first = true;
                for (int i = 0, nv=sol.size(); i < nv; i++) {
                    if (sol.get(i) == 1) continue;
                    if (first) first = false;
                    else $w.print(" ");
                    String p = personIntToStr(sol.get(i));
                    $w.print(p);
                }
                $w.println();
            }
        }
        $w.close();
    }

    int personStrToInt(String s) {
        int len = s.length();
        int n = Integer.parseInt(s.substring(0, len - 1));
        return n*2 + (s.charAt(len-1)=='w' ? 1 : 0);
    }

    String personIntToStr(int p) {
        StringBuilder sb = new StringBuilder();
        sb.append(p/2);
        sb.append((p & 1) == 1 ? 'w' : 'h');
        return sb.toString();
    }
}
