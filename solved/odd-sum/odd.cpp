#include <cstdio>

int a, b;

int sum(int lo, int hi)
{
    if (lo < 1) lo = 1;
    if (lo > hi) return 0;
    if (lo == hi) return lo;
    return (hi*(hi+1) - (lo-1)*lo)/2;
}

int solve()
{
    int x = a % 2 == 0 ? a / 2 : (a - 1) / 2;
    int y = b % 2 == 0 ? b / 2 - 1 : (b - 1) / 2;

    return sum(x, y)*2 + y - x + 1;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &a, &b);
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
