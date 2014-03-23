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
    const int MAX = 100;  // maximum N
    const int LMT =  10;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
    // Calculates the highest exponent of prime p that divides n!
    int pow_div_fact(int n, int p) {
        int sd = 0; for (int N=n; N; N /= p) sd += N % p; return (n-sd)/(p-1);
    }
};
using namespace Num;

int N;

int main()
{
    prime_sieve();

    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        printf("%3d! =", N);

        int cnt = 0;
        cFor (IV, pp, primes) {
            int p = *pp;
            if (p > N) break;

            if (++cnt > 15) {
                printf("\n      ");
                cnt = 0;
            }

            int times = pow_div_fact(N, p);
            printf("%3d", times);

        }
        putchar('\n');
    }

    return 0;
}
