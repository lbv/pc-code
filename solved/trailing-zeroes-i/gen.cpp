#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10000
#define MAXN 1000000000000ULL
#endif

#if 1
#define MAXT 5000
#define MAXN 1000000000000ULL
#endif


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
    u64 N = rand_u64() % MAXN + 1;
    if (rand() % 25 == 0) N = rand() % 1000 + 1;
    printf("%llu\n", N);
}

int main()
{
    int T = MAXT;
    printf("%d\n", T);

    while (T--)
        test_case();

    return 0;
}
