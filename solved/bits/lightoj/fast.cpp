#include <cstdio>

typedef long long i64;

i64 N;

// Finds the most significant bit set on n. The bit is left in b, and its
// zero-indexed position in p
void msb(i64 n, i64 &b, int &p)
{
    for (b = 1, p = 0, n >>= 1; n; b <<= 1, n >>= 1, ++p);
}

// Returns the number of adjacent bits from 0 to N
i64 f(i64 n)
{
    if (n < 3) return 0;
    if (n == 3) return 1;

    i64 b;
    int p;
    msb(n, b, p);

    i64 ans = (p - 1) * (1LL << (p - 2));
    if (n & (b >> 1))
        ans += (n & ~b & ~(b >> 1)) + 1;

    ans += f(n & ~b);
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%lld", &N);

        printf("Case %d: %lld\n", ++ncase, f(N));
    }

    return 0;
}
