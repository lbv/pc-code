#include <cstdio>
#include <cstdlib>
#include <ctime>

//#define MAXT 10000
#define MAXN 1000000000000LL

#define MAXT 100

typedef unsigned long long u64;

u64 rand_u64(u64 m)
{
    int n = rand() % 9 + 2;
    u64 r = 1;
    while (n--)
        r *= rand();
    return r % m;
}

void test_case()
{
    printf("%llu\n", rand_u64(MAXN));
}

int main()
{
    int T = MAXT;
    printf("%d\n", T);

    while (T--)
        test_case();

    return 0;
}
