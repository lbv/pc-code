#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 8000
#define MAXB 1000000000000LL
#endif

#if 1
#define MAXT 200
#define MAXB 100000000000LL
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
    u64 B = rand_u64() % MAXB + 1;
    u64 A = rand_u64() % B + 1;

    if (rand() % 25 == 0) {
        B = rand() % 1000 + 1;
        A = rand() % B + 1;
    }

    printf("%llu %llu\n", A, B);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

/*
    for (int B = 1; B <= 10; ++B)
        for (int A = 1; A <= 10; ++A) {
            printf("%d %llu\n", A, MAXB - B);
            --T;
        }
*/
    for (u64 B = 1; B <= MAXB; B *= 10) {
        printf("1 %llu\n", B);
        --T;
    }

    while (T--) test_case();

    return 0;
}
