#include <cstdio>


#define MAXN 50
#define MAXK 50
#define MAXM 50


typedef unsigned long long u64;


// dp[i][j][k]: number of valid codes of width i, with j bars, and k maximum
// width of any bar
u64 dp[MAXN + 1][MAXK + 1][MAXM + 1];

int n, k, m;


#include <limits>
using namespace std;
void run_dp()
{
    for (int k = 1; k <= MAXM; ++k)
        for (int i = 1; i <= k; ++i)
            dp[i][1][k] = 1;

    for (int j = 2; j <= MAXK; ++j)
        for (int k = 1; k <= MAXM; ++k) {

            int top = j*k;
            if (top > MAXN) top = MAXN;

            for (int i = j; i <= top; ++i)
                for (int r = 1; r <= k; ++r) {
                    if (i - r < j - 1) break;

                    dp[i][j][k] += dp[i - r][j - 1][k];
                }
        }
}

int main()
{
    run_dp();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &n, &k, &m);
        printf("Case %d: %llu\n", ++ncase, dp[n][k][m]);
    }

    return 0;
}
