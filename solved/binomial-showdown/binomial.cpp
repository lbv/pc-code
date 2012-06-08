#include <algorithm>
#include <cstdio>
using namespace std;

typedef unsigned long long u64;

int main()
{
    u64 n, k;
    u64 num, den, ans;

    while (true) {
        scanf("%llu%llu", &n, &k);
        if (n == 0 && k == 0) break;

        num = max(k, n-k) + 1;
        den = 1;

        ans = 1;
        for (u64 i = num; i <= n; ++i)
            ans = ans * i / den++;

        printf("%llu\n", ans);
    }

    return 0;
}
