#include <cstdio>
#include <cstring>

#define MAXM 200
#define MAXC 20
#define MAXK 20

#define Zero(v) memset(v, 0, sizeof(v))

// dp[i][j] is true iff it's possible to spend i money buying the first j
// garments
bool dp[MAXM + 1][MAXC + 1];

int M, C;
int Ks[MAXC];
int P[MAXC][MAXK];
int ans;

bool run_dp()
{
    Zero(dp);

    dp[0][0] = true;

    for (int j = 1; j <= C; ++j) {
        int g = j - 1;

        for (int k = 0; k < Ks[g]; ++k) {
            int p = P[g][k];

            for (int i = p; i <= M; ++i)
                if (i - p >= 0 && dp[i - p][j - 1])
                    dp[i][j] = true;
        }
    }

    for (int i = M; i >= 0; --i)
        if (dp[i][C]) {
            ans = i;
            return true;
        }
    return false;
}

int main()
{
    int N;
    scanf("%d", &N);

    while (N--) {
        scanf("%d%d", &M, &C);

        for (int i = 0; i < C; ++i) {
            scanf("%d", &Ks[i]);

            for (int j = 0; j < Ks[i]; ++j)
                scanf("%d", &P[i][j]);
        }

        if (run_dp())
            printf("%d\n", ans);
        else
            puts("no solution");
    }

    return 0;
}
