#include <cstdio>

typedef long long i64;

i64 a, b, c;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%lld%lld%lld", &a, &b, &c);

        printf("Case %d: ", ++ncase);
        if (a <= 0 || b <= 0 || c <= 0 ||
            a + b <= c ||
            a + c <= b ||
            b + c <= a)
            puts("Invalid");
        else if (a == b && a == c)
            puts("Equilateral");
        else if (a == b || b == c || a == c)
            puts("Isosceles");
        else
            puts("Scalene");
    }

    return 0;
}
