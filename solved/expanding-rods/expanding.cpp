#include <cmath>
#include <cstdio>

#define EPS (10e-8)

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        double L, n, C;
        scanf("%lf%lf%lf", &L, &n, &C);

        double a;  // angle
        double s;  // arc
        double c;  // chord
        double r;  // radius
        double h;

        double min = 0.0;
        double max = 1.5 * L;

        double L2 = L*L;

        s = (1 + n*C) * L;
        double prev = -1.0;
        while (1) {
            h = (max + min) / 2;
            if (fabs(h - prev) < EPS) break;

            r = h/2 + L2 / (8*h);
            a = s / r;
            c = 2 * r * sin(a/2);

            prev = h;
            if (c > L) min = h;
            else max = h;
        }

        printf("Case %d: %.8lf\n", ++ncase, h);
    }

    return 0;
}
