#include <cstdio>

typedef unsigned long long u64;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        u64 C;  // C = A - B
        scanf("%llu", &C);

        if (C % 9 == 0) {
            u64 A = C/9 * 10;
            printf("Case %d: %llu %llu\n", ncase++, A-1, A);
        }
        else
            printf("Case %d: %llu\n", ncase++, C*10/9);
    }

    return 0;
}
