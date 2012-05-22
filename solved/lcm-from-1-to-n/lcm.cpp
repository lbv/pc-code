#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <utility>
#include <vector>
using namespace std;

typedef unsigned int   u32;
typedef long long      i64;

typedef pair<int, int> II;
typedef vector<II>     IIV;
typedef map<int, u32>  IUM;
typedef vector<int>    IV;

typedef IIV::const_iterator IIVci;

// Limit for the "base primes" (primes that go up to sqrt(10^8))
#define BASELMT 10000
#define MAXT    10000

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 100000000;  // 10^8
    const int LMT = 10000;      // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV basePrimes;
    void primeSieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        basePrimes.push_back(2);
        for (int i = 3; i <= BASELMT; i+= 2)
            if (!IsComp(i)) basePrimes.push_back(i);
    }
    u32 upow(u32 b, int e) {
        u32 res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
        return res;
    }
}
using namespace Num;

int data[MAXT + 1];

int main()
{
    primeSieve();

    // Set of factors to calculate LCM, in ascending order
    IIV factors;
    cFor (IV, p, basePrimes)
        for (i64 i = *p; i <= MAX; i *= *p)
            factors.push_back(II(i, *p));
    sort(factors.begin(), factors.end());
    printf("  there are %d factors\n", factors.size());

    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; i++) scanf("%d", &data[i]);

    IV sortedInput(data, data + T);
    sort(sortedInput.begin(), sortedInput.end());

    IUM sol;  // map for the solutions

    // index of numbers beyond BASELMT that are tested for primality
    int idx = basePrimes.back() + 2;

    // accumulated product of all required factors for LCMs
    u32 acc = 1;

    IIVci f = factors.begin();

    cFor (IV, i, sortedInput) {
        int n = *i;

        for (; f != factors.end() && f->first <= n; f++)
            acc *= f->second;

        while (idx <= n) {
            if (!IsComp(idx))
                acc *= idx;
            idx += 2;
        }

        sol[n] = acc;
    }

    int ncase = 1;
    for (int i = 0; i < T; i++)
        printf("Case %d: %u\n", ncase++, sol[data[i]]);

    return 0;
}
