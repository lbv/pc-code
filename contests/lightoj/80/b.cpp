#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned long long u64;
typedef vector<int> IV;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000000;  // 10^6
    const int LMT = 1000;     // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void primeSieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
    void primeFactorization(u64 n, int &ndiv) {
        int sn = sqrt(n);
        ndiv = 0;
        cFor (IV, p, primes) {
            int prime = *p;
            if (prime > sn) break; if (n % prime) continue;
            int e = 0; for (; n % prime == 0; e++, n /= prime);
            ndiv += e;
            sn = sqrt(n);
        }
        if (n > 1) ++ndiv;
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
        u64 N;
        scanf("%llu", &N);

        int ndiv;
        primeFactorization(N, ndiv);

        printf("Case %d: %s\n", ++ncase, ndiv % 2 == 0 ? "Shifu" : "Panda");
    }

    return 0;
}
