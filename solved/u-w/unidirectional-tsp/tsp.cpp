#include <cstdio>


#define MAXM 10
#define MAXN 100


int m, n;
int maze[MAXM][MAXN];

// dp[i][j]: minimum cost of path that goes from right to left and ends in
// position (i, j)
int dp[MAXM][MAXN];

// next[i][j]: row of the next position in the best path from (i, j)
int next[MAXM][MAXN];


void print_path(int r)
{
    printf("%d", r + 1);

    r = next[r][0];
    int c = 1;
    while (r >= 0) {
        printf(" %d", r + 1);
        r = next[r][c++];
    }
    putchar('\n');
}

void solve()
{
    for (int i = 0; i < m; ++i) {
        dp[i][n - 1] = maze[i][n - 1];
        next[i][n - 1] = -1;
    }

    for (int j = n - 2; j >= 0; --j)
        for (int i = 0; i < m; ++i) {
            int row = (i - 1 + m) % m;
            int best = dp[row][j + 1];
            int nrow = row;

            if (dp[i][j + 1] < best || (dp[i][j + 1] == best && i < nrow)) {
                best = dp[i][j + 1];
                nrow = i;
            }

            row = (i + 1) % m;
            if (dp[row][j + 1] < best ||
                (dp[row][j + 1] == best && row < nrow)) {
                best = dp[row][j + 1];
                nrow = row;
            }

            dp[i][j] = maze[i][j] + best;
            next[i][j] = nrow;
        }

    int best = dp[0][0];
    int row = 0;

    for (int i = 1; i < m; ++i)
        if (dp[i][0] < best) {
            best = dp[i][0];
            row = i;
        }

    print_path(row);
    printf("%d\n", best);
}

int main()
{
    while (true) {
        if (scanf("%d%d", &m, &n) != 2) break;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &maze[i][j]);

        solve();
    }

    return 0;
}
