#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned long long u64;
typedef vector<int> IV;


#define Sc(t,v) static_cast<t>(v)
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000000;  // 10^6
    const int LMT =    1000;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void primeSieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }

    void primeFactorization(u64 n, u64 &ans) {
        if (n == 1) { ans = 1; return; }
        int sn = sqrt(n);
        ans = 1;
        cFor (IV, p, primes) {
            int prime = *p;
            if (prime > sn) break; if (n % prime) continue;
            int e = 0;
            for (; n % prime == 0; ++e, n /= prime);
            ans *= e + 1;
//            printf("  :: %d^%d\n", prime, e);
            sn = sqrt(n);
        }
        if (n > 1) {
            ans *= 2;
//            printf("  :: %llu^1\n", n);
        }
        if (ans % 2 != 0) ++ans;
        ans /= 2;
    }
}
using namespace Num;

int main()
{
    primeSieve();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        u64 W;
        scanf("%llu", &W);

        u64 ans;
        primeFactorization(W, ans);

        printf("Case %d: %llu\n", ++ncase, ans);
    }

    return 0;
}
