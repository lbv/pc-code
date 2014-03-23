#include <stdio.h>

int M, N;
int uranium[500][500];
int radium[500][500];

#define MAX(a,b) ((a)>(b) ? (a) : (b))

int
prev_col(int a[500][500], int i, int j)
{
    if (j == 0) return 0;
    return a[i][j-1];
}

int
prev_row(int a[500][500], int i, int j)
{
    if (i == 0) return 0;
    return a[i-1][j];
}

int
solve(void)
{
    int dp[500][500];
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            dp[i][j] = MAX(
                radium[i][j] + prev_col(dp, i, j),
                uranium[i][j] + prev_row(dp, i, j));
        }
    }

    return dp[M-1][N-1];
}

int
main(void)
{
    int T, ncase, n, i, j;

    scanf("%d", &T);
    ncase = 1;
    while (T-- > 0) {
        scanf("%d%d", &M, &N);
        for (i = 0; i < M; i++)
            for (j = 0; j < N; j++) {
                scanf("%d", &n);
                uranium[i][j] = n + prev_col(uranium, i, j);
            }
        for (i = 0; i < M; i++)
            for (j = 0; j < N; j++) {
                scanf("%d", &n);
                radium[i][j] = n + prev_row(radium, i, j);
            }

       printf("Case %d: %d\n", ncase++, solve());
    }

    return 0;
}
