#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef unsigned int u32;

#define MAXL 10

// dp0[i] has the amount of zeros in numbers with exactly i digits
// (including numbers that start with 0)
u32 dp0[MAXL];

// dpa[i] has the accumulated number of zeros of numbers with up to i digits
u32 dpa[MAXL];

// Powers of ten, for convenience
u32 tens[MAXL];

void prepare()
{
    tens[0] = 1;
    for (int i = 1; i < MAXL; i++)
        tens[i] = tens[i-1]*10;
    dp0[0] = 0;
    dp0[1] = 1;
    dpa[0] = 0;
    dpa[1] = 1;
    for (int i = 2; i < MAXL; i++) {
        dp0[i] = 10*dp0[i-1] + tens[i-1];
        dpa[i] = dpa[i-1] + 9*dp0[i-1];
    }
}

u32 zeroes(char *n, int l, bool z)
{
    if (l == 0) return 0;
    if (l == 1) return 1;

    int d = *n - '0';
    u32 res;
    if (z) {
        u32 rest = d==0 ? atoi(n+1)+1 : tens[l-1];
        res = d*dp0[l-1] + rest;
    }
    else
        res = (d-1) * dp0[l-1];

    return res + zeroes(n+1, l-1, true);
}

u32 acumzeroes(u32 n)
{
    char ns[MAXL + 1];
    sprintf(ns, "%u", n);

    size_t len = strlen(ns);
    return dpa[len - 1] + zeroes(ns, len, false);
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        u32 m, n;
        scanf("%u%u", &m, &n);

        if (m == 0)
            printf("Case %d: %u\n", ncase++, acumzeroes(n));
        else
            printf("Case %d: %u\n", ncase++, acumzeroes(n) - acumzeroes(m-1));
    }

    return 0;
}
