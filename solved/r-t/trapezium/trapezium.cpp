#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        double a, b, c, d, area_tri, area_tra, s;
        scanf("%lf%lf%lf%lf", &a, &b, &c, &d);

        if (a == c)
            area_tra = a * b;
        else {
            if (a < c) swap(a, c);
            s = (b + d + a-c) / 2;
            area_tri = sqrt(s * (s-b) * (s-d) * (s-a+c));

            area_tra = area_tri * (a+c) / (a-c);
        }

        printf("Case %d: %.9lf\n", ++ncase, area_tra);
    }

    return 0;
}
