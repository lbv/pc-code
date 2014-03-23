#include <algorithm>
#include <cstdio>
using namespace std;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP   = 20000000;  // 2*10^7
const int SQRP   =     4473;  // sqrt(MAX)
const int MAX_NP =  1498997;  // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int primes[MAX_NP];
int nprimes;
void prime_sieve() {
    for (int i = 3; i <= SQRP; i += 2)
        if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
    primes[nprimes++] = 2;
    for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
}

// Calculates the highest exponent of prime p that divides n!
int pow_div_fact(int n, int p) {
    int sd = 0; for (int N=n; N; N /= p) sd += N % p; return (n-sd)/(p-1);
}

template <typename TB, typename TE>
TB mod_pow(TB b, TE e, TB m) {
    TB res = 1; for (; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
    return res;
}


int N, M;


int solve()
{
    int ans = 1;

    int t2 = 0, t5 = 0;
    for (int i = 0; i < nprimes; ++i) {
        int &p = primes[i];
        if (p > N) break;

        int t = pow_div_fact(N, p) - pow_div_fact(N-M, p);

        if (p == 2) t2 = t;
        else if (p == 5) t5 = t;
        else
            ans = ans * mod_pow(1LL * p, t, 1LL * 10) % 10;
    }

    int t10 = min(t2, t5);

    if (t2 - t10 > 0)
        ans = ans * mod_pow(2, t2 - t10, 10) % 10;
    if (t5 - t10 > 0)
        ans = ans * mod_pow(5, t5 - t10, 10) % 10;

    return ans;
}

int main()
{
    prime_sieve();

    while (true) {
        if (scanf("%d%d", &N, &M) != 2) break;
        printf("%d\n", solve());
    }

    return 0;
}
