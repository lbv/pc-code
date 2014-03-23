#include <algorithm>
#include <cstdio>
using namespace std;


typedef long long i64;


i64 n;

i64 solve()
{
    i64 ans = 0;

    i64 pre = n;

    i64 hi = n;
    i64 lo = 1;

    while (lo <= hi) {
        i64 q = n / lo;

        hi = q;
        i64 range = pre - hi;

        ans += range * (lo - 1);

        if (lo <= hi) ans += q;

        ++lo;
        pre = hi;
    }

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%lld", &n);

        printf("%lld\n", solve());
    }

    return 0;
}
