#include <cmath>
#include <cstdio>


double const Pi  = acos(0.0) * 2.0;
double const Pi2 = acos(0.0) * 4.0;


double circle_angle(double a) { return a >= 0 ? a : Pi2 + a; }

struct Vector {
    double x, y;
    Vector(double X, double Y) : x(X), y(Y) {}
    double norm() { return sqrt(x*x + y*y); }
    double angle(const Vector &p) const {
        return circle_angle(atan2(p.y, p.x) - atan2(y, x));
    }
};


int Ax, Ay, Bx, By, b, c, d;
double Cx, Cy, Dx, Dy;
Vector ux(1.0, 0.0);


void solve()
{
    Vector va(Bx - Ax, By - Ay);
    double bas = va.norm() - c;

    double corner = acos((b*b + bas*bas - d*d) / (2*b*bas));

    double alpha = ux.angle(va) + Pi - corner;
    Vector vb(b * cos(alpha), b * sin(alpha));

    Cx = Bx + vb.x;
    Cy = By + vb.y;

    alpha = ux.angle(va) + Pi;
    Vector vc(c * cos(alpha), c * sin(alpha));

    Dx = Cx + vc.x;
    Dy = Cy + vc.y;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d%d%d%d%d", &Ax, &Ay, &Bx, &By, &b, &c, &d);
        solve();
        printf("Case %d:\n%.8lf %.8lf %.8lf %.8lf\n", ++ncase, Cx, Cy, Dx, Dy);
    }

    return 0;
}
