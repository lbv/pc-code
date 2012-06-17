public class TwoSat {
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
}
