#include <cmath>
#include <cstdio>


// The first BASE terms will be computed with the direct sum
#define BASE 1000

// The rest will use an approximation based on Euler's constant
#define GAMMA 0.57721566490153286060


double base_h[BASE + 1];
int n;

void prepare()
{
    base_h[1] = 1.0;

    for (int i = 2; i <= BASE; ++i)
        base_h[i] = base_h[i - 1] + 1.0/i;
}

double harmonic(int n)
{
    if (n <= BASE) return base_h[n];

    double den1 = pow(n, 1) * 2;
    double den2 = pow(n, 2) * 12;
    double den3 = pow(n, 4) * 120;
    return log(n) + GAMMA + 1.0 / den1 - 1.0 / den2 + 1.0 / den3;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        printf("Case %d: %.10lf\n", ++ncase, harmonic(n));
    }

    return 0;
}
