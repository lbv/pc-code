#include <cstdio>

typedef unsigned int u32;

u32 a, b;
int ans;

int main()
{
    while (true) {
        scanf("%u%u", &a, &b);
        if (a == 0 && b == 0) break;

        ans = 0;

        int x, y, c;  // digits and carry
        c = 0;
        while (a != 0 || b != 0) {
            x = a % 10;
            y = b % 10;
            if (x + y + c > 9) {
                ++ans;
                c = (x+y+c) / 10;
            }
            else
                c = 0;
            a /= 10;
            b /= 10;
        }

        if (ans == 0)
            puts("No carry operation.");
        else if (ans == 1)
            puts("1 carry operation.");
        else
            printf("%d carry operations.\n", ans);
    }

    return 0;
}
