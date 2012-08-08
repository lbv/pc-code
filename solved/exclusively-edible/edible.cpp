#include <cstdio>

int m, n, r, c;

int main()
{
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d%d%d%d", &m, &n, &r, &c);

        int nim1 = r;
        int nim2 = m - r - 1;
        int nim3 = c;
        int nim4 = n - c - 1;

        int ans = nim1 ^ nim2 ^ nim3 ^ nim4;

        if (ans == 0)
            puts("Hansel");
        else
            puts("Gretel");
    }

    return 0;
}
