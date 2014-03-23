#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

typedef vector<int> IV;

namespace numbers
{
    const int MAX = 65536;  // sqrt(2^32) = 2^16
    const int LMT = 256;    // sqrt(2^16) = 2^8
    int _c[(MAX>>5)+1];
#define ISCOMP(n)  (_c[(n)>>5]&(1<<((n)&31)))
#define SETCOMP(n) _c[(n)>>5]|=(1<<((n)&31))
    IV primeSieveList()
    {
        SETCOMP(0); SETCOMP(1);
        for (int i = 3; i <= LMT; i += 2)
            if (!ISCOMP(i)) for (int j = i*i; j <= MAX; j+=i+i) SETCOMP(j);
        IV p;
        p.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!ISCOMP(i)) p.push_back(i);
        return p;
    }
    int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }
}

int x;
IV primes;
int nprimes;

int power()
{
    int sx = static_cast<int>(sqrt(fabs(x)));
    int power = 0;
    for (int i = 0; i < nprimes; i++) {
        int p = primes[i];
        if (p > sx) return 1;
        if (x % p != 0) continue;
        int c = 0;
        while (x % p == 0) {
            x /= p;
            c++;
        }
        if (power == 0) power = c;
        else power = numbers::gcd(power, c);
        if (abs(x) == 1) {
            if (x < 0)
                while ((power & 1) == 0) power >>= 1;
            return power;
        }
        sx = static_cast<int>(sqrt(fabs(x)));
    }
    return 1;
}

void prepare()
{
    primes = numbers::primeSieveList();
    nprimes = primes.size();
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%d", &x);
        printf("Case %d: %d\n", ncase++, power());
    }

    return 0;
}
