#include <cstdio>

int T, ncase;
int n, area;
int x1, y1, z1, x2, y2, z2;
int xx1, yy1, zz1, xx2, yy2, zz2;

int main(void)
{
    scanf("%d", &T);

    for (ncase = 1; ncase <= T; ncase++) {
        scanf("%d", &n);
        
        x1 = y1 = z1 = 0;
        x2 = y2 = z2 = 1010;

        while (n--) {
            scanf("%d%d%d%d%d%d", &xx1, &yy1, &zz1, &xx2, &yy2, &zz2);
            if (xx1 > x1) x1 = xx1;
            if (yy1 > y1) y1 = yy1;
            if (zz1 > z1) z1 = zz1;

            if (xx2 < x2) x2 = xx2;
            if (yy2 < y2) y2 = yy2;
            if (zz2 < z2) z2 = zz2;
        }

        area = (x2-x1) * (y2-y1) * (z2-z1);
        printf("Case %d: %d\n", ncase, area > 0 ? area : 0);
    }

    return 0;
}
