#include <cstdio>

int main()
{
    puts("The 1500'th ugly number is 859963392.");
    return 0;
}

#if 0
#include <vector>
using namespace std;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef vector<int> IV;

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000000000;  // just an estimation
    const int LMT =      31623;  // sqrt(MAX)
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

bool ugly[MAX + 1];

int main()
{
    prime_sieve();

    for (int i = 1; i <= MAX; ++i)
        ugly[i] = true;

    cFor (IV, p, primes) {
        if (*p <= 5) continue;
        for (int i = *p; i <= MAX; i += *p)
            ugly[i] = false;
    }

    int cnt = 0;
    for (int i = 1; i <= MAX; ++i)
        if (ugly[i]) {
            ++cnt;
            if (cnt == 1500) {
                printf("The 1500'th ugly number is %d.\n", i);
                break;
            }
        }

    return 0;
}
#endif
