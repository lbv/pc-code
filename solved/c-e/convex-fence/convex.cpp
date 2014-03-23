#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};

// Geometry
typedef double p_t;
const double Pi2 = 4*acos(0.0);
struct Point {
    p_t x, y;
    Point() { x=y=0; }
    Point(p_t X, p_t Y) : x(X), y(Y) {}
    p_t distance(Point p) {
        p_t dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }
    p_t angle(Point p) {
        double a = atan2(p.y-y, p.x-x);
        return a >= 0 ? a : Pi2 + a;
    }
    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
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
    double normal_angle(double a) { return a >= 0 ? a : Pi2 + a; }
}
using namespace Geometry;

int N;
double D;

double solve(PV &p) {
    if (p.size() == 1)
        return Pi2*D;

    PV h;
    convex_hull(p, h);

    double fence = 0.0;

    double first_angle, prev_angle;
    bool set_first = false;

    for (int i = 0, I = h.size()-1; i < I; ++i) {
        Point &a = h[i];
        Point &b = h[i+1];

        fence += a.distance(b);

        double angle = a.angle(b);
        if (! set_first) {
            first_angle = angle;
            set_first = true;
        }
        else {
            double arc = normal_angle(angle - prev_angle);
            fence += D*arc;
        }
        prev_angle = angle;
    }

    double arc = normal_angle(first_angle - prev_angle);
    fence += D*arc;

    return fence;
}

int main()
{
    Reader rr;
    int T = rr.next_int();

    int ncase = 0;
    while (T--) {
        N = rr.next_int();
        D = rr.next_int();

        PV p;

        for (int i = 0; i < N; ++i) {
            double x, y;
            x = rr.next_int();
            y = rr.next_int();
            p.push_back(Point(x, y));
        }

        printf("Case %d: %.8lf\n", ++ncase, solve(p));
    }

    return 0;
}
