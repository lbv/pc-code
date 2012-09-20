#include <cstdio>


#define MAXN 22


typedef unsigned long long u64;


// dp[i][j][x] has the number of ways to produce the sequence, if the next
// number has to be chosen according to x (0: lower, 1: highest), and there
// are i numbers above and j numbers below the last one selected
u64 dp[MAXN][MAXN][2];

int N, m;


void run_dp()
{
    dp[1][0][1] = 1;
    dp[0][1][0] = 1;

    for (int p = 2; p < MAXN; ++p) {
        for (int i = 1; i <= p; ++i) {
            int j = p - i;

            for (int t = 1; t <= i; ++t) {
                dp[i][j][1] += dp[i - t][j + t - 1][0];
                dp[j][i][0] += dp[j + t - 1][i - t][1];
            }
        }
    }
}

int main()
{
    run_dp();

    while (true) {
        if (scanf("%d%d", &N, &m) != 2) break;

        u64 ans;
        if (m == 1)
            ans = N > 3 ? dp[N - 3][0][1] : 1;
        else
            ans = dp[N - m][m - 1][0];

        printf("%llu\n", ans);
    }

    return 0;
}
