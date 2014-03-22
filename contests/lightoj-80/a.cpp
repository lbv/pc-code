#include <cstdio>

int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int a, b;
        scanf("%d%d", &a, &b);

        int g = gcd(a, b);
        int l = a/g*b;
        printf("Case %d: %d %d\n", ++ncase, l, g);
    }

    return 0;
}
