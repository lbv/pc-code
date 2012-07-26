#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

#define EPS (1e-9)

const double Pi_2 = acos(0.0);
const double Pi2 = Pi_2*4;

// Geometry
double circle_angle(double a) { return a >= 0 ? a : Pi2 + a; }
bool eps_less(double a, double b) { return b - a > EPS; }
bool eps_equal(double a, double b) { return fabs(a - b) < EPS; }

typedef double p_t;
struct Point {
    p_t x, y;
    Point() { x=y=0; }
    Point(p_t X, p_t Y) : x(X), y(Y) {}
    p_t distance(Point p) {
        p_t dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }
    bool operator<(const Point &p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
};
struct Vector {
    p_t x, y;
    Vector(p_t X, p_t Y) : x(X), y(Y) {}
    Vector(const Point &p) : x(p.x), y(p.y) {}
    double angle(const Vector &p) const {
        return circle_angle(atan2(p.y, p.x) - atan2(y, x));
    }
    void rotate(double a) {
        p_t px = x, py = y;
        x = px*cos(a) - py*sin(a);
        y = px*sin(a) + py*cos(a);
    }
    double distance_line_point(Point a, Point p) {
        return abs((p.x-a.x)*y - (p.y-a.y)*x) / sqrt(x*x + y*y);
    }
};
typedef vector<Point> PV;
namespace Geometry {
    p_t cross(const Point &o, const Point &a, const Point &b) {
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
}
using namespace Geometry;

int N;

#define Next(idx) (idx + 1 < n - 1 ? idx + 1 : 0)

double solve(PV &p)
{
    if (N < 3) return 0.0;

    PV h;
    convex_hull(p, h);

    int n = h.size();

    int a, b, c, d;
    a = b = c = d = 0;

    for (int i = 1; i < n; ++i) {
        if (h[i].y < h[a].y) a = i;
        if (h[i].y > h[b].y) b = i;
        if (h[i].x < h[c].x) c = i;
        if (h[i].x > h[d].x) d = i;
    }

    double minarea = (h[b].y-h[a].y) * (h[d].x-h[c].x);

    // calipers
    Vector ca(1, 0), cb(-1, 0), cc(0, -1), cd(0, 1);

    double rotated = 0.0;

    while (rotated <= Pi_2) {
        int a2=Next(a), b2=Next(b), c2=Next(c), d2=Next(d);

        Vector ea(h[a2] - h[a]), eb(h[b2] - h[b]), ec(h[c2] - h[c]),
               ed(h[d2] - h[d]);

        double aa = ca.angle(ea);
        double ab = cb.angle(eb);
        double ac = cc.angle(ec);
        double ad = cd.angle(ed);

        double mina = min(min(aa, ab), min(ac, ad));
        ca.rotate(mina);
        cb.rotate(mina);
        cc.rotate(mina);
        cd.rotate(mina);

        double area =
            ca.distance_line_point(h[a], h[b])
            * cc.distance_line_point(h[c], h[d]);
        if (area < minarea) minarea = area;

        if (eps_equal(minarea, 0.0)) break;

        if (aa == mina) a = a2;
        if (ab == mina) b = b2;
        if (ac == mina) c = c2;
        if (ad == mina) d = d2;

        rotated += mina;
    }

    return minarea;
}

int main()
{
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        PV p;
        for (int i = 0; i < N; ++i) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            p.push_back(Point(x, y));
        }

        printf("%.4lf\n", solve(p));
    }

    return 0;
}
