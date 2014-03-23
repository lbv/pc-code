import java.math.BigInteger;
import java.io.*;
import java.util.*;

public class GarblingGame {
    public static void main(String[] args) {
        new GarblingGame().run();
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
        BigInteger nextBigInteger() { return new BigInteger(next()); }
    }
    class $W extends PrintWriter {
        $W() { super(new PrintWriter(new BufferedWriter(
                        new FileWriter(FileDescriptor.out)))); }
    }
    class Pos {
        int r, c;
        Pos(int R, int C) { r=R; c=C; }
        boolean eq(Pos p) { return r==p.r && c==p.c; }
        boolean eq(int R, int C) { return r==R && c==C; }
        public String toString() { return String.format("(%d,%d)", r, c); }
    }
    class $Matrix {
        int r, c;
        $Matrix(int R, int C) { r=R; c=C; }
        int cells() { return c*r; }
        void move(Pos p) {
            if (++p.c >= c) {
                p.c = 0;
                if (++p.r == r) p.r = 0;
            }
        }
        int posToScalar(Pos p) { return p.r*c + p.c; }
        Pos scalarToPos(int sp) { return new Pos(sp/c, sp%c); }
    }

    int R, C, S;
    BigInteger N;
    char[][] gmap;
    $Matrix $g, $n;
    $R $r;
    void run() {
        $r = new $R(System.in);
        $W $w = new $W();
        boolean firstCase = true;
        while ($r.hasNext()) {
            R = $r.nextInt();
            C = $r.nextInt();
            N = $r.nextBigInteger();

            S = R*C;
            gmap = new char[R-1][C-1];
            $n = new $Matrix(R, C);
            $g = new $Matrix(R-1, C-1);
            for (int i = 0; i < R - 1; i++)
                gmap[i] = $r.nextLine().toCharArray();
            if (firstCase) firstCase = false;
            else $w.println();

            preparations();

            for (int i = 0; i < S; i++)
                $w.println(TB[i]);
        }
        $w.close();
    }

    class Writes extends ArrayList<Integer> {}

    final int MOD = 100000;
    int[][] A, B;
    int K;
    int[] TA, TB;
    int[] posMap, writeMap, whois;
    int turn;
    Writes writes;
    void preparations() {
        posMap = initPosArray();
        whois = initPosArray();
        writeMap = new int[S];

        turn = 0;
        writes = new Writes();

        BigInteger GS = BigInteger.valueOf($g.cells());
        int limit = N.compareTo(GS) > 0 ? $g.cells() : N.intValue();

        for (int i = 0; i < limit; i++, turn++)
            processTurn();

        BigInteger rounds = N.divide(GS);

        if (rounds.compareTo(BigInteger.ZERO) > 0) {
            A = new int[2][S];
            B = new int[2][S];
            K = 0;
            A[K] = posMap;
            B[K] = writeMap;
        }

        BigInteger roundsToUse = BigInteger.ONE;
        TA = initPosArray();
        TB = new int[S];
        while (rounds.compareTo(BigInteger.ZERO) > 0) {
            if (rounds.testBit(0))
                addToTotals();
            roundsToUse = roundsToUse.shiftLeft(1);
            rounds = rounds.shiftRight(1);
            nextCalc();
        }
        int remTurns = N.mod(GS).intValue();
        countWrites(remTurns);
    }

    int[] initPosArray() {
        int[] a = new int[S];
        for (int i = 0; i < S; i++)
            a[i] = i;
        return a;
    }

    void nextCalc() {
        int K1 = (K + 1) % 2;
        final int[] A0 = A[K];
        final int[] A1 = A[K1];
        final int[] B0 = B[K];
        final int[] B1 = B[K1];
        for (int i = 0; i < S; i++) {
            int l = A0[i];
            A1[i] = A0[l];
            B1[i] = (B0[i] + B0[l]) % MOD;
        }
        K = K1;
    }

    void addToTotals() {
        final int[] A0 = A[K];
        final int[] B0 = B[K];
        for (int i = 0; i < S; i++) {
            int l = TA[i];
            TA[i] = A0[l];
            TB[i] = (TB[i] + B0[l]) % MOD;
        }
    }

    void processTurn() {
        Pos p = $g.scalarToPos(turn);
        int o = $n.posToScalar(p);
        int e = $n.posToScalar(new Pos(p.r, p.c+1));
        int s = $n.posToScalar(new Pos(p.r+1, p.c));
        int se = $n.posToScalar(new Pos(p.r+1, p.c+1));
        writes.add(whois[o]);
        writeMap[whois[o]]++;
        if (gmap[p.r][p.c] == 'L') {
            posMap[whois[o]] = s;
            posMap[whois[s]] = se;
            posMap[whois[se]] = e;
            posMap[whois[e]] = o;
            int n = whois[o];
            whois[o] = whois[e];
            whois[e] = whois[se];
            whois[se] = whois[s];
            whois[s] = n;
            return;
        }
        if (gmap[p.r][p.c] == 'R') {
            posMap[whois[o]] = e;
            posMap[whois[e]] = se;
            posMap[whois[se]] = s;
            posMap[whois[s]] = o;
            int n = whois[o];
            whois[o] = whois[s];
            whois[s] = whois[se];
            whois[se] = whois[e];
            whois[e] = n;
        }
    }

    void countWrites(int turns) {
        int[] W = new int[S];
        for (int i = 0; i < turns; i++) {
            int l = writes.get(i);
            W[l]++;
        }

        for (int i = 0; i < S; i++) {
            int l = TA[i];
            TB[i] = (TB[i] + W[l]) % MOD;
        }
    }
}
