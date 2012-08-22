import java.util.*;

public class Geometry {
    @interface _n {}
    class NumUtil {
        final @_n double E = 1e-5;
        @_n double diff(@_n double a, @_n double b){ return Math.abs(a-b); }
        boolean eq(@_n double a, @_n double b) { return diff(a, b) <= E; }
        boolean nz(@_n double n) { return diff(n, 0) > E; }
    }
    final NumUtil _N = new NumUtil();
    class Point {
        @_n double x, y;
        Point(@_n double X, @_n double Y) { x = X; y = Y; }
        @_n double distance(Point p) {
            @_n double dx = p.x - x;
            @_n double dy = p.y - y;
            return Math.sqrt(dx*dx + dy*dy);
        }
        boolean inBox(Point p, Point q) {
            return x >= Math.min(p.x, q.x)-_N.E && x <= Math.max(p.x, q.x)+_N.E
                && y >= Math.min(p.y, q.y)-_N.E && y <= Math.max(p.y, q.y)+_N.E;
        }
        public String toString() { return String.format("(%g,%g)", x, y); }
    }
    class Line {
        @_n double a, b, c;  // ax + by + c = 0
        Line(@_n double A, @_n double B, @_n double C) { a=A; b=B; c=C; }
        Line(Point p1, Point p2) {
            if (_N.eq(p1.x, p2.x)) { a = 1; b = 0; c = -p1.x; }
            else { a = (p1.y-p2.y)/(p2.x-p1.x); b = 1; c = -a*p1.x - p1.y; }
        }
        Line(Point p, @_n double m) { a = -m; b = 1; c = m*p.x-p.y; }
        boolean isParallel(Line l) { return _N.eq(a, l.a) && _N.eq(b, l.b); }
        boolean isSame(Line l) { return isParallel(l) && _N.eq(c, l.c); }
        boolean isVertical() { return !_N.nz(b); }
        boolean isHorizontal() { return !_N.nz(a); }
        Point intersection(Line l) {
            if (isParallel(l)) return null;
            @_n double x = (l.b*c - b*l.c) / (l.a*b - a*l.b);
            Line rl = isVertical() ? l : this;
            return new Point(x, -(rl.a * x + rl.c) / rl.b);
        }
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
        Point intersection(Segment s) {
            Line l1 = new Line(a, b);
            Line l2 = new Line(s.a, s.b);
            if (l1.isParallel(l2)) return null;
            Point in = l1.intersection(l2);
            if (in.inBox(a, b) && in.inBox(s.a, s.b)) return in;
            return null;
        }
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
