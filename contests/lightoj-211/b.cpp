#include <cmath>
#include <cstdio>

const double Pi = acos(0.0)*2;
double M, F, P;

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%lf%lf%lf", &M, &F, &P);

        double turns = M / F;
        double d = P * 2 * Pi * turns;

        printf("%.4lf\n", d);
    }

    return 0;
}
