#include <cstdio>

int a, b, c, d, e;

int main()
{
    while (true) {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
        if (a == 0) break;

        printf("%d\n", a*b*c*d*d*e*e);
    }

    return 0;
}
