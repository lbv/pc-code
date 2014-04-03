#include <cstdio>
#include <vector>
using namespace std;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef vector<int> IV;

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000000;  // 10^6
    const int LMT =    1000;  // sqrt(MAX)
    const int MAXP = 91202;   // 1.26 * MAX/log(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    IV pbc[10][6];  // primes by count of digits
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        pbc[2][1].push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) {
            primes.push_back(i);
            int cnt[10] = { 0 };
            int n = i;
            while (n != 0) {
                ++cnt[n % 10];
                n /= 10;
            }
            for (int j = 0; j < 10; ++j)
                if (cnt[j] > 0 && cnt[j] <= 5)
                    pbc[j][cnt[j]].push_back(i);
        }
    }
}
using namespace Num;

int a, b, c, ans;

bool solve()
{
    int s = pbc[a][b].size();
    if (s < c + 1) return false;

    ans = pbc[a][b][c];
    return true;
}

int main()
{
    prime_sieve();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &a, &b, &c);

        if (solve())
            printf("Case %d: %d\n", ++ncase, ans);
        else
            printf("Case %d: Not Found!\n", ++ncase);
    }

    return 0;
}
