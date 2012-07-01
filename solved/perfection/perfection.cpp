#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef vector<int> IV;

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 245;  // sqrt(60000)
    const int LMT =  16;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
    void divisors(int n, IV &ds)
    {
        ds.clear();
        ds.push_back(1);
        int sn = sqrt(n);
        cFor(IV, pp, primes) {
            int p = *pp;
            if (p > sn) break;
            if (n % p != 0) continue;
            IV aux(ds.begin(), ds.end());
            int q = 1;
            while (n % p == 0) {
                q *= p; n /= p;
                cFor(IV, v, ds) aux.push_back(*v * q);
            }
            sn = sqrt(n); ds = aux;
        }
        if (n > 1) {
            IV aux(ds.begin(), ds.end());
            cFor(IV, v, ds) aux.push_back(*v * n);
            ds = aux;
        }
    }
}
using namespace Num;

int n;

int main()
{
    prime_sieve();

    puts("PERFECTION OUTPUT");
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        IV divs;
        divisors(n, divs);
        int sum = 0;

        cFor(IV, d, divs)
            if (*d < n)
                sum += *d;

        printf("%5d  ", n);

        if (sum == n)
            puts("PERFECT");
        else if (sum < n)
            puts("DEFICIENT");
        else
            puts("ABUNDANT");
    }
    puts("END OF OUTPUT");

    return 0;
}
