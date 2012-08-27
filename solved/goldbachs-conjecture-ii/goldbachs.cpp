#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXN 32768

#define Neg(v)  memset((v), -1, sizeof(v))


typedef vector<int> IV;

//
// Number Theory
//
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = MAXN;  // 2^15
    const int LMT =  182;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    int nprimes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
        nprimes = primes.size();
    }
    bool is_prime(int n) {
        if (n < 2 || (n > 2 && n % 2 == 0)) return false;
        return ! IsComp(n);
    }
}
using namespace Num;


int N;
int memo[MAXN + 1];


int solve(int n) {
    if (memo[n] >= 0)
        return memo[n];

    int half = n/2;
    int ways = 0;

    for (int i = 0; i < nprimes; i++) {
        int prime = primes[i];
        if (prime > half) break;
        if (is_prime(n - prime)) ++ways;
    }
    return memo[n] = ways;
}

int main(void)
{
    Neg(memo);
    prime_sieve();

    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        printf("%d\n", solve(N));
    }
    return 0;
}
