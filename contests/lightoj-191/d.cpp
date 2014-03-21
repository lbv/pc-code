#include <cmath>
#include <cstdio>

#define EPS (1e-9)

int n, i;
double p;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%lf", &n, &i, &p);

        double ans;

        if (i == 0 || p < EPS)
            ans = 0.0;
        else
            ans = pow(1.0-p, i-1)*p / (1.0 - pow(1.0-p, n));

        printf("Game %d: %.3lf\n", ++ncase, ans);
    }

    return 0;
}
