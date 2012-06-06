#include <algorithm>
#include <cstdio>
using namespace std;

// dp[i] contains the minimum cost of painting houses when the last house is
// painted with color j
int dp[3];

int n;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    int r, g, b;
    int x, y, z;
    while (T--) {
        scanf("%d", &n);

        scanf("%d%d%d", &dp[0], &dp[1], &dp[2]);
        --n;
        while (n--) {
            scanf("%d%d%d", &r, &g, &b);
            x = r + min(dp[1], dp[2]);
            y = g + min(dp[0], dp[2]);
            z = b + min(dp[0], dp[1]);

            dp[0] = x;
            dp[1] = y;
            dp[2] = z;
        }

        int ans = min(dp[0], min(dp[1], dp[2]));
        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}
