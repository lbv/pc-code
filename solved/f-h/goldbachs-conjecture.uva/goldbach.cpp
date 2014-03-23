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
    bool is_prime(int n) {
        if (n < 2 || n % 2 == 0) return false;
        return ! IsComp(n);
    }
}
using namespace Num;


int n;
int a, b;

void solve()
{
    cFor (IV, pp, primes) {
        int p = *pp;
        if (is_prime(n - p)) {
            a = p;
            b = n - p;
            return;
        }
    }
}

int main()
{
    prime_sieve();

    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        solve();
        printf("%d = %d + %d\n", n, a, b);
    }

    return 0;
}
