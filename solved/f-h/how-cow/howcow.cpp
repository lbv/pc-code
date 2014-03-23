#include <cstdio>

int T, ncase, M, x1, y1, x2, y2, x, y;

int main(void)
{
    scanf("%d", &T);

    for (ncase = 1; ncase <= T; ncase++) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        scanf("%d", &M);

        printf("Case %d:\n", ncase);
        while (M--) {
            scanf("%d%d", &x, &y);

            if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }

    return 0;
}
