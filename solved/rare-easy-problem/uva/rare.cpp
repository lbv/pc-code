#include <cstdio>

typedef unsigned long long u64;

u64 NM;  // N - M

int main()
{
    while (true) {
        scanf("%llu", &NM);
        if (NM == 0) break;

        if (NM % 9 == 0) {
            u64 N = NM/9 * 10;
            printf("%llu %llu\n", N-1, N);
        }
        else
            printf("%llu\n", NM*10/9);
    }

    return 0;
}
