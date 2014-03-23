#include <cstdio>
#include <cstring>

#define MAXM 500

#define Zero(v) memset(v, 0, sizeof(v))

// states are described as tuples (i, j) where i is the number of red
// marbles, and j is the number of j marbles

// dp[i][j] is the probability of reaching the state (0, 1) from (i, j)
double dp[MAXM + 1][MAXM + 1];

int R, B;

void run_dp()
{
    for (int j = 1; j <= MAXM; j += 2)
        dp[0][j] = 1.0;

    for (int i = 1; i <= MAXM; ++i)
        for (int j = i + 1; j <= MAXM; j += 2) {
            dp[i][j]  = dp[i - 1][j - 1] * i / (i + j);
            dp[i][j] += dp[i][j - 2] * j / (i + j);
        }
}

int main()
{
    run_dp();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &R, &B);

        printf("Case %d: %.8lf\n", ++ncase, dp[R][B]);
    }

    return 0;
}
