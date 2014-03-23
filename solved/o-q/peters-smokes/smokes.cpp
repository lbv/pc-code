#include <cstdio>

typedef unsigned long long u64;

u64 n, k;

int main()
{
    while (true) {
        if (scanf("%llu%llu", &n, &k) != 2) break;

        u64 b = 0;
        u64 c = n;
        u64 total = 0;
        u64 x, y;

        while (c > 0 || b >= k) {
            total += c;
            x = (c + b) / k;
            y = (c + b) % k;
            c = x, b = y;
        }

        printf("%llu\n", total);
    }

    return 0;
}
