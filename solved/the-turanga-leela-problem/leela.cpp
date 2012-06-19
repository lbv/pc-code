#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

typedef vector<int> IV;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 31623;  // sqrt(10^9)
    const int LMT =   178;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
}
using namespace Num;

int a, b;

int solve()
{
    int n = abs(a-b);
    if (n == 0)
        return a;
    if (n == 1)
        return 1;

    int div = 1;

    int sn = sqrt(n);
    cFor (IV, p, primes) {
        int prime = *p;
        if (prime > sn) break; if (n % prime) continue;
        int e = 0; for (; n % prime == 0; e++, n /= prime);
        div *= e + 1;
        sn = sqrt(n);
    }
    if (n > 1) div *= 2;

    return div;
}

int main()
{
    prime_sieve();
    while (true) {
        scanf("%d%d", &a, &b);
        if (a == 0) break;

        printf("%d\n", solve());
    }

    return 0;
}
