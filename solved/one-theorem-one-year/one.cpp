#include <cstdio>
#include <vector>
using namespace std;


#define MAXK 500
#define MOD 1000000007


typedef long long i64;

typedef vector<int> IV;



//
// Number Theory
//
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 3600;  // The first 500 primes are under 3600
    const int LMT =   60;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(0);  // dummy value to shift the indices
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
}
using namespace Num;


// phi[i] is Phi(X) where X is the product of the first i primes
i64 phi[MAXK + 1];

// comb[i][j] is the summation of all combinations of products of i terms
// using the first j primes
i64 comb[MAXK + 1][MAXK + 1];

int K, P;


void prepare()
{
    prime_sieve();

    phi[0] = 1;
    for (int i = 1; i <= MAXK; ++i) {
        phi[i] = phi[i - 1] * (primes[i] - 1);
        phi[i] %= MOD;

        comb[1][i] = comb[1][i - 1] + primes[i];
    }

    for (int i = 2; i <= MAXK; ++i)
        for (int j = 1; j <= MAXK; ++j) {
            comb[i][j] += primes[j] * comb[i-1][j];
            comb[i][j] += comb[i][j - 1];
            comb[i][j] %= MOD;
        }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &K, &P);

        i64 ans = phi[P];

        if (K > P) {
            ans *= comb[K - P][P];
            ans %= MOD;
        }

        printf("Case %d: %lld\n", ++ncase, ans);
    }

    return 0;
}
