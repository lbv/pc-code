#include <cstdio>


#define MOD 1000000007


typedef long long i64;


int C;
int P, a;


void ext_euclid(int a, int b, int &x, int &y, int &gcd) {
    x = 0; y = 1; gcd = b;
    int m, n, q, r;
    for (int u=1, v=0; a != 0; gcd=a, a=r) {
        q = gcd / a; r = gcd % a;
        m = x-u*q; n = y-v*q;
        x=u; y=v; u=m; v=n;
    }
}

int mod_inv(int n, int m) {
    int x, y, gcd;
    ext_euclid(n, m, x, y, gcd);
    if (gcd == 1) return x % m;
    return 0;
}

int mod_pow(int _b, i64 e, int m) {
    i64 res = 1;
    for (i64 b=_b; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
    return res;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &C);

        i64 ans = 1;
        i64 fac = 1;
        while (C--) {
            scanf("%d%d", &P, &a);
            ans = (ans * mod_pow(P, a, MOD)) % MOD;

            i64 x = mod_pow(P, a, MOD) - 1 + MOD;
            x = x * (mod_inv(P - 1, MOD) + MOD) % MOD;

            i64 y = a + 1;
            y = y * mod_pow(P, a, MOD) % MOD;

            x = (x + y) % MOD;
            fac = fac * x % MOD;
        }

        ans = (ans + fac) % MOD;

        printf("Case %d: %lld\n", ++ncase, ans);
    }

    return 0;
}
