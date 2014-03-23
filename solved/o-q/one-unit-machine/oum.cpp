#include <cstdio>


#define MAXN 1000
#define MOD  1000000007
#define MAXU 1000000


typedef long long i64;


int n;
int ks[MAXN];
i64 fact[MAXU + 1];


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

int choose(int n, int k) {
    if (k > n) return 0;
    i64 num = fact[n];
    i64 den = fact[k] * fact[n-k] % MOD;
    i64 ans = num * mod_inv(den, MOD) % MOD;
    if (ans < 0) ans += MOD;
    return ans;
}

int solve()
{
    i64 ans = 1;

    int m = ks[0];  // number of units processed so far

    for (int i = 1; i < n; ++i) {
        // number of "buckets" to place the next units
        int p = m + 1;

        // number of units to place in the buckets, subtracting one that
        // has to be left for last
        int q = ks[i] - 1;

        int ways = choose(p + q - 1, p - 1);

        ans = ans * ways % MOD;

        m += ks[i];
    }

    return ans;
}

void prepare()
{
    i64 x = 1;
    fact[0] = 1;

    for (int i = 1; i <= MAXU; ++i) {
        x = x * i % MOD;
        fact[i] = x;
    }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", &ks[i]);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
