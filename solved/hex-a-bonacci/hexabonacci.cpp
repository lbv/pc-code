#include <cstdio>

typedef long long i64;

#define MOD 10000007
#define MAXN 10000

i64 hex[MAXN + 1];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        for (int i = 0; i < 6; i++) scanf("%lld", &hex[i]);
        int n;
        scanf("%d", &n);

        int res;
        if (n < 6) res = hex[n] % MOD;
        else {
            hex[6] = 0;
            for (int i = 0; i < 6; i++) hex[6] += hex[i];
            hex[6] %= MOD;

            for (int i = 7, j = 0; i <= n; i++, j++)
                hex[i] = (hex[i-1]*2 - hex[j]) % MOD;

            res = hex[n] < 0 ? hex[n] + MOD : hex[n];
        }

        printf("Case %d: %d\n", ncase++, res);
    }

    return 0;
}
