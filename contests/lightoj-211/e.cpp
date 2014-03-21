#include <cstdio>

int n;

int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        int num = 0;
        int den = n;

        int dist;
        while (n--) {
            scanf("%d", &dist);
            num += dist;
        }

        int g = gcd(num, den);
        num /= g;
        den /= g;

        printf("Case %d: ", ++ncase);

        if (den == 1)
            printf("%d\n", num);
        else
            printf("%d/%d\n", num, den);
    }

    return 0;
}
