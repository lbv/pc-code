#include <cstdio>

typedef unsigned int u32;

u32 N;

u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%u", &N);
        printf("Case %d: %u\n", ++ncase, next_popcount(N));
    }

    return 0;
}
