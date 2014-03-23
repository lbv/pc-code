#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define SZ 1000000

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef unsigned long long u64;

typedef vector<int> IV;
typedef vector<u64> UV;

typedef UV::iterator UVi;

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000000;  // 10^6
    const int LMT =    1000;  // sqrt(MAX)
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

u64 a, b, top;
int ans;

void divisors(u64 n, UV &ds)
{
    ds.clear();
    ds.push_back(1);
    int sn = sqrt(n);
    cFor(IV, pp, primes) {
        int p = *pp;
        if (p > sn) break;
        if (n % p != 0) continue;

        UV aux(ds.begin(), ds.end());
        int q = 1;
        while (n % p == 0) {
            q *= p;
            n /= p;
            cFor(UV, v, ds) aux.push_back(*v * q);
        }
        sn = sqrt(n);
        ds = aux;
    }
    if (n > 1) {
        UV aux(ds.begin(), ds.end());
        cFor(UV, v, ds) aux.push_back(*v * n);
        ds = aux;
    }
}

int solve()
{
    UV divs;
    divisors(a, divs);

    sort(divs.begin(), divs.end());

    u64 top = sqrt(a);
    if (top*top == a) --top;

    UVi lo = lower_bound(divs.begin(), divs.end(), b);
    UVi hi = upper_bound(lo, divs.end(), top);

    return hi - lo;
}

int main()
{
    prime_sieve();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%llu%llu", &a, &b);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
