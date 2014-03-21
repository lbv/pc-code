#include <cmath>
#include <cstdio>

double v, u, d, a;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%lf%lf%lf%lf", &v, &u, &d, &a);

        double t = a/sqrt(v*v - u*u) + (d-a)/v;

        printf("Case %d: %.2lf\n", ++ncase, t + (1e-9));
    }

    return 0;
}
