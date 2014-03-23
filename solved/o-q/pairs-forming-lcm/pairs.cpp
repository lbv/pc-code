#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef unsigned long long u64;

typedef vector<int> IV;


//
// Number Theory
//
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 10000000;  // 10^7
    const int LMT =     3163;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
};
using namespace Num;


u64 n;


u64 solve()
{
    u64 ans = 1;
    int sn = sqrt(n);
    cFor (IV, p, primes) {
        int prime = *p;
        if (prime > sn) break; if (n % prime) continue;
        int e = 0; for (; n % prime == 0; e++, n /= prime);
        ans *= 2*e + 1;
        sn = sqrt(n);
    }
    if (n > 1) ans *= 3;

    return (ans + 1) / 2;
}

int main()
{
    prime_sieve();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%llu", &n);
        printf("Case %d: %llu\n", ++ncase, solve());
    }

    return 0;
}
