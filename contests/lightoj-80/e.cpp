#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned long long u64;
typedef vector<int> IV;

#define MOD 1000000007

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000000;  // 10^6
    const int LMT =    1000;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void primeSieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
    u64 upow(u64 b, int e) {
        u64 res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
        return res;
    }
    void primeFactorization(u64 n, u64 &sumdiv, u64 &phi) {
        int sn = sqrt(n);
        sumdiv = 1;
        phi = n;
        cFor (IV, p, primes) {
            int prime = *p;
            if (prime > sn) break; if (n % prime) continue;
            int e = 0; for (; n % prime == 0; e++, n /= prime);
            sumdiv = sumdiv * (upow(prime, e+1)-1)/(prime-1) % MOD;
            phi -= phi/prime;
            sn = sqrt(n);
        }
        if (n > 1) {
            sumdiv = sumdiv * (n + 1) % MOD;
            phi -= phi/n;
        }
    }
    void eulerPhi(int a[], int N) {
        for (int i = 1; i <= N; i++) a[i] = i;
        for (int i = 2; i <= N; i += 2) a[i] = i/2;
        for (int i = 3; i <= N; i += 2)
            if (a[i] == i) {
                a[i]--; for (int j = i+i; j <= N; j += i) a[j] -= a[j]/i;
            }
    }
}
using namespace Num;

int main()
{
    primeSieve();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        u64 N;
        scanf("%llu", &N);

        u64 sumdiv, phi;
        primeFactorization(N, sumdiv, phi);

        printf("Case %d: %llu %llu\n", ++ncase, sumdiv, phi);
    }

    return 0;
}
