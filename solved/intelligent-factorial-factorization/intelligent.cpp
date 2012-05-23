#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> IV;

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 105;
    const int LMT = 10;   // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void primeSieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
    // Calculates the highest exponent of prime p that divides n!
    int powDivFact(int n, int p) {
        int sd = 0; for (int N=n; N; N /= p) sd += N % p; return (n-sd)/(p-1);
    }
    int powDivFact2(int n) {
        int sd = 0; for (int N=n; N; N /= 2) sd += N % 2; return n-sd;
    }
}

int main()
{
    using namespace Num;

    primeSieve();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int N;
        scanf("%d", &N);

        printf("Case %d: %d = 2 (%d)", ncase++, N, powDivFact2(N));
        for (int i = 1; primes[i] <= N; i++)
            printf(" * %d (%d)", primes[i], powDivFact(N, primes[i]));
        putchar('\n');
    }

    return 0;
}
