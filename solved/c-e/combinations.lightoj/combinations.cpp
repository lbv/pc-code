#include <cstdio>

typedef unsigned int u32;
typedef long long    i64;

#define MAXN 1000000
#define MOD  1000003

#define Sc(t,v) static_cast<t>(v)

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 nextU32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

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
        return x % m;
    }
}


int factmod[MAXN + 1];

void prepare() {
    factmod[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        factmod[i] = (Sc(i64, factmod[i-1]) * i) % MOD;
}

int choose(int n, int k)
{
    using namespace Num;
    int f1 = factmod[n];
    int f2 = modInv(factmod[k], MOD);
    int f3 = modInv(factmod[n-k], MOD);
    
    i64 res = (Sc(i64, f1) * f2 % MOD) * f3 % MOD;
    if (res < 0) res += MOD;

    return res;
}

int main()
{
    prepare();

    Reader rr;
    int T = rr.nextU32();;

    int ncase = 1;
    while (T--) {
        int n = rr.nextU32();
        int k = rr.nextU32();

        printf("Case %d: %d\n", ncase++, choose(n, k));
    }

    return 0;
}
