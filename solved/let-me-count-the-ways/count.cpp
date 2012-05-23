#include <cstdio>

#define MAXN 30000

typedef long long i64;

i64 dp[MAXN + 1];

#define DP_LOOP(n) \
    for (int i = n, j = 0; i <= MAXN; ++i, ++j)\
        dp[i] += dp[j];

void prepare()
{
    dp[0] = 1;
    DP_LOOP(50);
    DP_LOOP(25);
    DP_LOOP(10);
    DP_LOOP(5);
    DP_LOOP(1);
}

int main()
{
    prepare();

    int n;
    while (1) {
        if (scanf("%d", &n) != 1) break;

        if (dp[n] == 1)
            printf("There is only 1 way to produce %d cents change.\n", n);
        else
            printf("There are %lld ways to produce %d cents change.\n", dp[n], n);
    }

    return 0;
}
