#include <cstdio>


typedef long long i64;


i64 n;

i64 solve()
{
    i64 ans = 0;

    i64 hi = n;
    i64 lo = 1;

    while (lo <= hi) {
        i64 q = hi / lo;
        i64 nxt = hi / q + 1;

        ans += (nxt - lo) * q;

        lo = nxt;
    }

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%lld", &n);

        printf("Case %d: %lld\n", ++ncase, solve());
    }

    return 0;
}
