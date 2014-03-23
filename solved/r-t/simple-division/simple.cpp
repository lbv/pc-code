#include <cstdio>
#include <cstdlib>

int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }

int g, n, pre;

int main()
{
    while (true) {
        scanf("%d", &pre);
        if (pre == 0) break;
        scanf("%d", &n);

        g = abs(n-pre);
        if (g == 0) g = n;
        pre = n;

        while (true) {
            scanf("%d", &n);
            if (n == 0) {
                printf("%d\n", g);
                break;
            }

            g = gcd(abs(n-pre), g);
            if (g == 0) g = n;
            pre = n;
        }
    }

    return 0;
}
