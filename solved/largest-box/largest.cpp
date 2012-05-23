#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

double vol(double l, double w, double x)
{
    return (l - 2*x) * (w - 2*x) * x;
}

double maxvol(double l, double w)
{
    double a = 12.0;
    double b = -4.0 * (l+w);
    double c = l*w;

    double s1 = -b/(2*a);
    double s2 = sqrt(b*b - 4*a*c)/(2*a);

    double x1 = s1+s2;
    double x2 = s1-s2;

    return max(vol(l, w, x1), vol(l, w, x2));
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        double L, W;
        scanf("%lf%lf", &L, &W);
        printf("Case %d: %.8lf\n", ncase++, maxvol(L, W));
    }

    return 0;
}
