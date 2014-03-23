#include <cmath>
#include <cstdio>


#define EPS (1e-7)


double vol(double l, double w, double x)
{
    return (l - x*2) * (w - x*2) * x;
}

void solve(double l, double w, double &hi, double &lo)
{
    double a = 12.0;
    double b = -4.0 * (l+w);
    double c = l*w;

    double s1 = -b/(a*2);
    double s2 = sqrt(b*b - a*c*4)/(a*2);

    double x1 = s1+s2;
    double x2 = s1-s2;

    double v1 = vol(l, w, x1);
    double v2 = vol(l, w, x2);

    if (v1 > v2)
        hi = x1;
    else
        hi = x2;

    if (l > w)
        lo = w / 2.0;
    else
        lo = l / 2.0;
}

int main()
{
    double L, W;
    double hi, lo;

    while (true) {
        if (scanf("%lf%lf", &L, &W) != 2) break;

        solve(L, W, hi, lo);
        printf("%.3lf %.3lf %.3lf\n", hi + EPS, 0.0, lo + EPS);
    }

    return 0;
}
