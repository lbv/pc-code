#include <cstdio>

typedef unsigned long long u64;

#define MAXN 30

u64 dp[MAXN + 1][MAXN + 1];

int main()
{
    for (u64 i = 1; i <= MAXN; ++i) {
        dp[i][0] = 1;
        dp[i][1] = i*i;

        for (u64 j = 2, r = i-j+1; j <= i; ++j, --r)
            dp[i][j] = dp[i][j-1] * r * r / j;
    }

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n, k;
        scanf("%d%d", &n, &k);
        if (k > n)
            printf("Case %d: 0\n", ++ncase);
        else
            printf("Case %d: %llu\n", ++ncase, dp[n][k]);
    }

    return 0;
}
