#include <cstdio>

typedef unsigned long long u64;

#define MINN 8
#define MAXN 13

int n;
u64 fact[14];

void prepare()
{
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i)
        fact[i] = fact[i-1] * i;
}

int main()
{
    prepare();

    while (true) {
        if (scanf("%d", &n) != 1) break;

        if (n < 0) {
            n = -n;
            if (n % 2 == 0)
                puts("Underflow!");
            else
                puts("Overflow!");
        }
        else if (n < MINN)
            puts("Underflow!");
        else if (n <= MAXN)
            printf("%llu\n", fact[n]);
        else
            puts("Overflow!");
    }

    return 0;
}
