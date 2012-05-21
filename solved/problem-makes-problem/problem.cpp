#include <cstdio>

typedef long long i64;

#define MAXN 1000000
#define MOD 1000000007

#define Sc(t,v) static_cast<t>(v)

namespace Num {
    void extEuclid(int a, int b, int &x, int &y, int &gcd) {
        x = 0; y = 1; gcd = b;
        int m, n, q, r;
        for (int u=1, v=0; a != 0; gcd=a, a=r) {
            q = gcd / a; r = gcd % a;
            m = x-u*q; n = y-v*q;
            x=u; y=v; u=m; v=n;
        }
    }
    int modInv(int n, int m) {
        int x, y, gcd;
        extEuclid(n, m, x, y, gcd);
        if (gcd == 1) return x % m;
        return 0;
    }
}


int factmod[2*MAXN];

void prepare() {
    factmod[0] = 1;
    for (int i = 1, I=2*MAXN; i < I; i++)
        factmod[i] = (Sc(i64, factmod[i-1]) * i) % MOD;
}

int choose(int n, int k)
{
    using namespace Num;
    int f1 = factmod[n];
    int f2 = modInv(factmod[k], MOD);
    int f3 = modInv(factmod[n-k], MOD);

    i64 res = (Sc(i64, f1) * f2) % MOD;
    res = (res * f3) % MOD;
    if (res < 0) res += MOD;

    return Sc(int, res);
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n, k;
        scanf("%d%d", &n, &k);
        k--;
        n += k;

        int c;
        if (k > n) c = 0;
        else c = choose(n, k);

        printf("Case %d: %d\n", ncase++, c);
    }

    return 0;
}
