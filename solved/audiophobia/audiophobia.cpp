#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXC 100
#define INF  1000000000

int g[MAXC + 1][MAXC + 1];

int main()
{
    bool first = true;
    int ncase = 0;
    while (true) {
        int C, S, Q;
        scanf("%d%d%d", &C, &S, &Q);
        if (C == 0 && S == 0 && Q == 0) break;

        for (int i = 1; i <= C; ++i)
            for (int j = 1; j <= C; ++j)
                g[i][j] = INF;

        while (S--) {
            int c1, c2, d;
            scanf("%d%d%d", &c1, &c2, &d);
            g[c1][c2] = d;
            g[c2][c1] = d;
        }

        for (int k = 1; k <= C; ++k)
            for (int i = 1; i <= C; ++i)
                for (int j = 1; j <= C; ++j)
                    g[i][j] = min(g[i][j], max(g[i][k], g[k][j]));


        if (first) first = false;
        else putchar('\n');

        printf("Case #%d\n", ++ncase);

        while (Q--) {
            int c1, c2;
            scanf("%d%d", &c1, &c2);

            if (g[c1][c2] == INF)
                printf("no path\n");
            else
                printf("%d\n", g[c1][c2]);
        }
    }

    return 0;
}
