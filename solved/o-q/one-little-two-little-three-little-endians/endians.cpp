#include <cstdio>

int n;

int main()
{
    while (true) {
        if (scanf("%d", &n) != 1) break;

        printf("%d converts to ", n);

        n = (n & 0xFF) << 24 | (n & 0xFF00) << 8 |
            (n & 0xFF0000) >> 8 | (n & 0xFF000000) >> 24;

        printf("%d\n", n);
    }

    return 0;
}
