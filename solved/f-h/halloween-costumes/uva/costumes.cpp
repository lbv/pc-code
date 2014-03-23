#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100

const int INF = MAXN + 1;


int N;
int cos[MAXN];

// dp[i][j]: minimum number of costumes to put on to attend parties i to j
int dp[MAXN][MAXN];


void pre()
{
    for (int i = 0; i < MAXN; ++i)
        dp[i][i] = 1;
}

int solve()
{
    for (int len = 2; len <= N; ++len)
        for (int a = 0, b = len - 1; b < N; ++a, ++b) {
            int best = INF;

            for (int c = b - 1; c >= a; --c) {
                if (cos[c] == cos[b])
                    best = min(best, dp[a][c] + dp[c+1][b-1]);
                else
                    best = min(best, dp[a][c] + dp[c+1][b]);
            }

            dp[a][b] = best;
        }

    return dp[0][N - 1];
}

int main()
{
    pre();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%*d", &N);
        for (int i = 0; i < N; ++i) scanf("%d", &cos[i]);
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
