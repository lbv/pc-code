#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

double l, w;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%lf%lf", &l, &w);

        double h = max(l, w) / (2 * sqrt(2));

        printf("Case %d: %.1lf\n", ++ncase, h);
    }

    return 0;
}
