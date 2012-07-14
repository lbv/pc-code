#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#define MAXT 4000
#define MAXA 1000000000000ULL
#define MAXB 1000000ULL


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
    u64 a = rand_u64() % MAXA + 1;
    u64 sa = sqrt(a);

    u64 b;    
    if (rand() % 5 == 0)
        b = rand_u64() % MAXB + 1;
    else
        b = rand_u64() % sa + 1;

    printf("%llu %llu\n", a, b);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}
