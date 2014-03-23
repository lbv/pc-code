#include <cmath>
#include <cstdio>

const double Pi2 = 4 * acos(0);
namespace Geometry {
    double circle_angle(double a) { return a >= 0 ? a : Pi2 + a; }
}
typedef double p_t;
struct Point {
    p_t x, y;
    Point() { x=y=0; }
    Point(p_t X, p_t Y) : x(X), y(Y) {}
    Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
};
struct Vector {
    p_t x, y;
    Vector(p_t X, p_t Y) : x(X), y(Y) {}
    Vector(const Point &p) : x(p.x), y(p.y) {}
    double angle(const Vector &p) const {
        return Geometry::circle_angle(atan2(p.y, p.x) - atan2(y, x));
    }
    double norm() { return sqrt(x*x + y*y); }
    double distance_line_point(Point a, Point p) {
        return fabs((p.x-a.x)*y - (p.y-a.y)*x) / sqrt(x*x + y*y);
    }
};

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        double R1, R2, R3;
        scanf("%lf%lf%lf", &R1, &R2, &R3);

        Point p1(0, 0);
        Point p2(R1 + R2, 0);

        double r1s = R1*R1;
        double r2s = R2*R2;

        double x, y;
        x = (2*R1*R3 + r1s - 2*R2*R3 - r2s + p2.x*p2.x) / (2*p2.x);
        y = sqrt((R2+R3)*(R2+R3) - (x-p2.x)*(x-p2.x));

        Point p3(x, y);
        Vector AB(p2);
        Vector AC(p3);
        Vector BC(p3-p2);
        Vector BA(p1-p2);
        Vector CA(p1-p3);
        Vector CB(p2-p3);

        double area_t = AC.norm()*AC.distance_line_point(p1, p2) / 2;
        double area1 = AB.angle(AC) * r1s / 2;
        double area2 = BC.angle(BA) * r2s / 2;
        double area3 = CA.angle(CB) * R3*R3 / 2;

        printf("Case %d: %.9lf\n", ++ncase, area_t - area1 - area2 - area3);
    }

    return 0;
}
