#include <cstdio>

typedef unsigned long long u64;

// 20! > 10^18
#define MAXF 19

u64 fact[MAXF + 1];
int used[MAXF + 1];

void prepare()
{
    fact[0] = 1;
    for (int i = 1; i <= MAXF; ++i)
        fact[i] = fact[i-1] * i;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        u64 n;
        scanf("%llu", &n);

        int u = 0;
        for (int i = MAXF; i >= 0; --i)
            if (n >= fact[i]) {
                used[u++] = i;
                n -= fact[i];
            }

        printf("Case %d: ", ++ncase);
        if (n == 0) {
            printf("%d!", used[--u]);
            for (int i = u - 1; i >= 0; --i)
                printf("+%d!", used[i]);
            putchar('\n');
        }
        else
            puts("impossible");
    }

    return 0;
}
