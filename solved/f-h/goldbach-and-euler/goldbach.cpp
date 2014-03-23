#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


typedef vector<int>  IV;
typedef IV::iterator IVi;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 100000000;  // 10^8
    const int LMT =     10000;  // sqrt(MAX)
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


int n, p1, p2;

bool solve()
{
    if (n < 5) return false;
    if (n % 2 != 0) {
        if (is_prime(n - 2)) {
            p1 = 2;
            p2 = n - 2;
            return true;
        }
        return false;
    }

    IVi it = upper_bound(primes.begin(), primes.end(), n / 2);
    --it;

    if (*it == n / 2) --it;
    while (! is_prime(n - *it)) {
        if (it == primes.begin()) return false;
        --it;
    }

    p1 = *it;
    p2 = n - p1;

    return true;
}

int main()
{
    prime_sieve();

    while (true) {
        if (scanf("%d", &n) != 1) break;

        if (solve())
            printf("%d is the sum of %d and %d.\n", n, p1, p2);
        else
            printf("%d is not the sum of two primes!\n", n);
    }

    return 0;
}
