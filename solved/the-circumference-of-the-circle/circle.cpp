#include <cstdio>
#include <cmath>


#define EPS (1e-8)


const double pi = acos(-1);


bool eps_equal(double a, double b) { return fabs(a - b) < EPS; }


template <typename T>
struct Point {
    T x, y;
    Point() { x=y=0; }
    Point(T X, T Y) : x(X), y(Y) {}
    T distance(const Point &p) const {
        T dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }
};
typedef Point<double> P;

template <typename T>
struct Circle {
    T x, y, r;
    Circle() {}
    Circle(T X, T Y, T R) : x(X), y(Y), r(R) {}
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
    T circum() {
        return pi * r * 2;
    }
};


double X1, Y1, X2, Y2, X3, Y3;


double solve()
{
    Circle<double> circ(P(X1, Y1), P(X2, Y2), P(X3, Y3));
    return circ.circum();
}

int main()
{
    while (true) {
        if (scanf("%lf%lf%lf%lf%lf%lf", &X1, &Y1, &X2, &Y2, &X3, &Y3) != 6)
            break;

        printf("%.2lf\n", solve());
    }

    return 0;
}
