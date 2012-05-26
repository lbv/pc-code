#include <cstdio>

typedef unsigned int u32;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        u32 A, B;
        scanf("%u%u", &A, &B);

        printf("Case %d: %u\n", ++ncase, 2*B/3 - 2*(A-1)/3);
    }

    return 0;
}
