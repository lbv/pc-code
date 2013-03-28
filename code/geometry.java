import java.util.*;

public class Geometry {
    @interface _n {}
    class NumUtil {
        final @_n double E = 1e-5;
        @_n double diff(@_n double a, @_n double b){ return Math.abs(a-b); }
        boolean eq(@_n double a, @_n double b) { return diff(a, b) <= E; }
        boolean nz(@_n double n) { return diff(n, 0) > E; }
    }
    class Line {
        @_n double a, b, c;  // ax + by + c = 0
        Point closestTo(Point p) {
            if (isVertical()) return new Point(-c, p.y);
            if (isHorizontal()) return new Point(p.x, -c);
            return intersection(new Line(p, 1/a));
        }
    }
    class Circle {
        @_n double x, y, r;
        Circle(@_n double X, @_n double Y, @_n double R) { x=X; y=Y; r=R; }
        Point[] tangentPoints(Point p) {
            @_n double pox = x - p.x;
            @_n double poy = y - p.y;
            @_n double h2 = pox*pox + poy*poy;
            @_n double s = Math.sqrt(h2 - r*r);
            Point[] res = {
                new Point(p.x + s*(pox*s-poy*r)/h2, p.y + s*(poy*s+pox*r)/h2),
                new Point(p.x + s*(pox*s+poy*r)/h2, p.y + s*(poy*s-pox*r)/h2)
            };
            return res;
        }
        public String toString() { return String.format("(%g,%g:%g)", x, y, r); }
    }
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
