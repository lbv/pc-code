#include <cstdio>

typedef long long i64;

int a, b;
i64 n;

int main()
{
    while (true) {
        scanf("%d%d%lld", &a, &b, &n);
        if (a == 0) break;

        int ans = 0;
        switch (n % 5) {
        case 0:
            ans = a;
            break;
        case 1:
            ans = b;
            break;
        case 2:
            ans = (1+b)/a;
            break;
        case 3:
            ans = (1+a+b)/(a*b);
            break;
        case 4:
            ans = (1+a)/b;
            break;
        }
        printf("%d\n", ans);
    }

    return 0;
}
