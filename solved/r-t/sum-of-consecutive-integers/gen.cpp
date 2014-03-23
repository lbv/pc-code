#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 200
#define MAXN 100000000000000LL
#define PRE  1
#endif

#if 1
#define MAXT 200
#define MAXN 100000000000000LL
#define PRE  0
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
    if (rand() % 20 == 0) N = rand() % 1000 + 1;

    printf("%llu\n", N);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

#if PRE
    for (int i = 0; i < 10; ++i) {
        printf("%llu\n%llu\n", 1LL + i, MAXN - i);
        T -= 2;
    }
#endif

    while (T--) test_case();

    return 0;
}
