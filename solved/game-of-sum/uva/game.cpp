#include <cstdio>

#define MAXN 100
#define INF 1LL << 63;

typedef long long i64;

// dp[i][j] will have the best possible socre difference for a player who is
// playing with the numbers from i to j
i64 dp[MAXN + 1][MAXN + 1];

i64 ns[MAXN + 1];
i64 ps[MAXN + 1];  // prefix sums
int n;

void run_dp()
{
    for (int i = 1; i <= n; ++i)
        dp[i][i] = ns[i];

    i64 best, cur;
    for (int i = 2; i <= n; ++i) {
        for (int a = 1, b = a + i - 1; b <= n; ++a, ++b) {
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
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &ns[i]);
            ps[i] = ps[i-1] + ns[i];
        }

        run_dp();

        printf("%lld\n", dp[1][n]);
    }

    return 0;
}
