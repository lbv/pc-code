#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
using namespace std;


#define MAXT 500
#define MAXC 15
#define MAXA 50

#define Zero(v) memset((v), 0, sizeof(v))


typedef vector<int> IV;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000;
    const int LMT =   32;  // sqrt(MAX)
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


bool vis[1001];
int nprimes;


void test_case(bool crit=false)
{
    int C = rand() % MAXC + 1;
    if (crit) C = MAXC;
    printf("%d\n", C);

    Zero(vis);
    while (C--) {
        int P, a;
        do {
            P = primes[rand() % nprimes];
        } while (vis[P]);
        vis[P] = true;
        a = rand() % MAXA + 1;

        printf("%d %d\n", P, a);
    }
}

int main()
{
    srand(time(NULL));
    prime_sieve();
    nprimes = primes.size();

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}
