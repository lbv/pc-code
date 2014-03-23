import java.io.*;
import java.util.*;

class EqualizingMoney {
    public static void main(String[] args) {
        new EqualizingMoney().run();
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
    class $G {
        class E { int v, w; E(int V, int W) { v=V; w=W; } }
        class EL extends ArrayList<E> {}
        int n;
        EL[] edg;
        $G(int N) { n=N; edg = new EL[n]; }
        void add(int u, int v, int w) { edges(u).add(new E(v, w)); }
        EL edges(int v) {
            if (edg[v] == null) edg[v] = new EL();
            return edg[v];
        }
        int nEdges(int v) { return edg[v] == null ? 0 : edg[v].size(); }
        int[] pre, dis;
        // Topological sort
        // Tarjan
        class SCC extends ArrayList<Integer> {}
        class SCCL extends ArrayList<SCC> {}
        SCCL sccl;
        Deque<Integer> ts;
        int gCnt;
        int[] gLow, gIdx;
        boolean[] inStack;
        void tarjanSCC() {
            sccl = new SCCL();
            ts = new ArrayDeque<Integer>();
            inStack = new boolean[n];
            gLow = new int[n];
            gIdx = new int[n];
            gCnt = 1;
            for (int i = 0; i<n; i++)
                if (gLow[i] == 0) tarjanVisit(i);
        }
        void tarjanVisit(int v) {
            gIdx[v] = gLow[v] = gCnt++;
            ts.push(v);
            inStack[v] = true;
            for (int i=0, lim=nEdges(v); i<lim; i++) {
                E e = edg[v].get(i);
                if (gLow[e.v] == 0) {
                    tarjanVisit(e.v);
                    gLow[v] = Math.min(gLow[v], gLow[e.v]);
                }
                else if (inStack[e.v])
                    gLow[v] = Math.min(gLow[v], gIdx[e.v]);
            }
            if (gLow[v] == gIdx[v]) {
                SCC scc = new SCC();
                int u;
                do {
                    u = ts.pop();
                    inStack[u] = false;
                    scc.add(u);
                } while (u != v);
                sccl.add(scc);
            }
        }
    }

    $G g;
    int N, M, sum;
    int[] money;

    void run() {
        $R $r = new $R(System.in);
        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            M = $r.nextInt();

            money = new int[N];
            sum = 0;

            for (int i=0; i < N; i++) {
                money[i] = $r.nextInt();
                sum += money[i];
            }

            g = new $G(N);

            for (int i=0; i < M; i++) {
                int u = $r.nextInt() - 1;
                int v = $r.nextInt() - 1;

                g.add(u, v, 0);
                g.add(v, u, 0);
            }

            System.out.println("Case " + ncase + ": " +
                               (canEqualize() ? "Yes" : "No"));
        }
    }

    boolean canEqualize() {
        if (sum % N != 0) return false;
        int mpp = sum / N;  // money per person

        g.tarjanSCC();

        for (int i=0, nScc=g.sccl.size(); i < nScc; i++) {
            $G.SCC scc = g.sccl.get(i);

            int sccMoney = 0;
            for (int j=0, nv=scc.size(); j<nv; j++) {
               int v = scc.get(j);
               sccMoney += money[v];
            }

            if (sccMoney != mpp * scc.size()) return false;
        }

        return true;
    }
}
