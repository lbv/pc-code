#include <cmath>
#include <cstdio>


#define EPS (1e-9)


struct Point {
    double x, y, z;
    Point() {}
    Point(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
    void read() { scanf("%lf%lf%lf", &x, &y, &z); }
    double distance(const Point &p) const {
        double dx = p.x - x;
        double dy = p.y - y;
        double dz = p.z - z;
        return sqrt(dx*dx + dy*dy + dz*dz);
    }
};


Point A, B, P;
double dx, dy, dz;


double distance(double m)
{
    Point p1(A.x + dx * m, A.y + dy * m, A.z + dz * m);
    return p1.distance(P);
}

double solve()
{
    double lo = 0.0;
    double hi = 1.0;

    dx = B.x - A.x;
    dy = B.y - A.y;
    dz = B.z - A.z;

    while (true) {
        double third = (hi - lo) / 3.0;
        double m1 = lo + third;
        double m2 = hi - third;

        double d1 = distance(m1);
        double d2 = distance(m2);

        if (fabs(d1 - d2) < EPS && fabs(hi - lo) < EPS) return d1;

        if (d1 < d2) hi = m2;
        else lo = m1;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        A.read();
        B.read();
        P.read();

        printf("Case %d: %.8lf\n", ++ncase, solve());
    }

    return 0;
}
