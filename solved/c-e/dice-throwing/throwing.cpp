#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef unsigned long long u64;

#define Zero(v) memset(v, 0, sizeof(v))

#define MAXN 24
#define MAXX 149

// dp[i][j] has the numerator of the probability that i dice produce at least j
u64 dp[MAXN + 1][MAXX + 1];

// dp2[i] has the denominator of the probability for i dice
u64 dp2[MAXN + 1];

u64 gcd(u64 a, u64 b) { for (u64 c = a%b; c; a=b,b=c,c=a%b); return b; }

void prepare()
{
    Zero(dp);

    // First, dp[i][j] has the probability that i dice produce exactly j
    for (int i = 1; i <= 6; i++)
        dp[1][i] = 1;
    for (int i = 2; i <= MAXN; i++)
        for (int j = i, J = min(MAXX, 6*i); j <= J; j++)
            for (int k = j-1, K = max(j - 6, 0); k >= K; k--)
                dp[i][j] += dp[i-1][k];

    // Then we accumulate
    for (int i = 1; i <= MAXN; i++)
        for (int j = min(MAXX, 6*i) - 1; j >= 0; j--)
            dp[i][j] += dp[i][j+1];

    dp2[1] = 6;
    for (int i = 2; i <= MAXN; i++)
        dp2[i] = dp2[i-1]*6;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n, x;
        scanf("%d%d", &n, &x);

        u64 num = dp[n][x];
        u64 den = dp2[n];
        u64 comdiv = gcd(num, den);
        num /= comdiv;
        den /= comdiv;
        printf("Case %d: ", ncase++);
        if (den == 1)
            printf("%llu\n", num);
        else
            printf("%llu/%llu\n", num, den);
    }

    return 0;
}
