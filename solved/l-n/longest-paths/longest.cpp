#include <cstdio>
#include <cstring>

#define MAXN 100

#define Zero(v) memset(v, 0, sizeof(v))

int g[MAXN + 1][MAXN + 1];

void floyd(int N)
{
    for (int k = 1; k <= N; k++)
        for(int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++) {
                if (g[i][k] == 0 || g[k][j] == 0) continue;
                int t = g[i][k] + g[k][j];
                if (t > g[i][j]) g[i][j] = t;
            }
}

int main()
{
    int n, s, p, q;

    int ncase = 0;
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;
        scanf("%d", &s);

        Zero(g);

        while (true) {
            scanf("%d%d", &p, &q);
            if (p == 0 && q == 0) break;
            g[p][q] = 1;
        }

        floyd(n);

        int len = 0;
        int dest = 0;

        for (int i = 1; i <= n; ++i)
            if (g[s][i] > len) {
                len = g[s][i];
                dest = i;
            }

        printf("Case %d: "
               "The longest path from %d has length %d, finishing at %d.\n\n",
               ++ncase, s, len, dest);
    }

    return 0;
}

