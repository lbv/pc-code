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
    const int MAX = 1000;  // sqrt(10^6)
    const int LMT = 32;    // sqrt(MAX)
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

u64 gcd(u64 a, u64 b) { for (u64 c = a%b; c; a=b,b=c,c=a%b); return b; }

int main()
{
    primeSieve();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        u64 a, b, L;
        scanf("%llu%llu%llu", &a, &b, &L);

        u64 l = a*b/gcd(a, b);  // LCM(a, b)
        if (L % l != 0) {
            printf("Case %d: impossible\n", ncase++);
            continue;
        }

        u64 f = L/l;
        u64 ans = f;

        int sa = sqrt(a);
        int sb = sqrt(b);
        cFor (IV, p, primes) {
            int prime = *p;
            if (prime > sa && prime > sb) break;

            u64 fa = 1;
            if (a % prime == 0) {
                while (a % prime == 0) {
                    a  /= prime;
                    fa *= prime;
                }
                sa = sqrt(a);
            }

            u64 fb = 1;
            if (b % prime == 0) {
                while (b % prime == 0) {
                    b  /= prime;
                    fb *= prime;
                }
                sb = sqrt(b);
            }
            if (f % prime == 0)
                ans *= max(fa, fb);
        }
        if (a > 1 && f % a == 0) ans *= a;
        if (b > 1 && b != a && f % b == 0) ans *= b;

        printf("Case %d: %llu\n", ncase++, ans);
    }

    return 0;
}
