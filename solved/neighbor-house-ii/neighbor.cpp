#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 1000

// both elements unused
#define XX 0
// only the last element used
#define XO 1
// onlye the first element used
#define OX  2

// dp[i][s] has the maximum sum of elements up to the ith element, with the
// state s. The state is one of 3 possibilities: the first element is used
// and the last element is not used, or the first is not used and the last
// is used, or neither is used.
int dp[MAXN][3];

int n;
int xs[MAXN];

int run_dp()
{
    dp[1][XX] = 0;
    dp[1][XO] = xs[1];
    dp[1][OX] = xs[0];

    for (int i = 2; i < n; ++i) {
        dp[i][XX] = max(dp[i-1][XX], dp[i-1][XO]);

        dp[i][XO] = dp[i - 1][XX] + xs[i];

        dp[i][OX] = dp[i - 1][OX];
        if (i > 2)
            dp[i][OX] = max(dp[i][OX], dp[i-2][OX] + xs[i-1]);
    }

    int ans = dp[n - 1][XX];
    ans = max(ans, dp[n - 1][XO]);
    ans = max(ans, dp[n - 1][OX]);
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) scanf("%d", &xs[i]);

        printf("Case %d: %d\n", ++ncase, run_dp());
    }

    return 0;
}
