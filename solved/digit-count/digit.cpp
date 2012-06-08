#include <cstdio>
#include <cstring>

#define MAXM 9
#define MAXN 10

#define Zero(v) memset(v, 0, sizeof(v))

int digits[MAXM];

// dp[i][j] has the number of valid i-digit numbers, where the last digit is
// digits[j]
int dp[MAXN + 1][MAXM];

int m, n;

int run_dp()
{
    Zero(dp);
    for (int j = 0; j < m; ++j)
        dp[1][j] = 1;

    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i][j] = 0;
            for (int k = j; k < m && digits[k] - digits[j] <= 2; ++k)
                dp[i][j] += dp[i - 1][k];
            for (int k = j - 1; k >= 0 && digits[j] - digits[k] <= 2; --k)
                dp[i][j] += dp[i - 1][k];
        }
    }

    int ans = 0;
    for (int i = 0; i < m; ++i)
        ans += dp[n][i];

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &m, &n);

        for (int i = 0; i < m; ++i)
            scanf("%d", &digits[i]);

        printf("Case %d: %d\n", ++ncase, run_dp());
    }

    return 0;
}
