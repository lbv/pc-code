#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> IV;

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    // nice number that guarantees more than 3501 primes
    const int MAX = 40000;
    const int LMT =   200;  // sqrt(MAX)
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

int n;

int josephus(int n, int p)
{
    if (n == 1) return 0;
    return (josephus(n-1, p + 1) + primes[p]) % n;
}

int main()
{
    prime_sieve();

    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        printf("%d\n", josephus(n, 0) + 1);
    }

    return 0;
}
