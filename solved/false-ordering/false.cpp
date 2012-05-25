#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> IV;

namespace numbers
{
    const int MAX = 32;  // sqrt(1000)
    const int LMT = 6;   // sqrt(sqrt(1000))
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
}

#define MAXN 1000

IV primes;
int nprimes;
int order[MAXN];     // the numbers from 1 to 1000
int divs[MAXN + 1];  // divs[i] has the number of divisors of i

bool falseOrder(int a, int b)
{
    if (divs[a] < divs[b]) return true;
    if (divs[a] == divs[b] && a > b) return true;
    return false;
}

int divisors(int x)
{
    int sx = static_cast<int>(sqrt(x));
    int d = 1;
    for (int i = 0; i < nprimes; i++) {
        int p = primes[i];
        if (p > sx) break;
        if (x % p != 0) continue;
        int e = 0;
        while (x % p == 0) { x /= p; e++; }
        d *= e + 1;
        sx = static_cast<int>(sqrt(x));
    }
    if (x > 1) d *= 2;
    return d;
}

void prepare()
{
    primes = numbers::primeSieveList();
    nprimes = primes.size();
    for (int i = 0; i < MAXN; i++) order[i] = i+1;
    for (int i = 1; i <= MAXN; i++) divs[i] = divisors(i);

    sort(order, order + MAXN, falseOrder);
}

int n;

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%d", &n);
        printf("Case %d: %d\n", ncase++, order[n-1]);
    }

    return 0;
}
