#include <cstdio>

typedef unsigned int u32;

u32 a, b;

int main()
{
    while (true) {
        if (scanf("%u%u", &a, &b) != 2) break;
        printf("%u\n", a ^ b);
    }

    return 0;
}
