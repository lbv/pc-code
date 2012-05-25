import java.io.*;
import java.util.*;

class FormingTheCouncil {
    public static void main(String[] args) {
        new FormingTheCouncil().run();
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
        class VL extends ArrayList<Integer> {}
        VL topoSort() {
            int[] in = new int[n];
            for (int i = 0; i<n; i++)
                for (int j = 0, ne = nEdges(i); j<ne; j++) {
                    E e = edg[i].get(j);
                    in[e.v]++;
                }
            Deque<Integer> q = new ArrayDeque<Integer>();
            for (int i = 0; i < n; i++)
                if (in[i] == 0) q.add(i);
            VL res = new VL();
            while(!q.isEmpty()) {
                int v = q.remove();
                res.add(v);
                for (int i=0, ne=nEdges(v); i<ne; i++) {
                    E e = edg[v].get(i);
                    in[e.v]--;
                    if (in[e.v] == 0)
                        q.add(e.v);
                }
            }
            return res;
        }
        // Tarjan
        class SCC extends ArrayList<Integer> {}
        class SCCL extends ArrayList<SCC> {}
        SCCL sccl;
        Deque<Integer> ts;
        int tn;
        int[] tLow, tIdx;
        boolean[] inStack;
        void tarjan() {
            sccl = new SCCL();
            ts = new ArrayDeque<Integer>();
            inStack = new boolean[n];
            tLow = new int[n];
            tIdx = new int[n];
            tn = 1;
            for (int i = 0; i<n; i++)
                if (tLow[i] == 0) tarjanVisit(i);
        }
        void tarjanVisit(int v) {
            tIdx[v] = tLow[v] = tn++;
            ts.push(v);
            inStack[v] = true;
            for (int i=0, lim=nEdges(v); i<lim; i++) {
                E e = edg[v].get(i);
                if (tLow[e.v] == 0) {
                    tarjanVisit(e.v);
                    tLow[v] = Math.min(tLow[v], tLow[e.v]);
                }
                else if (inStack[e.v])
                    tLow[v] = Math.min(tLow[v], tIdx[e.v]);
            }
            if (tLow[v] == tIdx[v]) {
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
        $G scclDag;
        void tarjanDAG() {
            int nSccl = sccl.size();
            int[] vComp = new int[n];
            for (int i=0; i<nSccl; i++) {
                SCC scc = sccl.get(i);
                for (int j=0, lim=scc.size(); j<lim; j++) {
                    int v = scc.get(j);
                    vComp[v] = i;
                }
            }
            scclDag = new $G(nSccl);
            for (int u=0; u < n; u++)
                for (int i=0, lim=nEdges(u); i<lim; i++) {
                    E e = edg[u].get(i);
                    if (vComp[u] != vComp[e.v])
                        scclDag.add(vComp[u], vComp[e.v], 0);
                }
        }
    }

    int N, M;
    $G g;

    void run() {
        $R $r = new $R(System.in);
        int T = $r.nextInt();

        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();
            M = $r.nextInt();

            g = new $G(M*2);

            for (int i=0; i<N; i++) {
                int a = vertexNum($r.next());
                int b = vertexNum($r.next());

                g.add(neg(a), b, 0);
                g.add(neg(b), a, 0);
            }

            g.tarjan();
            g.tarjanDAG();

            System.out.print("Case " + ncase + ": ");
            if (findSolution()) {
                System.out.println("Yes");
                System.out.print(nAccept);
                for (int i=0; i < M; i++) {
                    if (accept[i])
                        System.out.print(" " + (i+1));
                }
                System.out.println();
            }
            else
                System.out.println("No");
        }
    }

    int vertexNum(String node) {
        int v = Integer.parseInt(node.substring(1)) - 1;
        v <<= 1;
        if (node.charAt(0) == '-') v |= 1;
        return v;
    }

    int neg(int v) { return v^1; }

    boolean[] accept;
    int nAccept;

    boolean findSolution() {
        $G.VL ts = g.scclDag.topoSort();
        int[] vScc = new int[M];
        accept = new boolean[M];

        Arrays.fill(vScc, -1);
        nAccept = 0;

        for (int i=0, nScc=ts.size(); i<nScc; i++) {
            int dagv = ts.get(i);
            $G.SCC scc = g.sccl.get(dagv);

            for (int j=0, nv=scc.size(); j<nv; j++) {
                int v = scc.get(j);
                int p = v >> 1;
                boolean isNeg = (v & 1) == 1;

                if (vScc[p] == dagv) return false;
                if (vScc[p] >= 0) break;
                vScc[p] = dagv;
                if (isNeg) {
                    accept[p] = true;
                    nAccept++;
                }
            }
        }
        return true;
    }
}

