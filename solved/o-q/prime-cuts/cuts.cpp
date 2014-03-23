#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


typedef vector<int> IV;
typedef IV::iterator IVi;


//
// Number Theory
//
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000;  // 10^6
    const int LMT =   32;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(1); // Yuck! Just for this problem
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
}
using namespace Num;


int N, C;


int main()
{
    prime_sieve();

    while (true) {
        if (scanf("%d%d", &N, &C) != 2) break;

        printf("%d %d:", N, C);
        IVi it = upper_bound(primes.begin(), primes.end(), N);
        int cnt = (it - primes.begin());

        int from, to;
        if (cnt % 2 == 0) {
            from = max(cnt / 2 - C, 0);
            to = min(cnt / 2 + C, cnt);
        }
        else {
            from = max((cnt + 1) / 2 - C, 0);
            to = min(cnt / 2 + C, cnt);
        }

        for (int i = from; i < to; ++i)
            printf(" %d", primes[i]);
        printf("\n\n");
    }

    return 0;
}
