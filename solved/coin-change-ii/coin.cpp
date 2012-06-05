#include <cstdio>
#include <cstring>

#define MAXK 10000
#define MAXN 100
#define MOD  100000007

#define Zero(v) memset(v, 0, sizeof(v))

// dp[i] will store the number of ways to make i with the coins
int dp[MAXK + 1];

int A[MAXN];
int n, K;

void run_dp()
{
    Zero(dp);
    dp[0] = 1;

    for (int i = n - 1; i >= 0; --i)
        for (int a = 0, b = A[i]; b <= K; ++a, ++b)
            dp[b] = (dp[b] + dp[a]) % MOD;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &K);

        for (int i = 0; i < n; ++i)
            scanf("%d", &A[i]);

        run_dp();

        printf("Case %d: %d\n", ++ncase, dp[K]);
    }

    return 0;
}
