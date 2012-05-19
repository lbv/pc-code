#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        double v1, v2, v3, a1, a2;
        scanf("%lf%lf%lf%lf%lf", &v1, &v2, &v3, &a1, &a2);

        double t1 = v1/a1, t2 = v2/a2;
        double bird = max(t1, t2) * v3;
        double d = (t1*v1 + t2*v2) / 2;

        printf("Case %d: %.8lf %.8lf\n", ncase++, d, bird);
    }

    return 0;
}
