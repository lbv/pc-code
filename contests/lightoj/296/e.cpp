#include <cstdio>


typedef unsigned long long u64;


u64 x;


bool noninc(u64 n)
{
    int last = n % 10;

    while (n) {
        int d = n % 10;
        if (d < last) return false;
        n /= 10;
        last = d;
    }
    return true;
}

u64 solve()
{
    u64 ans = x + x;

    while (! noninc(ans))
        ans += x;

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%llu", &x);
        printf("%llu\n", solve());
    }

    return 0;
}
