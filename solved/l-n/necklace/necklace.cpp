#include <cstdio>

#define MOD 1000000007

typedef long long i64;

int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }

int mod_pow(int _b, i64 e, int m) {
    i64 res = 1;
    for (i64 b=_b; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
    return res;
}

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

int solve(int n, int k)
{
    i64 sum = mod_pow(k, n, MOD);

    for (int i = 1; i < n; ++i)
        sum += mod_pow(k, gcd(n, i), MOD);

    sum = sum % MOD * mod_inv(n, MOD) % MOD;
    if (sum < 0) sum += MOD;
    return sum;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n, K;
        scanf("%d%d", &n, &K);

        printf("Case %d: %d\n", ++ncase, solve(n, K));
    }

    return 0;
}
