#include <cmath>
#include <cstdio>

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        double AB, R;
        scanf("%lf %*f %*f %lf", &AB, &R);

        double AD = sqrt(AB*AB*R / (R+1));
        printf("Case %d: %.9lf\n", ++ncase, AD);
    }

    return 0;
}
