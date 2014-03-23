import java.io.*;
import java.util.*;

public class IPChecking {
    public static void main(String[] args) {
        new IPChecking().run();
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

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        int T = $r.nextInt();
        for (int ncase = 1; ncase <= T; ncase++) {
            String s1 = $r.next();
            String s2 = $r.next();

            int[] ip1 = splitIPInt(s1);
            int[] ip2 = binaryToDecimal(splitIP(s2));

            $w.println("Case " + ncase + ": "
                       + (ipsEqual(ip1, ip2) ? "Yes" : "No"));
        }

        $w.close();
    }

    boolean ipsEqual(int[] ip1, int[] ip2) {
        for (int i = 0; i < 4; i++)
            if (ip1[i] != ip2[i]) return false;
        return true;
    }

    String p(int[] a) {
        String r = "";
        for (int i=0; i<4; i++) {
            r = r + " " + a[i];
        }
        return r;
    }

    String[] splitIP(String ip) {
        StringTokenizer st = new StringTokenizer(ip, ".");
        String[] octets = new String[4];
        for (int i = 0; i < 4; i++)
            octets[i] = st.nextToken();
        return octets;
    }

    int[] splitIPInt(String ip) {
        String[] octets = splitIP(ip);
        int[] res = new int[4];
        for (int i = 0; i < 4; i++)
            res[i] = Integer.parseInt(octets[i]);
        return res;
    }

    int[] binaryToDecimal(String[] ip) {
        int[] res = new int[4];
        for (int i = 0; i < 4; i++) {
            res[i] = 0;
            int v = 1;
            for (int j = 7; j >= 0; j--) {
                if (ip[i].charAt(j) == '1')
                    res[i] += v;
                v <<= 1;
            }
        }
        return res;
    }
}
