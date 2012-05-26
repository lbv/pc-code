#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

typedef long long      i64;
typedef pair<int, int> II;
typedef vector<II>     IIV;
typedef vector<int>    IV;

#define MOD 1000000007

#define Sc(t,v) static_cast<t>(v)
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Number Theory
#define ISCOMP(n)  (_c[(n)>>5]&(1<<((n)&31)))
#define SETCOMP(n) _c[(n)>>5]|=(1<<((n)&31))
namespace Num
{
    const int MAX = 46341;  // sqrt(2^31)
    const int LMT = 216;    // sqrt(MAX)
    int _c[(MAX>>5)+1];
    IV primes;
    void primeSieveList() {
        SETCOMP(0); SETCOMP(1);
        for (int i = 3; i <= LMT; i += 2)
            if (!ISCOMP(i)) for (int j = i*i; j <= MAX; j+=i+i) SETCOMP(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!ISCOMP(i)) primes.push_back(i);
    }
    void primeFactorization(int n, IIV &f) {
        int sn = Sc(int, sqrt(n));
        cFor (IV, p, primes) {
            int prime = *p;
            if (prime > sn) break; if (n % prime != 0) continue;
            int e = 0; for (; n % prime == 0; e++, n /= prime);
            f.push_back(II(prime, e));
            sn = Sc(int, sqrt(n));
        }
        if (n > 1) f.push_back(II(n, 1));
    }

    int modPow(int _b, i64 e, int m) {
        i64 res = 1;
        for (i64 b=_b; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
        return res;
    }
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

IIV fact;

int result(int n, int m)
{
    using namespace Num;

    fact.clear();
    primeFactorization(n, fact);

    i64 sum = 1;
    cFor (IIV, f, fact) {
        int prime = f->first;
        int e     = f->second;

        int f1 = modPow(prime, Sc(i64, m)*e+1, MOD) - 1;
        int f2 = modInv(prime - 1, MOD);

        sum = (sum*f1 % MOD) * f2 % MOD;
    }
    if (sum < 0) sum += MOD;
    return sum;
}

int main()
{
    Num::primeSieveList();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        printf("Case %d: %d\n", ncase++, result(n, m));
    }

    return 0;
}
