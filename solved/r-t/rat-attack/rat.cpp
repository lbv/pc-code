#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define SZ 1024

#define Zero(v) memset(v, 0, sizeof(v))

int pop[SZ + 1][SZ + 1];  // original rat populations
int hor[SZ + 1][SZ + 1];  // horizontal sums of radius d

int d, n;

int lox, hix, loy, hiy;

int X, Y, P;  // solution

#define Lo(c) (max(0, c))
#define Hi(c) (min(SZ, c))

void solve()
{
    Zero(hor);

    lox = Lo(lox - d);
    loy = Lo(loy - d);
    hix = Hi(hix + d);
    hiy = Hi(hiy + d);

    int a, b;
    for (int y = loy; y <= hiy; ++y) {
        for (int k = Lo(lox - d), K = Hi(lox + d); k <= K; ++k)
            hor[lox][y] += pop[k][y];

        for (int x = lox + 1; x <= hix; ++x) {
            a = x + d     <= SZ ? pop[x + d][y]     : 0;
            b = x - d - 1 >= 0  ? pop[x - d - 1][y] : 0;

            hor[x][y] = hor[x - 1][y] + a - b;
        }
    }

    P = -1;

    int pre, cur;

    for (int x = lox; x <= hix; ++x) {
        pre = 0;
        for (int k = Lo(loy - d), K = Hi(loy + d); k <= K; ++k)
            pre += hor[x][k];

        if (pre > P) X = x, Y = loy, P = pre;

        for (int y = loy + 1; y <= hiy; ++y) {
            a = y + d     <= SZ ? hor[x][y + d]     : 0;
            b = y - d - 1 >= 0  ? hor[x][y - d - 1] : 0;

            cur = pre + a - b;
            if (cur > P) X = x, Y = y, P = cur;
            pre = cur;
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &d, &n);

        Zero(pop);

        lox = loy = SZ + 1;
        hix = hiy = -1;
        while (n--) {
            int x, y, p;
            scanf("%d%d%d", &x, &y, &p);

            pop[x][y] = p;

            if (x < lox) lox = x;
            if (x > hix) hix = x;
            if (y < loy) loy = y;
            if (y > hiy) hiy = y;
        }

        solve();

        printf("%d %d %d\n", X, Y, P);
    }

    return 0;
}
