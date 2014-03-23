#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100
#define MAXP 1000000000000ULL

typedef unsigned long long u64;

u64 rand_u64()
{
    u64 r = rand();
    r <<= 32;
    r |= rand();
    return r;
}

void gen1()
{
    int P = rand() % 1000;
    printf("%d\n", P);
}

void gen2()
{
    int P = rand() % 1000000;
    printf("%d\n", P);
}

void gen3()
{
    u64 P = rand_u64() % (MAXP + 1);
    printf("%llu\n", P);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) {
        int n = rand() % 10;
        if (n < 3) gen1();
        else if (n < 6) gen2();
        else gen3();
    }

    return 0;
}
