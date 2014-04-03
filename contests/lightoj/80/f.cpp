#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> IV;

#define MAXN 100
#define INF  100010

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 317;  // sqrt(10^5)
    const int LMT =  18;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void primeSieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
}
using namespace Num;

int ns[MAXN];
int es[MAXN];
int N;
int maxpow;
int A, B;

void solve()
{
    sort(ns, ns + N);
    maxpow = 0;
    A = B = INF;

    int e1, e2;

//    int top = sqrt(ns[N-1]);

    cFor (IV, p, primes) {
        int prime = *p;

        // if (prime > top) break;

        e1 = e2 = 0;

        for (int i = 0; i < N; ++i) {
            es[i] = 0;
            if (ns[i] % prime != 0) continue;

            for (int n = ns[i]; n % prime == 0; n/=prime) ++es[i];

            if (es[i] > e1) e2 = e1, e1 = es[i];
            else if (es[i] > e2) e2 = es[i];
        }

        if (e2 >= maxpow) {
            int i, a, b;
            for (i = 0; es[i] < e2; ++i) ;
            a = ns[i];
            for (++i; es[i] < e2; ++i) ;
            b = ns[i];

            if (e2 > maxpow || (a < A || (a==A && b < B))) {
                A=a, B=b;
                maxpow = e2;
                // printf("  :: a new partial sol: %d  %d, %d  prime: %d\n", maxpow, A, B, prime);
            }
        }
    }

    if (maxpow == 0)
        for (int i = 0, j = 1; j < N; ++i, ++j)
            if (ns[i] == ns[j]) {
                maxpow = 1;
                A = ns[i];
                B = ns[j];
                break;
            }
}

int main()
{
    primeSieve();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        for (int i = 0; i < N; ++i) scanf("%d", &ns[i]);

        solve();

        if (maxpow == 0)
            printf("Case %d: No Solution\n", ++ncase);
        else
            printf("Case %d: %d %d\n", ++ncase, A, B);
    }

    return 0;
}
