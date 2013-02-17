#include <cmath>
#include <cstdio>


typedef long long i64;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP   = 30000000;  // sqrt(9E14)
const int SQRP   =     5478;  // sqrt(MAX)
const int MAX_NP =  2195542;  // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int primes[MAX_NP];
int nprimes;
void prime_sieve() {
    for (int i = 3; i <= SQRP; i += 2)
        if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
    primes[nprimes++] = 2;
    for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
}


i64 N;


int solve()
{
    if (N == 0) return 1;
    while (N % 2 == 0) N /= 2;

    int ans = 1;

    int sn = sqrt(N);
    for (int i = 1; i < nprimes; ++i) {
        int &p = primes[i];
        if (p > sn) break;
        if (N % p != 0) continue;

        int e = 0;
        while (N % p == 0) N /= p, ++e;
        ans *= e + 1;

        sn = sqrt(N);
    }
    if (N > 1) ans *= 2;

    return ans;
}

int main()
{
    prime_sieve();

    while (true) {
        if (scanf("%lld", &N) != 1) break;
        printf("%d\n", solve());
    }

    return 0;
}
