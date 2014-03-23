#include <cstdio>

int N, x, hi;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        hi = -1;

        while (N--) {
            scanf("%d", &x);
            if (x > hi) hi = x;
        }

        printf("Case %d: %d\n", ++ncase, hi);
    }

    return 0;
}
