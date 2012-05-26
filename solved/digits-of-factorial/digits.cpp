#include <cmath>
#include <cstdio>

#define MAX 1000000

double f[MAX + 1];

void precalculate(void)
{
    f[1] = 0.0;
    for (int i = 2; i <= MAX; i++)
        f[i] = log(i) + f[i-1];
}

int digits(int n, int base)
{
    if (n == 0) return 1;
    return static_cast<int>(ceil(f[n]/log(base)));
}

int main(void)
{
    precalculate();

    int T;
    scanf("%d", &T);

    for (int ncase = 1; ncase <= T; ncase++) {
        int n, base;
        scanf("%d%d", &n, &base);

        printf("Case %d: %d\n", ncase, digits(n, base));
    }
}
