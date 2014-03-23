#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 10000
#define MOD  1000000000000000000ULL

typedef unsigned long long u64;

u64 rand_u64()
{
    u64 r = rand();
    r <<= 32;
    r |= rand();
    return r;
}

void test_case()
{
    u64 n = rand_u64() % MOD + 1;

    if (rand() % 50 == 0)
        n = rand() % 1000 + 1;

    printf("%llu\n", n);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    for (int i = 1; i <= 100; ++i) {
        printf("%d\n", i);
        --T;
    }

    while (T--) test_case();

    return 0;
}
