#include <cmath>
#include <cstdio>

typedef long long i64;

i64 i;
i64 a, b;  // numerator and denominator of the answer

void solve()
{
    // number of the diagonal in Cantor's series
    i64 diag = ceil(sqrt(0.25 + 2*i) - 0.5);

    // number of the term inside the diagonal
    i64 n = i - (diag-1)*diag / 2;
    a = diag + 1 - n;
    b = n;
}

int main()
{
    while (true) {
        if (scanf("%lld", &i) != 1) break;

        solve();
        printf("%lld/%lld\n", a, b);
    }

    return 0;
}
