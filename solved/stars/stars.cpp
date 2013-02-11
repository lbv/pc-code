#include <cmath>
#include <cstdio>


typedef long long i64;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP   = 46341;  // sqrt(2^31)
const int SQRP   =   216;  // sqrt(MAX)
const int MAX_NP =  5435;  // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int primes[MAX_NP];
int nprimes;
void prime_sieve() {
    for (int i = 3; i <= SQRP; i += 2)
        if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
    primes[nprimes++] = 2;
    for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
}


int N;


int solve()
{
    i64 phi = N;

    int n = N;
    int s = sqrt(n);
    for (int i = 0; i < nprimes; ++i) {
        int &p = primes[i];
        if (p > s) break;

        if (n % p != 0) continue;
        phi -= phi/p;
        while (n % p == 0) n /= p;
        s = sqrt(n);
    }

    if (n != 1) phi -= phi/n;

    return phi / 2;
}

int main()
{
    prime_sieve();

    while (true) {
        if (scanf("%d", &N) != 1) break;
        printf("%d\n", solve());
    }

    return 0;
}
