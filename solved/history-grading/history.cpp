#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 20


// dp[i][j]: length of LCS between A(0 .. i) and B(0 .. j)
int dp[MAXN + 1][MAXN + 1];

int n;
int A[MAXN];
int B[MAXN];

int solve()
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            int best = max(dp[i - 1][j], dp[i][j - 1]);

            if (A[i - 1] == B[j - 1])
                best = max(best, dp[i - 1][j - 1] + 1);

            dp[i][j] = best;
        }

    return dp[n][n];
}

int main()
{
    scanf("%d", &n);
    int x;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        A[x - 1] = i;
    }

    while (true) {
        for (int i = 1; i <= n; ++i) {
            if (scanf("%d", &x) != 1) return 0;
            B[x - 1] = i;
        }

        printf("%d\n", solve());
    }

    return 0;
}
