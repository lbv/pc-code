import java.util.*;

public class Geometry {
    class Segment {
        Point a, b;
        Segment(Point A, Point B) { a=A; b=B; }
        Point raySegmentIntersection(Segment s) {
            Line l1 = new Line(a, b);
            Line l2 = new Line(s.a, s.b);
            if (l1.isParallel(l2)) return null;
            Point in = l1.intersection(l2);
            int dirXa = (int)Math.signum(b.x-a.x);
            int dirYa = (int)Math.signum(b.y-a.y);
            int dirXb = (int)Math.signum(a.x-in.x);
            int dirYb = (int)Math.signum(a.y-in.y);
            if (dirXa == -dirXb && dirYa == -dirYb
                && in.inBox(s.a, s.b)) return in;
            return null;
        }
        public String toString() { return String.format("%s-%s", a, b); }
    }
}
