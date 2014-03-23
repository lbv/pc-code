import java.io.*;
import java.text.*;
import java.util.*;

public class TheClosestPair {
    public static void main(String[] args) {
        new TheClosestPair().run();
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
        double nextDouble() { return Double.parseDouble(next()); }
    }
    class $W extends PrintWriter {
        $W() { super(new BufferedOutputStream(System.out)); }
    }

    class Point {
        double x, y;
        Point(double X, double Y) {x=X; y=Y;}
        double distance(Point p) {
            double dx = p.x - x;
            double dy = p.y - y;
            return Math.sqrt(dx*dx + dy*dy);
        }
    }

    final Comparator<Point> compX = new Comparator<Point>() {
        public int compare(Point a, Point b) {
            return a.x < b.x ? -1 : (a.x > b.x ? 1 : 0);
        }
    };
    final Comparator<Point> compY = new Comparator<Point>() {
        public int compare(Point a, Point b) {
            return a.y < b.y ? -1 : (a.y > b.y ? 1 : 0);
        }
    };

    final DecimalFormat df =
        (DecimalFormat)NumberFormat.getNumberInstance(Locale.US);

    final double INF = 10000.0;
    Point[] points;
    double dist;
    int N;

    void run() {
        $R $r = new $R(System.in);
        $W $w = new $W();

        df.applyPattern("0.0000");

        while (true) {
            N = $r.nextInt();
            if (N == 0) break;

            points = new Point[N];
            for (int i = 0; i < N; i++) {
                double x = $r.nextDouble();
                double y = $r.nextDouble();
                points[i] = new Point(x, y);
            }

            solve();

            if (dist < INF)
                $w.println(df.format(dist));
            else
                $w.println("INFINITY");

        }

        $w.close();
    }

    class PointTree extends TreeSet<Point> {
        PointTree() { super(compY); }
    }

    void solve() {
        Arrays.sort(points, compX);
        dist = INF;  // minimum distance so far (squared)
        Point a, b;
        PointTree tree = new PointTree();
        tree.add(points[0]);
        int least = 0;  // index of the lowest (by X) point in tree

        for (int i = 1; i < N; i++) {
            Point p = points[i];

            while (p.x - points[least].x > dist)
                tree.remove(points[least++]);

            Point from = new Point(p.x, p.y - dist);
            Point to = new Point(p.x, p.y + dist);
            for (Point cp : tree.subSet(from, to)) {
                double d = p.distance(cp);
                if (d < dist)
                    dist = d;
            }

            tree.add(p);
        }
    }
}
