#include <cstdio>

#define MAXN 500

// dp[i][j] will have the probability of having a maximum winning streak of
// j in i consecutive games
double dp[MAXN + 1][MAXN + 1];

// pp[i] will have p^i
double pp[MAXN + 1];

int n;
double p;
double ans;

void run_dp()
{
    pp[0] = 1.0;
    for (int i = 1; i <= n; ++i) pp[i] = pp[i - 1] * p;

    for (int j = 0; j <= n; ++j)
        dp[0][j] = 1.0;

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = dp[i-1][j];
            if (j == i - 1) dp[i][j] -= pp[i];
            else if (j < i - 1)
                dp[i][j] -= dp[i - j - 2][j] * (1-p) * pp[j+1];
        }

    ans = 0.0;
    for (int j = 1; j <= n; ++j)
        ans += j * (dp[n][j] - dp[n][j - 1]);
}

int main()
{
    while (true) {
        scanf("%d%lf", &n, &p);
        if (n == 0) break;

        run_dp();

        printf("%.8lf\n", ans);
    }

    return 0;
}
