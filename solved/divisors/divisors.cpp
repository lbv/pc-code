#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef vector<int> IV;


//
// Number Theory
//
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 31623;  // sqrt(10^9)
    const int LMT =   178;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
};
using namespace Num;


int L, U;
int P, D;


int nod(int n)
{
    int ans = 1;

    int sn = sqrt(n);
    cFor (IV, p, primes) {
        int prime = *p;
        if (prime > sn) break; if (n % prime) continue;
        int e = 0; for (; n % prime == 0; e++, n /= prime);

        ans *= e + 1;
        sn = sqrt(n);
    }
    if (n > 1) ans *= 2;

    return ans;
}

void solve()
{
    D = 0;
    for (int i = L; i <= U; ++i) {
        int n = nod(i);
        if (n > D) {
            P = i;
            D = n;
        }
    }
}

int main()
{
    prime_sieve();

    int N;
    scanf("%d", &N);

    while (N--) {
        scanf("%d%d", &L, &U);

        solve();
        printf("Between %d and %d, %d has a maximum of %d divisors.\n",
               L, U, P, D);
    }

    return 0;
}
