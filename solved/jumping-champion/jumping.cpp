#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

// 1.26 * 10^6 / log(10^6)
#define MAXCNT 91202

#define Zero(v) memset(v, 0, sizeof(v))

typedef vector<int>  IV;
typedef IV::iterator IVi;

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000000;  // 10^6
    const int LMT =    1000;  // sqrt(MAX)
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

int L, U, champion;
int cnt[MAXCNT + 1];

bool solve()
{
    Zero(cnt);
    IVi it = lower_bound(primes.begin(), primes.end(), L);

    if (it == primes.end()) return false;

    int maxcnt = 0;
    champion = 0;

    int prev = *it;
    ++it;

    while (it != primes.end() && *it <= U) {
        int diff = *it - prev;

        ++cnt[diff];
        if (cnt[diff] > maxcnt) {
            maxcnt = cnt[diff];
            champion = diff;
        }
        else if (cnt[diff] == maxcnt)
            champion = -1;

        prev = *it;
        ++it;
    }

    return champion > 0;
}

int main()
{
    prime_sieve();

    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &L, &U);

        if (solve())
            printf("The jumping champion is %d\n", champion);
        else
            puts("No jumping champion");
    }

    return 0;
}
