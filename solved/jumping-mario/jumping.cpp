#include <cstdio>

int N, hi, lo;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        hi = lo = 0;

        int n, prev;
        scanf("%d", &prev); --N;

        while (N--) {
            scanf("%d", &n);
            if (n > prev) ++hi;
            else if (n < prev) ++lo;
            prev = n;
        }

        printf("Case %d: %d %d\n", ++ncase, hi, lo);
    }

    return 0;
}
