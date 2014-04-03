#include <cstdio>

typedef unsigned long long u64;

int M, P;
u64 X;

void solve()
{
    for (int i = P - 1; i >= 0; --i) {
        int d = (X / (1 << i)) % 4;

        if (d == 0 || d == 3)
            putchar('0');
        else
            putchar('1');
    }

    putchar('\n');
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &M, &P);

        while (M--) {
            scanf("%llu", &X);
            solve();
        }
    }

    return 0;
}
