#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef long long i64;

typedef vector<bool> BV;
typedef vector<int>  IV;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 46341;  // sqrt(2^31)
    const int LMT =   216;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }

    int prime_seg_sieve(i64 a, i64 b) {
        BV pmap(b - a + 1, true);
        int sqr_b = sqrt(b);
        For (IV, pp, primes) {
            int p = *pp;
            if (p > sqr_b) break;
            for (i64 j = (a+p-1)/p, v=(j==1?p+p:j*p); v <= b; v += p)
                pmap[v-a] = false;
        }
        int cnt = 0;
        for (int i = a%2 ? 0 : 1, I = b - a + 1; i < I; i += 2)
            if (pmap[i])
                ++cnt;
        return cnt;
    }
}
using namespace Num;


int a, b;


int solve()
{
    int ans = 0;

    if (b < 2) return 0;
    if (a <= 2) {
        ++ans;
        a = 3;
        if (a > b) return ans;
    }

    ans += prime_seg_sieve(a, b);
    return ans;
}

int main()
{
    prime_sieve();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &a, &b);
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
