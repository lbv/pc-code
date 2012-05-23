#include <cmath>
#include <cstdio>

namespace Geometry {
    const double Eps = 1e-6;
    bool eps_eq(double a, double b) { return fabs(a-b) <= Eps; }
}
using namespace Geometry;

bool solve(double a, double b, double c, double &d)
{
    double p, q;

    if (eps_eq(b, 0)) return false;
    p = a*c/b;

    if (eps_eq(b-p, 0)) return false;
    q = (p+c)*(a+p)/(b-p);

    if (p+q < 0) return false;
    d = p+q;
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        double a, b, c, d;
        scanf("%lf%lf%lf", &a, &b, &c);

        bool valid = solve(a, b, c, d);

        if (valid)
            printf("Case %d: %.9lf\n", ++ncase, d);
        else
            printf("Case %d: -1\n", ++ncase);
    }

    return 0;
}
