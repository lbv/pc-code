#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef pair<int, int> II;
typedef vector<int>    IV;
typedef vector<II>     IIV;


//
// Number Theory
//
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1 << 16;  // 2^16
    const int LMT =  1 << 8;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
    void prime_factorize(int n, IIV &f) {
        int sn = sqrt(n);
        cFor (IV, p, primes) {
            int prime = *p;
            if (prime > sn) break; if (n % prime) continue;
            int e = 0; for (; n % prime == 0; e++, n /= prime);
            f.push_back(II(prime, e));
            sn = sqrt(n);
        }
        if (n > 1) f.push_back(II(n, 1));
    }
    // Calculates the highest exponent of prime p that divides n!
    int pow_div_fact(int n, int p) {
        int sd = 0; for (int N=n; N; N /= p) sd += N % p; return (n-sd)/(p-1);
    }
}
using namespace Num;


int n, m;

bool solve()
{
    if (m == 1) return true;
    if (m == 0) return false;

    IIV factors;
    prime_factorize(m, factors);

    cFor (IIV, f, factors)
        if (pow_div_fact(n, f->first) < f->second)
            return false;

    return true;
}

int main()
{
    prime_sieve();

    while (true) {
        if (scanf("%d%d", &n, &m) != 2) break;

        printf("%d %s %d!\n", m, solve() ? "divides" : "does not divide", n);
    }

    return 0;
}
