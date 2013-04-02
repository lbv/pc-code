//
// Geometry
//
double circle_angle(double a) { return a >= 0 ? a : Pi2 + a; }
bool eps_less(double a, double b) { return b - a > EPS; }
bool eps_equal(double a, double b) { return fabs(a - b) < EPS; }
double heron(double a, double b, double c)
{
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

template <typename T>
struct Point {
    T x, y;
    Point() { x=y=0; }
    Point(T X, T Y) : x(X), y(Y) {}
    T distance(const Point &p) const {
        T dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }

    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y); }
    bool operator==(const Point &p) const { return x == p.x && y == p.y; }
    Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }

    bool collinear(const Point &b, const Point &c) const {
        return (b.y - y) * (c.x - x) == (c.y - y) * (b.x - x);
    }
    bool in_box(const Point &a, const Point &b) const {
        T lox = min(a.x, b.x), hix = max(a.x, b.x);
        T loy = min(a.y, b.y), hiy = max(a.y, b.y);
        return x >= lox && x <= hix && y >= loy && y <= hiy;
    }
    // cross product magnitude of axb, relative to this
    T cross(const Point &a, const Point &b) const {
        return (a.x-x)*(b.y-y) - (a.y-y)*(b.x-x);
    }
};

template <typename T>
struct Line {
    T a, b, c;  // ax + by + c = 0
    Line(T A, T B, T C) : a(A), b(B), c(C) {}
    Line(const Point<T> &p1, const Point<T> &p2) {
        if (p1.x == p2.x) { a = 1, b = 0, c = -p1.x; return; }
        a = p1.y-p2.y; b = p2.x-p1.x; c = -a*p1.x - b*p1.y;
    }
    Line(const Point<T> &p, T m) { a = -m; b = 1; c = m*p.x - p.y; }

    bool is_parallel(const Line &l) const { return a * l.b == b * l.a; }
    bool is_vertical() const { return b == 0; }
    bool is_horizontal() const { return a == 0; }
    bool operator==(const Line &l) const {
        return is_parallel(l) && a * l.c == c * l.a;
    }
    bool intersection(const Line<T> &l, Point<T> &p) const {
        if (is_parallel(l)) return false;
        const Line<T> &rl = is_vertical() ? l : *this;
        p.x = (l.b*c - b*l.c) / (l.a*b - a*l.b);
        p.y = -(rl.a * p.x + rl.c) / rl.b;
        return true;
    }
};

template <typename T>
struct Segment {
    Point<T> a, b;
    Segment(Point<T> A, Point<T> B) : a(A), b(B) {}

    bool intersection(const Segment<T> &s, Point<T> &p) const {
        Line<T> l1(a, b);
        Line<T> l2(s.a, s.b);
        if (! l1.intersection(l2, p)) return false;
        return p.in_box(a, b) && p.in_box(s.a, s.b);
    }
};

struct Vector {
    double x, y;
    Vector(double X, double Y) : x(X), y(Y) {}
    Vector(const Point &p) : x(p.x), y(p.y) {}
    double norm() { return sqrt(x*x + y*y); }
    double cross(const Vector &v) const { return x * v.y  - y * v.x; }
    double angle(const Vector &p) const {
        return circle_angle(atan2(p.y, p.x) - atan2(y, x));
    }
    void rotate(double a) {
        double px = x, py = y;
        x = px*cos(a) - py*sin(a);
        y = px*sin(a) + py*cos(a);
    }
    double distance_line_point(Point a, Point p) {
        return fabs((p.x-a.x)*y - (p.y-a.y)*x) / sqrt(x*x + y*y);
    }
};

template <typename T>
struct Circle {
    T x, y, r;
    Circle() {}
    Circle(T X, T Y, T R) : x(X), y(Y), r(R) {}
    // Finds the circle formed by three points
    Circle(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3) {
        Point<T> m, a, b;
        if (! eps_equal(p1.x, p2.x) && ! eps_equal(p1.x, p3.x))
            m = p1, a = p2, b = p3;
        else if (! eps_equal(p2.x, p1.x) && ! eps_equal(p2.x, p3.x))
            m = p2, a = p1, b = p3;
        else
            m = p3, a = p1, b = p2;

        T ma = (m.y - a.y) / (m.x - a.x);
        T mb = (b.y - m.y) / (b.x - m.x);

        x = ma*mb*(a.y - b.y) + mb*(a.x + m.x) - ma*(m.x + b.x);
        x /= (mb - ma)*2.0;

        if (eps_equal(0.0, ma))
            y = (m.y + b.y) / 2.0 - (x - (m.x + b.x)/2.0) / mb;
        else
            y = (a.y + m.y) / 2.0 - (x - (a.x + m.x)/2.0) / ma;

        r = p1.distance(Point<T>(x, y));
    }
    T circum() { return pi * r * 2; }
    bool perimeters_touch(const Circle &c) const {
        double dx = x - c.x;
        double dy = y - c.y;
        double dist = sqrt(dx*dx + dy*dy);
        return ! (eps_less(r + c.r, dist) ||
                  eps_less(dist, fabs(r - c.r)));
    }
};

// area of a polygon, times two
template <typename T>
T poly_area2(Point<T> *p, int n)
{
    T a = 0;
    for (int i = 0, j = n - 1; i < n; j = i++)
        a += (p[j].x + p[i].x) * (p[j].y - p[i].y);
    if (a < 0) a *= -1;
    return a;
}

template <typename T>
T lattice_pts(Point<T> &a, Point<T> &b)
{
    if (a.x == b.x) return llabs(a.y - b.y) + 1;
    return gcd(llabs(a.y - b.y), llabs(a.x - b.x)) + 1;
}
void convex_hull(Point<> *p, int n, Point<> *h, int &k) {
    // Pre-cond:  sizeof(h) == 2*sizeof(p)
    // Post-cond: n > 1 => h[0] == h[k-1]
    k = 0;
    sort(p, p + n);
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && h[k-2].cross(h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n-2, t=k+1; i >= 0; --i) {
        while (k >= t && h[k-2].cross(h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
}
