#include <cmath>
#include <cstdio>

typedef long long i64;

i64 n, sol;

i64 sum(i64 from, i64 to)
{
    if (from == to) return to;
    return (to*(to+1) - (from-1)*from) / 2;
}

void solve()
{
    i64 sq = sqrt(n);
    sol = 0;
    for (i64 i = 2; i <= sq; ++i)
        sol += sum(i, n/i) + i * (n/i - i);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%lld", &n);
        solve();
        printf("Case %d: %lld\n", ++ncase, sol);
    }

    return 0;
}
