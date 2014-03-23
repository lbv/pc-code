#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 200
#define MAXI 100000000000000000ULL

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
    u64 i = rand_u64() % MAXI;
    u64 j = rand_u64() % MAXI;

    if (rand() % 5 == 0)
        i = rand() % 10000;
    if (rand() % 5 == 0)
        j = rand() % 10000;

    printf("%llu %llu\n", i, j);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}
