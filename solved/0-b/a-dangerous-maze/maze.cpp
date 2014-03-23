#include <cstdio>

int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n;
        scanf("%d", &n);

        int sum = 0;
        int neg = 0;  // number of negative numbers

        for (int i = 0; i < n; i++) {
            int num; scanf("%d", &num);
            if (num < 0) num = -num, neg++;
            sum += num;
        }

        if (neg == n) {
            printf("Case %d: inf\n", ncase++);
            continue;
        }

        int num = sum*n;
        int den = n*(n-neg);

        int g = gcd(num, den);
        num /= g;
        den /= g;
        printf("Case %d: %d/%d\n", ncase++, num, den);
    }

    return 0;
}
