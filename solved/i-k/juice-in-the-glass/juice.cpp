#include <cmath>
#include <cstdio>

const double Pi = 2 * acos(0);

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        double r1, r2, h, p;
        scanf("%lf%lf%lf%lf", &r1, &r2, &h, &p);

        double m = (r1-r2)/h;
        double b = r2;
        double mp = m*p;

        double v = Pi * p * (mp*(mp/3 + b) + b*b);
        printf("Case %d: %.9lf\n", ++ncase, v);
    }

    return 0;
}
