#include <cmath>
#include <cstdio>


#define EPS (1e-9)


int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
double dx1, dy1, dx2, dy2;


double distance (double m)
{
    double x1 = Ax + dx1 * m;
    double y1 = Ay + dy1 * m;
    double x2 = Cx + dx2 * m;
    double y2 = Cy + dy2 * m;

    double dx = x2 - x1;
    double dy = y2 - y1;

    return sqrt(dx*dx + dy*dy);
}

double solve()
{
    double lo = 0.0;
    double hi = 1.0;

    while (true) {
        double third = (hi - lo) / 3.0;
        double m1 = lo + third;
        double m2 = hi - third;

        double d1 = distance(m1);
        double d2 = distance(m2);

        if (fabs(hi - lo) < EPS && fabs(d1 - d2) < EPS) return d1;

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
        scanf("%d%d%d%d%d%d%d%d", &Ax, &Ay, &Bx, &By, &Cx, &Cy, &Dx, &Dy);
        dx1 = Bx - Ax;
        dy1 = By - Ay;
        dx2 = Dx - Cx;
        dy2 = Dy - Cy;
        printf("Case %d: %.8lf\n", ++ncase, solve());
    }

    return 0;
}
