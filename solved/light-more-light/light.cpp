#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef unsigned int u32;

typedef vector<int> IV;

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 65536;  // 10^6
    const int LMT =   256;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
    int divs(u32 n) {
        int sn = sqrt(n);
        int divs = 1;
        cFor (IV, p, primes) {
            int prime = *p;
            if (prime > sn) break; if (n % prime) continue;
            int e = 0; for (; n % prime == 0; e++, n /= prime);
            divs *= e + 1;
            sn = sqrt(n);
        }
        if (n > 1) divs *= 2;
        return divs;
    }
}
using namespace Num;

u32 n;

int main()
{
    prime_sieve();

    while (true) {
        scanf("%u", &n);
        if (n == 0) break;

        if (divs(n) % 2 == 0)
            puts("no");
        else
            puts("yes");
    }

    return 0;
}
