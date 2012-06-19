#include <cmath>
#include <cstdio>

#define EPS (10e-8)

double L, n, C;

int main()
{
    while (true) {
        scanf("%lf%lf%lf", &L, &n, &C);
        if (L < 0 && n < 0 && C < 0) break;

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

        printf("%.3lf\n", h);
    }

    return 0;
}
