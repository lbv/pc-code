#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 200
#define MAXD 20
#define MAXM 10

typedef long long i64;
int N, Q, D, M;
int nums[MAXN + 1];

// dp[i][j][k] has the number of combinations with k numbers, such that
// sum%i==j, where sum is the sum of the k numbers
i64 dp[MAXD + 1][MAXD + 1][MAXM + 1];

void run_dp(void)
{
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= MAXD; i++)
        dp[i][0][0] = 1;

    int mod;
    for (int i = 1; i <= MAXD; i++)
        for (int n = 0; n < N; n++) {
            mod = nums[n] % i;
            if (mod < 0) mod += i;

            for (int k = min(n+1, MAXM); k > 0; k--)
                for (int j = 0; j < i; j++)
                    if (dp[i][j][k-1]) {
                        int nj = (j + mod) % i;
                        dp[i][nj][k] += dp[i][j][k-1];
                    }
        }
}

int main(void)
{
    int T;
    scanf("%d", &T);
    int ncase = 1;
    while (T--) {
        scanf("%d%d", &N, &Q);
        for (int i = 0; i < N; i++) scanf("%d", &nums[i]);
        run_dp();
        printf("Case %d:\n", ncase++);
        while (Q--) {
            scanf("%d%d", &D, &M);
            printf("%Ld\n", dp[D][0][M]);
        }
    }
    return 0;
}
