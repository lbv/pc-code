#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXK 100
#define MAXN 100

int ys[MAXN];
int N, w, k;

// dp[i][j] has the maximum number of dust points that are covered by i
// moves, up until the point j
int dp[MAXK + 1][MAXN];

// move1[i] has the number of dust points covered by one move, placing the
// top of the brush at point ys[i]
int move1[MAXN];

#define DP(i,j) ((i)>=1 && (j)>=0 ? dp[i][j] : 0)

void run_dp()
{
    sort(ys, ys + N);

    for (int hi=0, lo=0; hi < N; hi++) {
        while (ys[hi] - ys[lo] > w) lo++;
        move1[hi] = hi-lo+1;
    }
    for (int i = 1; i <= k; i++) {
        dp[i][0] = move1[0];
        for (int j = 1; j < N; j++)
            dp[i][j] = max(move1[j] + DP(i-1, j-move1[j]), dp[i][j-1]);
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%d%d%d", &N, &w, &k);
        int x;
        for (int i = 0; i < N; i++)
            scanf("%d%d", &x, &ys[i]);

        run_dp();

        printf("Case %d: %d\n", ncase++, dp[k][N-1]);
    }

    return 0;
}
