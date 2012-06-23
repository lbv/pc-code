#include <cstdio>

#define MAXN 100
#define INF 10000000

int N;
int m[MAXN + 1][MAXN + 1];
int ans;

// prefix sums of the columns
int psc[MAXN + 1][MAXN + 1];

void solve()
{
    ans = -INF;
    int curr_best;

    for (int a = 1; a <= N; ++a)
        for (int b = a; b <= N; ++b) {
            curr_best = -INF;
            for (int j = 1; j <= N; ++j) {
                int col = psc[j][b] - psc[j][a-1];

                if (curr_best < 0) {
                    curr_best = col;
                }
                else
                    curr_best += col;

                if (curr_best > ans) ans = curr_best;
            }
        }
}

int main()
{
    while (true) {
        if (scanf("%d", &N) != 1) break;

        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j) {
                scanf("%d", &m[i][j]);
                psc[j][i] = m[i][j] + psc[j][i - 1];
            }

        solve();
        printf("%d\n", ans);
    }

    return 0;
}
