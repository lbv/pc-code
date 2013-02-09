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
        return x < p.x || (x == p.x && y < p.y);
    }
    Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
    bool collinear(const Point &b, const Point &c) const {
        return (b.y - y) * (c.x - x) == (c.y - y) * (b.x - x);
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
p_t cross(const Point &o, const Point &a, const Point &b)
{
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
void convex_hull(PV &p, PV &h) {
    // Post-cond: p.size() > 1 => h.front() == h.back()
    int n = p.size(), k = 0;
    h.resize(2*n);
    sort(p.begin(), p.end());
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n-2, t=k+1; i >= 0; --i) {
        while (k >= t && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    h.resize(k);
}
