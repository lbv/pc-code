#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long   i64;
typedef vector<int> IV;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Number Theory
#define ISCOMP(n)  (_c[(n)>>5]&(1<<((n)&31)))
#define SETCOMP(n) _c[(n)>>5]|=(1<<((n)&31))
namespace Num
{
    const int MAX = 1000000;  // sqrt(10^12)
    const int LMT = 1000;     // sqrt(MAX)
    int _c[(MAX>>5)+1];
    IV primes;
    void primeSieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!ISCOMP(i)) for (int j = i*i; j <= MAX; j+=i+i) SETCOMP(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!ISCOMP(i)) primes.push_back(i);
    }
}

int nbases(i64 n)
{
    using Num::primes;

    int ndiv = 1;
    int sn = sqrt(n);
    cFor (IV, p, primes) {
        int prime = *p;
        if (prime > sn) break; if (n % prime) continue;
        int e = 0; for (; n % prime == 0; e++, n /= prime);
        ndiv *= e + 1;
        sn = sqrt(n);
    }
    if (n > 1) ndiv *= 2;
    return ndiv - 1;
}

int main()
{
    Num::primeSieve();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        i64 N;
        scanf("%lld", &N);
        printf("Case %d: %d\n", ncase++, nbases(N));
    }

    return 0;
}
