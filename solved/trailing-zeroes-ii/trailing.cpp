#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long i64;

// Calculates the highest exponent of prime p that divides n!
int powerFact(int n, int p)
{
    int e = 0; for (i64 d=p; d <= n; d *= p) e += n/d; return e;
}

int power2(int n) { int e = 0; while (n % 2 == 0) e++, n/=2;  return e; }
int power5(int n) { int e = 0; while (n % 5 == 0) e++, n/=5;  return e; }

int zeroes(int n, int r, int p, int q)
{
    int n2 = powerFact(n, 2) - powerFact(r, 2) - powerFact(n-r, 2);
    n2 += power2(p) * q;
    int n5 = powerFact(n, 5) - powerFact(r, 5) - powerFact(n-r, 5);
    n5 += power5(p) * q;
    return min(n2, n5);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n, r, p, q;
        scanf("%d%d%d%d", &n, &r, &p, &q);
        printf("Case %d: %d\n", ncase++, zeroes(n, r, p, q));
    }

    return 0;
}
