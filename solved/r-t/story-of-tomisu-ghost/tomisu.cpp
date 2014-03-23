#include <cstdio>
#include <vector>
using namespace std;


#define MOD 10000019

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef long long i64;

typedef vector<int> IV;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 100000;  // 10^5
    const int LMT =    317;  // sqrt(MAX)
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
    i64 mod_pow(i64 _b, i64 e) {
        i64 res = 1;
        for (i64 b=_b; e; e >>= 1, b = b*b%MOD) if (e & 1) res = res*b%MOD;
        return res;
    }
};
using namespace Num;


int n, t;


int solve()
{
    i64 ans = 1;
    bool found = false;
    For (IV, p, primes) {
        int exp = pow_div_fact(n, *p);
        if (exp < t) break;
        found = true;
        ans *= mod_pow(*p, exp / t);
        ans %= MOD;
    }
    if (! found) return -1;
    return ans;
}

int main()
{
    prime_sieve();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &t);
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
