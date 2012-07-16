#include <cstdio>


typedef unsigned long long u64;


int x;


u64 ipow(u64 b, int e) {
    u64 res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
    return res;
}


u64 sum()
{
    u64 ans = (ipow(x, 4) + ipow(x, 3)*2 + ipow(x, 2))/4;
    return ans;
}

int main()
{
    while (true) {
        if (scanf("%d", &x) != 1) break;

        printf("%llu\n", sum());
    }

    return 0;
}
