#include <cstdio>

typedef unsigned long long u64;

#define MOD 10000

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int K;
        scanf("%d", &K);

        int lo = K / 500 * 500;
        u64 val = 0;
        for (int i = lo + 1; i <= K; ++i)
            val = (val+1) * i % MOD;

        if (K <= 5)
            printf("Case %d: %llu\n", ++ncase, val+1);
        else
            printf("Case %d: %04llu\n", ++ncase, (val+1) % MOD);
    }

    return 0;
}
