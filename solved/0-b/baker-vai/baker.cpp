#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXM 100
#define MAXN 100

#define Zero(v) memset(v, 0, sizeof(v))

// dp[i][j][k] has the maximum sum after reaching the ith row, with two
// paths, one in column j, and the other in column k
int dp[MAXM][MAXN][MAXN];

int map[MAXM][MAXN];
int m, n;

void run_dp()
{
    Zero(dp);

    dp[0][0][1] = map[0][0] + map[0][1];
    for (int k = 2; k < n; ++k)
        dp[0][0][k] = dp[0][0][k - 1] + map[0][k];

    for (int i = 1; i < m; ++i) {
        // we'll try three possible moves, in order, to avoid counting any
        // cell more than once

        // first, move directly the two paths from the row above
        for (int j = 0; j < n; ++j)
            for (int k = j + 1 ; k < n; ++k)
                dp[i][j][k] = dp[i - 1][j][k] + map[i][j] + map[i][k];

        // now, move the left path only
        for (int j = 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k)
                dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k] + map[i][j]);

        // finally, move the right path only
        for (int j = 0; j < n; ++j)
            for (int k = j + 2; k < n; ++k)
                dp[i][j][k] = max(dp[i][j][k], dp[i][j][k - 1] + map[i][k]);
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &m, &n);

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &map[i][j]);

        run_dp();

        printf("Case %d: %d\n", ++ncase, dp[m - 1][n - 2][n - 1]);
    }

    return 0;
}
