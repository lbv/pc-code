#include <cstdio>

#define MAXN 100
#define INF 1000100

// dp[i][j] will have the best possible socre difference for a player who is
// playing with the numbers from i to j
int dp[MAXN + 1][MAXN + 1];

int ns[MAXN + 1];
int ps[MAXN + 1];  // prefix sums
int N;

void run_dp()
{
    for (int i = 1; i <= N; ++i)
        dp[i][i] = ns[i];

    int best, cur;
    for (int i = 2; i <= N; ++i) {
        for (int a = 1, b = a + i - 1; b <= N; ++a, ++b) {
            best = -INF;
            for (int j = 1; j <= i; ++j) {
                // take from the left
                cur = ps[a + j - 1] - ps[a - 1];
                if (j < i)
                    cur -= dp[a + j][b];
                if (cur > best) best = cur;

                // take from the right
                cur = ps[b] - ps[b - j];
                if (j < i)
                    cur -= dp[a][b - j];
                if (cur > best) best = cur;
            }
            dp[a][b] = best;
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        for (int i = 1; i <= N; ++i) {
            scanf("%d", &ns[i]);
            ps[i] = ps[i-1] + ns[i];
        }

        run_dp();

        printf("Case %d: %d\n", ++ncase, dp[1][N]);
    }

    return 0;
}
