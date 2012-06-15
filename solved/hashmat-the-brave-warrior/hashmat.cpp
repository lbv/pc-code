#include <cstdio>

typedef long long i64;

i64 a, b, ans;

int main()
{
    while (true) {
        if (scanf("%lld%lld", &a, &b) != 2) break;

        if (a > b) ans = a - b;
        else ans = b - a;

        printf("%lld\n", ans);
    }

    return 0;
}
