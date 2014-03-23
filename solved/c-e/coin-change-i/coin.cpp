#include <cstdio>
#include <cstring>


#define MAXK 1000
#define MAXN 50
#define MOD  100000007

#define Zero(v) memset((v), 0, sizeof(v))


// dp[i][j] has the number of ways to make j using the first i coins
int dp[MAXN + 1][MAXK + 1];

int n, K;
int A[MAXN + 1], C[MAXN + 1];

void run_dp()
{
    Zero(dp);
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i)
        for (int c = 0; c <= C[i]; ++c)
            for (int j = A[i] * c, b = 0; j <= K; ++j, ++b) {
                dp[i][j] += dp[i - 1][b];
                dp[i][j] %= MOD;
            }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &K);

        for (int i = 1; i <= n; ++i) scanf("%d", &A[i]);
        for (int i = 1; i <= n; ++i) scanf("%d", &C[i]);

        run_dp();

        printf("Case %d: %d\n", ++ncase, dp[n][K]);
    }

    return 0;
}
