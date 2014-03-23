#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 300
#define MAXA 1000000
#define MAXL 1000000000000ULL


typedef unsigned long long u64;


int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }

u64 rand_u64()
{
    u64 r = rand();
    r <<= 32;
    r |= rand();
    return r;
}

void test_case()
{
    int a = rand() % MAXA + 1;
    int b = rand() % MAXA + 1;

    if (rand() % 15 == 0) {
        a = rand() % 100 + 1;
        b = rand() % 100 + 1;
    }
    

    u64 lcm = a;
    lcm *= b;
    lcm /= gcd(a, b);

    u64 q = MAXL / lcm;
    u64 L = lcm * (rand_u64() % q + 1);

    if (rand() % 25 == 0)
        L = rand_u64();

    if (rand() % 10 == 0) {
        a = rand() % 1000 + 1;
        b = a * (rand() % 900 + 1);
        L = b * (rand_u64() % 100ULL + 1);
    }

    printf("%d %d %llu\n", a, b, L);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}
