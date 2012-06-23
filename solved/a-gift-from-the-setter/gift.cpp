#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 100000
#define MOD 1000007

typedef long long i64;

int K, C, n;
i64 a[MAXN];

i64 ans;

void solve()
{
    for (int i = 1, j = 0; i < n; ++i, ++j)
        a[i] = (K*a[j] + C) % MOD;

    sort(a, a + n);

    ans = 0;
    int pos = 0;
    int neg = n - 1;
    for (int i = 0; i < n; ++i) {
        ans += a[i] * (pos - neg);
        --neg;
        ++pos;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d%lld", &K, &C, &n, &a[0]);

        solve();

        printf("Case %d: %lld\n", ++ncase, ans);
    }

    return 0;
}
