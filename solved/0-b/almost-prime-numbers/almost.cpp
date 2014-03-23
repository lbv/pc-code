#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned long long u64;

typedef vector<int> IV;
typedef vector<u64> UV;

typedef UV::iterator UVi;

// 10^12
#define LIM 1000000000000LL

#define Sc(t,v) static_cast<t>(v)
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000000;  // 10^6
    const int LMT = 1000;    // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void primeSieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
}
using namespace Num;

UV ap;  // vector of almost primes

void prepare()
{
    primeSieve();

    cFor (IV, p, primes) {
        int prime = *p;

        for (u64 a = Sc(u64, prime)*prime; a <= LIM; a *= prime)
            ap.push_back(a);
    }

    sort(ap.begin(), ap.end());
}

int main()
{
    prepare();

    int N;
    scanf("%d", &N);

    while (N--) {
        u64 lo, hi;
        scanf("%llu%llu", &lo, &hi);

        UVi i = lower_bound(ap.begin(), ap.end(), lo);
        UVi j = upper_bound(ap.begin(), ap.end(), hi);

        printf("%d\n", j-i);
    }

    return 0;
}
