#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long i64;
typedef vector<bool> BV;
typedef vector<int>  IV;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 46341;  // sqrt(2^31)
    const int LMT =   216;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
    // Finds prime numbers between a and b, using basic primes up to sqrt(b)
    void prime_seg_sieve(i64 a, i64 b, IV &seg_primes) {
        BV pmap(b - a + 1, true);
        i64 sqr_b = sqrt(b);
        cFor (IV, pp, primes) {
            int p = *pp;
            if (p > sqr_b) break;
            for (i64 j = (a+p-1)/p, v=(j==1?p+p:j*p); v <= b; v += p)
                pmap[v-a] = false;
        }
        seg_primes.clear();
        if (a == 1) pmap[0] = false;
        for (int i = 0, I = b - a + 1; i < I; ++i)
            if (pmap[i])
                seg_primes.push_back(a + i);
    }
}
using namespace Num;

int L, U;

int a1, a2;  // closest pair
int b1, b2;  // more distant pair

bool solve()
{
    IV seg_primes;
    prime_seg_sieve(L, U, seg_primes);

    int sz = seg_primes.size();

    if (sz < 2) return false;

    int close = seg_primes[sz - 1] - seg_primes[0] + 1;
    int distant = 0;
    for (int i = 0, j = 1; j < sz; ++i, ++j) {
        int diff = seg_primes[j] - seg_primes[i];

        if (diff < close)
            a1 = seg_primes[i], a2 = seg_primes[j], close = diff;

        if (diff > distant)
            b1 = seg_primes[i], b2 = seg_primes[j], distant = diff;
    }

    return true;
}

int main()
{
    prime_sieve();

    while (true) {
        if (scanf("%d%d", &L, &U) != 2) break;

        if (solve())
            printf("%d,%d are closest, %d,%d are most distant.\n",
                   a1, a2, b1, b2);
        else
            puts("There are no adjacent primes.");
    }

    return 0;
}
