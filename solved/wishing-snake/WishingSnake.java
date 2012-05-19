import java.io.*;
import java.util.*;

class WishingSnake {
    public static void main(String[] args) {
        new WishingSnake().run();
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
    class $W extends PrintWriter {
        $W() { super(new PrintWriter(new BufferedWriter(
                        new FileWriter(FileDescriptor.out)))); }
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
        $G tarjanDAG() {
            int nSccl = sccl.size();
            int[] vComp = new int[n];
            for (int i=0; i<nSccl; i++) {
                SCC scc = sccl.get(i);
                for (int j=0, lim=scc.size(); j<lim; j++) {
                    int v = scc.get(j);
                    vComp[v] = i;
                }
            }
            $G dag = new $G(nSccl);
            for (int u=0; u < n; u++)
                for (int i=0, lim=nEdges(u); i<lim; i++) {
                    E e = edg[u].get(i);
                    if (vComp[u] != vComp[e.v])
                        dag.add(vComp[u], vComp[e.v], 0);
                }
            return dag;
        }
    }

    int N;
    $G g;
    boolean[] board;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            N = $r.nextInt();

            g = new $G(1000);
            board = new boolean[1000];

            for (int i = 0; i < N; i++) {
                int K = $r.nextInt();

                for (int j = 0; j < K; j++) {
                    int u = $r.nextInt();
                    int v = $r.nextInt();

                    g.add(u, v, 0);
                    board[u] = board[v] = true;
                }
            }

            $w.println("Case " + ncase + ": "
                       + (possible() ? "YES" : "NO"));
        }

        $w.close();
    }

    boolean possible() {
        int vBoard = 0;
        for (int i = 0; i < 1000; i++)
            if (board[i]) vBoard++;

        g.tarjanSCC();
        int v = initialSCC();  // Get the SCC where the first vertex is
        $G dag = g.tarjanDAG();

        int vertices = 0;
        while (true) {
            vertices += g.sccl.get(v).size();

            int ne = dag.nEdges(v);
            if (ne > 1) return false;
            if (ne == 1)
                v = dag.edg[v].get(0).v;
            else
                break;
        }
        return vertices == vBoard;
    }

    int initialSCC() {
        for (int i = 0, nScc=g.sccl.size(); i < nScc; i++) {
            $G.SCC scc = g.sccl.get(i);

            for (int j =0, nv=scc.size(); j < nv; j++) {
                int v = scc.get(j);
                if (v == 0) return i;
            }
        }
        return -1;
    }
}
