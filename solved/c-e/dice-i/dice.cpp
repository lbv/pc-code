#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXS 15000
#define MOD  100000007



// dp[x][i] will have the prefix sum of the number of ways to make i
int dp[2][MAXS + 1];

int *cur;
int *nxt;

int N, K, S;


#define Clear(v) memset((v), 0, sizeof(dp[0]))
void run_dp()
{
    cur = dp[0];
    nxt = dp[1];

    Clear(cur);
    for (int i = 1; i <= min(K, S); ++i) cur[i] = i;
    for (int i = K + 1, I = min(2*K, S); i <= I; ++i) cur[i] = cur[i - 1];

    for (int i = 2; i <= N; ++i) {
        Clear(nxt);

        for (int j = i, J = min(S, K*i); j <= J; ++j) {
            nxt[j] += nxt[j - 1];
            nxt[j] += cur[j - 1] - cur[max(0, j - 1 - K)];
            nxt[j] %= MOD;
        }
        for (int j = K*i + 1, J = min(S, K*(i+1)); j <= J; ++j)
            nxt[j] = nxt[j - 1];

        swap(cur, nxt);
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &N, &K, &S);
        run_dp();

        int ans = cur[S] - cur[max(0, S - 1)];
        ans %= MOD;
        if (ans < 0) ans += MOD;

        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}
